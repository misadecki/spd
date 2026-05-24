#ifndef PROBLEM_HH
#define PROBLEM_HH

#include "Permutation.hh"
#include "solution.hh"

class Problem {
  Permutation p; 
  Solution s;
  int n;
  std::vector<Task> &t;
public:
  int sort_algorithm(bool by_rj = false);
  int brute_force();
  int own_algorithm();
  int Schrage();
  int Schrage_preemptive();
  Problem(std::vector<Task> &tasks, int num);
};

#endif // PROBLEM_HH
