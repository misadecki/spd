#ifndef PROBLEM_HH
#define PROBLEM_HH

#include "permutation.hh"
#include "solution.hh"
#include "instance.hh"
#include <vector>

class Problem {
  Permutation p; 
  Solution s;
  int n;
  Instance &instance;
  int K_ptas;
  int K_fptas;
public:
  Problem(Instance &i, int num, int k_ptas, int k_fptas);
  int brute_force(std::vector<int> &pj_vec, int j_tasks);
  int LSA();
  int LPT();
  int PD();
  int PTAS();
  int FPTAS();
};

#endif // PROBLEM_HH
