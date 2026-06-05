#include "problem.hh"
#include "permutation.hh"
#include <climits>
#include <iostream>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using _clock_t = std::chrono::high_resolution_clock;

Problem::Problem(Instance &i, int num, int k_ptas, int k_fptas) : p(num), s(p,i), instance(i){
  n = num;
  if(n < k_ptas || n < k_fptas)
    exit(EXIT_FAILURE);
  K_ptas = k_ptas;
  K_fptas = k_fptas;
}

int Problem::PTAS() {
  if (instance.m != 2)
    return -1;

  auto start = _clock_t::now();
  int best_sol = 0;
  std::vector<int> sorted_tasks = instance.pj;
  std::vector<int> load(instance.m);
  std::sort(sorted_tasks.begin(), sorted_tasks.end(), std::greater<>());

  p = Permutation(K_ptas); 
  brute_force(sorted_tasks, K_ptas, 0);
  for (int j = 0; j < K_ptas; ++j) {
    load[p[j]] += sorted_tasks[j];
  }

  for (size_t j = K_ptas; j < sorted_tasks.size(); ++j) {
    auto min_load = std::min_element(load.begin(), load.end());
    *min_load += sorted_tasks[j];
  }

  best_sol = *(std::max_element(load.begin(), load.end()));

  auto end = _clock_t::now();
  std::cout << best_sol << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
  return best_sol;
}

int Problem::FPTAS() {
  auto start = _clock_t::now();
  std::vector<int> red_pj(instance.n);

  for (size_t j = 0; j < instance.pj.size(); ++j) {
    red_pj[j] = std::floor(instance.pj[j] / K_fptas);
  }

  int best_sol = PD(&red_pj, 0);
  auto end = _clock_t::now();
  std::cout << best_sol << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
  return best_sol;
}

int Problem::brute_force(std::vector<int> &pj_vec, int j_tasks, int print_result) {
  auto start = _clock_t::now();
  int best_sol = INT_MAX;
  std::vector<int> best_perm;
  int temp;
  do {
	  temp = s.solve(pj_vec, j_tasks);
	  if (temp < best_sol) {
		  best_sol = temp;
		  best_perm = p.perm;
	  }
  } while(p.next_perm());

  p.perm = best_perm;
  auto end = _clock_t::now();

  if(print_result){
    std::cout << best_sol << "\t";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
  }

  return best_sol;
}

int Problem::LSA() {
  auto start = _clock_t::now();
  std::vector<int> load(instance.m);

  for (size_t j = 0; j < instance.pj.size(); ++j) {
    auto min_load = std::min_element(load.begin(), load.end());
    *min_load += instance.pj[j];
  }

  int best_sol = *std::max_element(load.begin(), load.end());
  auto end = _clock_t::now();
  std::cout << best_sol << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
  return best_sol;
}

int Problem::LPT() {
  auto start = _clock_t::now();
  std::vector<int> load(instance.m);
  std::vector<int> pj_sorted = instance.pj;
  std::sort(pj_sorted.begin(), pj_sorted.end(), std::greater<>());

  for (size_t j = 0; j < pj_sorted.size(); ++j) {
    auto min_load = std::min_element(load.begin(), load.end());
    *min_load += pj_sorted[j];
  }

  int best_sol = *std::max_element(load.begin(), load.end());
  auto end = _clock_t::now();
  std::cout << best_sol << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";

  return best_sol;
}

int Problem::PD(std::vector<int> *pj_vec, int print_result){
  if(instance.m != 2)
    return -1;

  if(pj_vec == nullptr)
    pj_vec = &instance.pj;

  auto start = _clock_t::now();
  std::vector<int> m1(n), m2(0);
  for(int j=0; j<n; ++j)
    m1[j] = j;

  int sum_pj = 0;
  for(int pj : *pj_vec)
    sum_pj += pj;
  sum_pj = sum_pj/2 + 1;
  std::vector<std::vector<int>> T(n + 1, std::vector<int>(sum_pj, 0));
  
  for(int j=1; j<=n; ++j)
    for(int k=1; k<sum_pj; ++k)
      if ((T[j-1][k]==1) || ((k>=(*pj_vec)[j-1]) && T[j-1][k-(*pj_vec)[j-1]]==1))
        T[j][k]=1;

  for(int k=sum_pj-1; k >= 0; ){
    int j;
    for(j=n; T[j-1][k] != 0; --j);
    m2.push_back(j-1);
    m1.erase(m1.begin()+j-1);
    k -= (*pj_vec)[j-1];
  }

  int best_sol = std::max(s.solve(m1), s.solve(m2));
  auto end = _clock_t::now();

  if(print_result){
    std::cout << best_sol << "\t";
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
  }

  return best_sol;
}
