#ifndef INSTANCE_HH 
#define INSTANCE_HH

#include <iostream>
#include <sstream>
#include <vector>

struct Instance {
  const int n;	// number of tasks
  const int m;	// number of machines
  std::vector<int> pj;	// tasks array 

  Instance(int n_tasks, int m_operations, std::istringstream &input) :
    n(n_tasks), m(m_operations) {
    std::string buf;
    pj.resize(n_tasks);

    for(int i=0; i<n; ++i){
      input >> buf;
      pj[i] = std::stoi(buf);
    }
  }

  int operator[](int idx) { return pj[idx]; }

  void print() {
    //std::cout << n << "\t" << m << "\t";
    std::cout << "Number of tasks: " << n << std::endl;
    std::cout << "Number of operations: " << m << std::endl;
    for(int p : pj){
      std::cout << p << " ";
    }
    std::cout << std::endl;
  }
};

#endif // INSTANCE_HH 
