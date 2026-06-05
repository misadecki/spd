#include "solution.hh"
#include <climits>
#include <list>

int Solution::solve() {
  int c_max = 0;
  int *c = (int *)malloc(i.m * sizeof(int));
  for(int i=0; i<i.m; ++i)
    c[i] = 0;

  for(int task_id=0; task_id<i.n; ++task_id)
    c[p[task_id]] += i[task_id];

  for(int i=0; i<i.m; ++i){
    if(c[i] > c_max)
      c_max = c[i];
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
