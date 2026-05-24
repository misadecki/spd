#ifndef SOLUTION_HH
#define SOLUTION_HH

#include "dataTypes.hh"
#include "Permutation.hh"
#include <algorithm>

class Solution {
  //int current_L = 0;
  Permutation &p;
  Instance &i;
  std::vector<std::vector<int>> c;
public:
  int solve();
  Solution(Permutation &perm, Instance &instance) : p(perm), i(instance), c(instance.m + 1, std::vector<int>(instance.n+1, 0)){};
};

#endif // SOLUTION_HH
