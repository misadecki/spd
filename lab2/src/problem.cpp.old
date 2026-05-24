#include "problem.hh"
#include "Permutation.hh"
#include <climits>
#include <iostream>
#include <algorithm>
#include <queue>
#include <chrono>

using _clock_t = std::chrono::high_resolution_clock;

Problem::Problem(std::vector<Task> &tasks, int num) : p(num), s(p,tasks), t(tasks){
	n = num;
}

int Problem::sort_algorithm(bool by_rj) {
  auto start = _clock_t::now();
	if (by_rj) {
    std::sort(p.perm.begin(), p.perm.end(), [&](const int a, const int b) {
    return t[a].rj < t[b].rj;
    });
    //std::cout << p << std::endl;
	} else {
    std::sort(p.perm.begin(), p.perm.end(), [&](const int a, const int b) {
    return t[a].dj < t[b].dj;
    });
	}
  int result = s.solve();
  auto end = _clock_t::now();
  std::string param = "by_dj): ";
  if (by_rj) param = "by_rj): ";
  //std::cout << "t(" << param;
  std::cout << result << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";

	return result;
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

int Problem::own_algorithm(){
  auto start = _clock_t::now();
	int L;

	for(int i = 0; i < n-1; ++i) {
		L = s.solve();
		iter_swap(p.perm.begin()+i, p.perm.begin()+i+1);
		if(s.solve() > L) 
			iter_swap(p.perm.begin()+i, p.perm.begin()+i+1);
	}
  int result = s.solve();
  auto end = _clock_t::now();
  //std::cout << "t = ";
  std::cout << result << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
	return result;
}

int Problem::Schrage(){
  auto start = _clock_t::now();
	auto compare = [this](int a, int b) {
		return t[a].dj > t[b].dj;
	};
	std::priority_queue all_tasks(p.perm.begin(), p.perm.end(), [&](const int a, const int b) {
		return t[a].rj > t[b].rj;
	});
	std::priority_queue<int, std::vector<int>, decltype(compare)> available(compare);
	
	int Lmax = INT_MIN;
	int time = 0;
	int temp_task;
	int current_task;
	bool last_flag = false;

	if(!all_tasks.empty()){
		temp_task = all_tasks.top();
		all_tasks.pop();
		time = std::max(time, t[temp_task].rj);
	}
	while(!all_tasks.empty() || !available.empty()) {
		while(t[temp_task].rj <= time && !last_flag) {
			available.push(temp_task);
			if(!all_tasks.empty()){
				temp_task = all_tasks.top();
				all_tasks.pop();
			} else {
				last_flag = true;	
			}
		}
		current_task = available.top();
		available.pop();
		time += t[current_task].pj;
		Lmax = std::max(Lmax, time - t[current_task].dj);
		//std::cout << "Task: " << current_task << "; L = " << time - t[current_task].dj << std::endl;
		if(t[temp_task].rj > time && available.empty())
			time = std::max(time, t[temp_task].rj);
	}
  auto end = _clock_t::now();
  std::cout << Lmax << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
	return Lmax;
}

int Problem::Schrage_preemptive(){
  auto start = _clock_t::now();
	auto compare = [this](int a, int b) {
		return t[a].dj > t[b].dj;	// Czy tutaj dodać
						// porównawanie pj?
	};
	std::priority_queue all_tasks(p.perm.begin(), p.perm.end(), [&](const int a, const int b) {
		return t[a].rj > t[b].rj;
	});
	std::priority_queue<int, std::vector<int>, decltype(compare)> available(compare);
	
	int Lmax = INT_MIN;
	int time = 0;
	int temp_task;
	int current_task;
	bool last_flag = false;

	if(!all_tasks.empty()){
		temp_task = all_tasks.top();
		all_tasks.pop();
		time = std::max(time, t[temp_task].rj);
	}
	while(!all_tasks.empty() || !available.empty()) {
		while(t[temp_task].rj <= time && !last_flag) {
			available.push(temp_task);
			if(!all_tasks.empty()){
				temp_task = all_tasks.top();
				all_tasks.pop();
			} else {
				last_flag = true;	
			}
		}
		current_task = available.top();
		if(t[temp_task].rj < (time + t[current_task].pj) && !last_flag){
			t[current_task].pj = t[current_task].pj - (t[temp_task].rj - time);
			time = t[temp_task].rj;
			//std::cout << "wywlaszylem taska" << std::endl;
		} else {
			time += t[current_task].pj;
			Lmax = std::max(Lmax, time - t[current_task].dj);
			available.pop();
			//std::cout << "Task: " << current_task << "; L = " << time - t[current_task].dj <<std::endl;
		}
		if(t[temp_task].rj > time && available.empty())
			time = std::max(time, t[temp_task].rj);
	}


  auto end = _clock_t::now();
  std::cout << Lmax << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                           start).count() << "\t";
	
	return Lmax;
}
