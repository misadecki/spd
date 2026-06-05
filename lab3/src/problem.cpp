#include "problem.hh"
#include "permutation.hh"
#include <climits>
#include <iostream>
#include <chrono>
#include <cmath>

using _clock_t = std::chrono::high_resolution_clock;

Problem::Problem(Instance &i, int num, int k_ptas, int k_fptas) : p(num), s(p,i), instance(i){
	n = num;
  K_ptas = k_ptas;
  K_fptas = k_fptas;
}

int Problem::PTAS_P2() {
  if (instance.m != 2)
    return -1;

  auto start = _clock_t::now();
  std::vector<int> sorted_tasks = instance.pj;
  std::sort(sorted_tasks.begin(), sorted_tasks.end(), std::greater<>());
  int c_brute = 0, c_lsa = 0;

  for (int j = sorted_tasks.size(); j > K_ptas; --j) {
    c_brute = brute_force_p2();
  }

  for (int j = 0; j < K_ptas; ++j) {
    c_lsa = LSA();
  }
  int best_sol = c_brute + c_lsa;
  auto end = _clock_t::now();

  std::cout << best_sol << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
  return best_sol;
}

int Problem::FPTAS_P2() {
  std::vector<int> red_pj(instance.n);

  for (size_t j = 0; j < instance.pj.size(); ++j) {
    red_pj[j] = std::floor(instance.pj[j] / K_fptas);
  }

  std::vector<int> new_idx = PD_P2(red_pj); //programowanie dynamiczne na
  //wektorze zredukowanym, ma zwrócić wektor nowych indeksów
}

int Problem::brute_force_p2() {
  auto start = _clock_t::now();
  int best_sol = INT_MAX;
  std::vector<int> best_perm;
  int temp;
  do {
	  temp = s.solve();
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

int Problem::PD_P2(){
  if(instance.m == 2)
    return PD_P2();
  return -1;
}
