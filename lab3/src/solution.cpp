#include "solution.hh"
#include <climits>
#include <list>

int Solution::solve(std::vector<int> &pj_vec, int n_tasks) {
  int c_max = 0;
  int *c = (int *)malloc(i.m * sizeof(int));
  for(int j=0; j<i.m; ++j)
    c[j] = 0;

  for(int task_id=0; task_id < n_tasks; ++task_id)
    c[p.perm[task_id]] += pj_vec[task_id];

  for(int j=0; j<i.m; ++j){
    if(c[j] > c_max)
      c_max = c[j];
  }

  return c_max;
}

int Solution::solve(std::vector<std::vector<int>> &v) {
  int c_max = 0;
  int temp_c = 0;

  for(std::vector<int> machine : v){
    temp_c = solve(machine);
    if(temp_c > c_max)
      c_max = temp_c;
  }

  return c_max;
}

int Solution::solve(std::vector<int> &v) {
  int c_max = 0;

  for(int task_id : v)
    c_max += i[task_id];

  return c_max;
}
