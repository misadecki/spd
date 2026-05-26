#ifndef PROBLEM_HH
#define PROBLEM_HH

#include "Permutation.hh"
#include "solution.hh"
#include "dataTypes.hh"
#include <list>

class Problem {
  Permutation p; 
  Solution s;
  int n;
  Instance &instance;
public:
  Problem(Instance &i, int num);
  int brute_force();
  int NEH();
  int johnson();
};

#endif // PROBLEM_HH
