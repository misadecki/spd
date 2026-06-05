#ifndef SOLUTION_HH
#define SOLUTION_HH

#include "instance.hh"
#include "permutation.hh"
#include <vector>

class Solution {
  Permutation &p;
  Instance &i;

public:
  int solve(std::vector<int> &pj_vec, int n_tasks);
  int solve(std::vector<std::vector<int>> &v);
  int solve(std::vector<int> &v);
  Solution(Permutation &perm, Instance &instance) : p(perm), i(instance) {};
};

#endif // SOLUTION_HH
