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
  void bnb_recur(std::vector<int> &sigma, std::vector<int> &tasks, int &best_sol,
                 std::vector<int> &best_perm);
public:
  Problem(Instance &i, int num);
  int brute_force();
  int NEH();
  int FNEH();
  int johnson();
  int branch_and_bound();
};

struct FNEHNode{
	int e = 0;	// earliest end time before new task
	int q = 0;	// latest start time after task
};

#endif // PROBLEM_HH
