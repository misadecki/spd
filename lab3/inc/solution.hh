#ifndef SOLUTION_HH
#define SOLUTION_HH

#include "instance.hh"
#include "permutation.hh"
#include <list>
#include <vector>

class Solution {
  Permutation &p;
  Instance &i;

public:
  int solve();
  int solve(std::vector<int> &v);
  Solution(Permutation &perm, Instance &instance) : p(perm), i(instance) {};
};

#endif // SOLUTION_HH
