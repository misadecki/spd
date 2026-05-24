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
<<<<<<< Updated upstream:lab2/inc/problem.hh
  //int own_algorithm();
  //int Schrage();
  //int Schrage_preemptive();
  Problem(Instance &i, int num);
=======
  void NEH(Solution &init_sol);
  int Schrage();
  int Schrage_preemptive();
  Problem(std::vector<Task> &tasks, int num);
>>>>>>> Stashed changes:lab2/inc/problem.hh.old
};

#endif // PROBLEM_HH
