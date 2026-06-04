#include "problem.hh"
#include "Permutation.hh"
#include <climits>
#include <iostream>
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
  std::vector<int> pi;
  //pi.resize(p.get_n());

  auto start = _clock_t::now();
  for (int j = 0; j < p.get_n(); j++) {
    int task_id = p[j];
    C_max = INT_MAX;
    for (int k = 0; k <= j ; k++) {
      auto it = pi.begin() + k;
      pi.insert(it, task_id);
      int c = s.solve(pi);

      if (c < C_max) {
        C_max = c;
        idx = k;
      }
      pi.erase(pi.begin()+k);
    }
    auto it = pi.begin() + idx;
    pi.insert(it, task_id);
  }
  std::cout << "PI: ";
  for(auto element : pi)
	  std::cout << element << " ";
  std::cout << std::endl;

  C_max = s.solve(pi);

  std::cout << C_max << "\t";
  //std::cout << p << std::endl;
  auto end = _clock_t::now();
  //std::cout << "t = ";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";

  return C_max;
}

int Problem::FNEH() {
  int C_max = INT_MAX;
  int idx;

  std::vector<std::vector<FNEHNode>> matrix;
  std::vector<int> temp(instance.m);

  std::vector<int> pi;
  //pi.resize(p.get_n());

  auto start = _clock_t::now();
  for (int j = 0; j < p.get_n(); j++) {
    int task_id = p[j];
    C_max = INT_MAX;
    for (int k = 0; k <= j ; k++) {
      int c = INT_MIN;
      temp[0] = ((k-1>=0) ? matrix[k-1][0].e : 0) + instance[task_id][0];
      if(temp[0] + ((k<j) ? matrix[k][0].q : 0) > c)
        c = temp[0] + ((k<j) ? matrix[k][0].q : 0);
      for(int i=1; i<instance.m; ++i){
        temp[i] = std::max(
			(k-1>=0) ? matrix[k-1][i].e : 0,
			temp[i-1]
			) + instance[task_id][i];

      if(temp[i] + ((k<j) ? matrix[k][i].q : 0) > c)
        c = temp[i] + ((k<j) ? matrix[k][i].q : 0);
      }
      if(c < C_max) {
        C_max = c;
        idx = k;
      }
    }

    auto it = pi.begin() + idx;
    pi.insert(it, task_id);
    auto it_matrix = matrix.begin() + idx;
    matrix.insert(it_matrix, std::vector<FNEHNode>(instance.m));
    for(int i=idx; i>=0; --i){
      for(int m_id=instance.m-1; m_id>=0; --m_id){
        matrix[i][m_id].q = std::max(
			  (i+1<=j) ? matrix[i+1][m_id].q : 0,
			  (m_id+1<instance.m) ? matrix[i][m_id+1].q : 0
			  ) + instance[pi[i]][m_id];
      }
    }
    for(int i=idx; i<=j; ++i){
      for(int m_id=0; m_id<instance.m; ++m_id){
        matrix[i][m_id].e = std::max(
			  (i-1>=0) ? matrix[i-1][m_id].e : 0,
			  (m_id-1>=0) ? matrix[i][m_id-1].e : 0
			  ) + instance[pi[i]][m_id];
      }
    }

  }

  std::cout << "PI: ";
  for(auto element : pi)
	  std::cout << element << " ";
  std::cout << std::endl;

  C_max = s.solve(pi);

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

int Problem::branch_and_bound() {
  int best_sol = NEH(), cmax = 0;
  std::vector<int> sigma, best_perm;

  bnb_recur(sigma, instance.tasks, best_sol, best_perm);

  return best_sol;
}

void Problem::bnb_recur(std::vector<int> &sigma, std::vector<int>& tasks, int &best_sol,
                 std::vector<int> &best_perm) {
  int lb = 0;
  if (tasks.empty()) {
    int cmax = s.solve(sigma);
    if (cmax < best_sol) {
      best_sol = cmax;
      best_perm = sigma;
      return;
    }
  }

  for (size_t i = 0; i < tasks.size(); ++i) {
    int task = tasks[i];
    sigma.push_back(task);
    lb += 1;

    if (lb < best_sol) {
      tasks.erase(tasks.begin() + i);
      bnb_recur(sigma, tasks, best_sol, best_perm);
      tasks.insert(tasks.begin() + i, task);
    }

    sigma.pop_back();
  }
}
