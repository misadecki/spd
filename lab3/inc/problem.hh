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

  int brute_p2();
  int brute_p3();
  int PD_P2();
  int PD_P3();
  int PTAS_P2();
  int PTAS_P3();

public:
  Problem(Instance &i, int num);
  int brute_force();
  int LSA();
  int LPT();
  int PD();
  int PTAS();
  int FPTAS();
};

#endif // PROBLEM_HH
