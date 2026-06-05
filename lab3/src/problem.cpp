#include "problem.hh"
#include "permutation.hh"
#include <climits>
#include <iostream>
#include <chrono>
#include <list>

using _clock_t = std::chrono::high_resolution_clock;

Problem::Problem(Instance &i, int num) : p(num), s(p,i), instance(i){
	n = num;
}

int Problem::brute_p2(){
  return 0;
}

int Problem::brute_p3(){
  return 0;
}

int Problem::PD_P2(){
  return 0;
}

int Problem::PD_P3(){
  return 0;
}

int Problem::PTAS_P2(){
  return 0;
}

int Problem::PTAS_P3(){
  return 0;
}

int Problem::brute_force() {
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

int Problem::LSA(){
  return 0;
}

int Problem::LPT(){
  return 0;
}

int Problem::PD(){
  if(instance.m == 2)
    return PD_P2();
  else if(instance.m == 3)
    return PD_P3();
  else
    return -1;
}

int Problem::PTAS(){
  if(instance.m == 2)
    return PTAS_P2();
  else if(instance.m == 3)
    return PTAS_P3();
  else
    return -1;
}

int Problem::FPTAS(){
  if(instance.m != 2)
    return -1;

  // Begin FPTAS algorithm
}

