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
  int K_ptas;
  int K_fptas;
public:
  Problem(Instance &i, int num, int k_ptas, int k_fptas);
  int brute_force_p2();
  int LSA();
  int LPT();
  int PD_P2();
  int PTAS_P2();
  int FPTAS_P2();
};

#endif // PROBLEM_HH
