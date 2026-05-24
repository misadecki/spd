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
  Solution(Permutation &perm, Instance &instance) : p(perm), i(instance)
  {
    c.resize(i.m+1);
    for(int n=0; n<(i.n+1); n++){
      c[n].resize(i.n);
      std::fill(c[n].begin(), c[n].end(), 0);
    }
  };
};

#endif // SOLUTION_HH
