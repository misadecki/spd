#include "problem.hh"
#include "Permutation.hh"
#include <climits>
#include <iostream>
#include <algorithm>
#include <queue>
#include <chrono>
#include <list>

using _clock_t = std::chrono::high_resolution_clock;

Problem::Problem(Instance &i, int num) : p(num), s(p,i), instance(i){
	n = num;
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
  std::cout << best_sol << "\t";
  //std::cout << p << std::endl;
  auto end = _clock_t::now();
  //std::cout << "t = ";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";

  return best_sol;
}

int Problem::NEH() {
  int C_max = INT_MAX;
  int idx;

  auto start = _clock_t::now();
  for (int j = 0; j < p.get_n(); j++) {
    int task_id = p[j];
    C_max = INT_MAX;
    for (int k = 0; k <= j ; k++) {
      auto it = p.perm.begin() + k;
      p.perm.insert(it, task_id);
      int c = s.solve();

      if (c < C_max) {
        C_max = c;
        idx = k;
      }
    }
    auto it = p.perm.begin() + idx;
    p.perm.insert(it, task_id);
  }

  std::cout << C_max << "\t";
  //std::cout << p << std::endl;
  auto end = _clock_t::now();
  //std::cout << "t = ";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";

  return C_max;
}

int Problem::johnson() {
  auto start = _clock_t::now();
	if(instance.m != 2) return INT_MAX;
	std::list<int> g1 = {}, g2 = {};
	for(int idx=0; idx<instance.n; idx++){
		if(instance[idx][0]<instance[idx][1])
			g1.push_back(idx);
		else
			g2.push_back(idx);
	}
	// sort g1 niemalejąco
	g1.sort([&](int a, int b){
			return instance[a][0] < instance[b][0];
			});
	// sort g2 nierosnąco
	g2.sort([&](int a, int b){
			return instance[a][1] >= instance[b][1];
			});
	// kolejnosc g1,g2
	g1.splice(g1.end(), g2);
	std::cout << "Lista 1: ";
	for (auto v : g1)
        	std::cout << v << "\n";
	int best_sol = s.solve(g1);
  std::cout << best_sol << "\t";
  //std::cout << p << std::endl;
  auto end = _clock_t::now();
  //std::cout << "t = ";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";

  return best_sol;
}
