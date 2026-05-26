#include "solution.hh"
#include <climits>
#include <list>

int Solution::solve() {
  for (int a=1; a<=(i.m); a++){
	 for(int b=1; b<=(i.n); b++)
		c[a][b] = std::max(c[a][b-1], c[a-1][b]) + i[p[b-1]][a-1];	 
  }

  return c[i.m][i.n];
}

int Solution::solve(std::list<int> &task_list) {
  std::vector<int> v{std::begin(task_list), std::end(task_list)};
  for (int a=1; a<=(i.m); a++){
	 for(int b=1; b<=(i.n); b++)
		c[a][b] = std::max(c[a][b-1], c[a-1][b]) + i[v[b-1]][a-1];
  }

  return c[i.m][i.n];
}
