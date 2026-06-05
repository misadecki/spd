#include "problem.hh"
#include "permutation.hh"
#include <climits>
#include <iostream>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using _clock_t = std::chrono::high_resolution_clock;

Problem::Problem(Instance &i, int num, int k_ptas, int k_fptas) : p(num), s(i), instance(i){
  n = num;
  if(n < K_ptas || n < K_fptas)
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
  brute_force(sorted_tasks, K_ptas);
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
  std::vector<int> red_pj(instance.n);

  for (size_t j = 0; j < instance.pj.size(); ++j) {
    red_pj[j] = std::floor(instance.pj[j] / K_fptas);
  }

  std::vector<int> new_idx = PD(red_pj); //programowanie dynamiczne na
  //wektorze zredukowanym, ma zwrócić wektor nowych indeksów
}

int Problem::brute_force(std::vector<int> &pj_vec, int j_tasks) {
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
  std::cout << best_sol << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";

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

int Problem::PD(){
  if(instance.m != 2)
    return -1;

  //...
}
