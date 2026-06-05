#ifndef PERMUTATION_HH
#define PERMUTATION_HH
#include <vector>
#include <ostream>

class Permutation {
	int n = 0;
public:
	std::vector<int> perm;
	Permutation(){ perm = {0}; };
	Permutation(int n_tasks) : n(n_tasks){ perm.assign(n_tasks, 0); };
	
	int operator[](int idx) { return perm[idx]; };
	int operator==(const Permutation &other) { return perm == other.perm; };
	void operator=(const Permutation &other) { perm = other.perm; };
	friend std::ostream &operator<<(std::ostream &stream, Permutation const &p);
	bool next_perm();
	int get_n() { return n; };
};

#endif // PERMUTATION_HH
