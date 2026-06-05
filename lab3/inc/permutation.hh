#ifndef PERMUTATION_HH
#define PERMUTATION_HH
#include <algorithm>
#include <vector>
#include <ostream>

class Permutation {
	int n = 0;
public:
	std::vector<int> perm;
	Permutation(){ perm = {0};};
	Permutation(int n_tasks) : n(n_tasks){
		perm.resize(n);
		for(int i=0; i<n; ++i){
			perm[i] = i;
		}
	};
	
	int operator[](int idx) { return perm[idx];}
	int operator==(const Permutation &other) {return perm == other.perm;}
	void operator=(const Permutation &other) {perm = other.perm;}
	friend std::ostream &operator<<(std::ostream &stream, Permutation const &p){
		stream << "[";
		for(int i : p.perm){
			stream << i << ", ";
		}
		stream << "]" << std::endl;
		return stream;
	};

	bool next_perm() {return std::next_permutation(perm.begin(), perm.end());};
	int get_n() {return n;}
};

#endif // PERMUTATION_HH
