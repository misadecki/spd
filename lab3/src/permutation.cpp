#include "permutation.hh"


std::ostream &operator<<(std::ostream &stream, Permutation const &p){
	stream << "[";
	for(int i : p.perm){
		stream << i << ", ";
	}
	stream << "]" << std::endl;
	return stream;
};

bool Permutation::next_perm(){
	for(int i=0; i<n; ++i){
		if(perm[i] == 0){
			perm[i] = 1;
			return true;
		} else {
			perm[i] = 0;
		}
	}
	return false;
};
