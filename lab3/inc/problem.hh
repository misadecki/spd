#ifndef PROBLEM_HH
#define PROBLEM_HH

#include "permutation.hh"
#include "solution.hh"
#include "instance.hh"

class Problem {
  Permutation p; 
  Solution s;
  int n;
  Instance &instance;
  void bnb_recur(std::vector<int> &sigma, std::vector<int> &tasks, int &best_sol,
                 std::vector<int> &best_perm);
public:
  Problem(Instance &i, int num);
  int brute_force();
  int NEH();
  int FNEH(int print_result = 1);
  int johnson();
  int branch_and_bound();
};

#endif // PROBLEM_HH
