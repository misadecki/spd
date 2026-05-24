#ifndef PROBLEM_HH
#define PROBLEM_HH

#include "Permutation.hh"
#include "solution.hh"
#include "dataTypes.hh"

class Problem {
  Permutation p; 
  Solution s;
  int n;
  Instance &instance;
public:
  //int sort_algorithm(bool by_rj = false);
  int brute_force();
  //int own_algorithm();
  //int Schrage();
  //int Schrage_preemptive();
  Problem(Instance &i, int num);
};

#endif // PROBLEM_HH
