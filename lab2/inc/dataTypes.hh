#ifndef DATATYPES_HH
#define DATATYPES_HH

#include <iostream>
#include <string>
#include <sstream>

struct Instance {
  const int n;	// number of tasks
  const int m;	// number of machines/operations
  int **tasks;	// tasks array 

  Instance(int n_tasks, int m_operations, std::istringstream &input) :
    n(n_tasks), m(m_operations) {
    std::string buf;
    int temp;
    tasks = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i){
      tasks[i] = (int*)malloc(m * sizeof(int));
      for (int j = 0; j < m; ++j){
        input >> buf;
        temp = std::stoi(buf);
        input >> buf;
        tasks[i][temp] = std::stoi(buf);
      }
    }
  }

  int* operator[](int idx) { return tasks[idx]; }
  ~Instance() {
    for (int i = 0; i < n; ++i){
      free(tasks[i]);
    }
  }

  void print() {
	  std::cout << n << "\t" << m << "\t";
    //std::cout << "Number of tasks: " << n << std::endl;
    //std::cout << "Number of operations: " << m << std::endl;
    //for (int i = 0; i < n; ++i){
      //std::cout << "Task " << i << ": ";
      //for (int j = 0; j < m; ++j)
        //std::cout << j << "(" << tasks[i][j] << ") ";
      //std::cout << std::endl;
    //} 
  }
};

#endif // DATATYPES_HH
