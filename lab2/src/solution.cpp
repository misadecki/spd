#include "solution.hh"
#include <climits>

int Solution::solve() {
  for (int a=1; a<=(i.m); a++){
	 for(int b=1; b<=(i.n); b++)
		c[a][b] = std::max(c[a][b-1], c[a-1][b]) + i[p[b]][a];	 
  }

  return c[i.m][i.n];
}
