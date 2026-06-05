#ifndef SOLUTION_HH
#define SOLUTION_HH

#include "instance.hh"
#include <vector>

class Solution {
  Instance &i;

public:
  int solve(std::vector<int> &pj_vec, int n_tasks);
  int solve(std::vector<std::vector<int>> &v);
  int solve(std::vector<int> &v);
  Solution(Instance &instance) : i(instance) {};
};

#endif // SOLUTION_HH
