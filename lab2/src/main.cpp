#include "import_tools.hh"
#include "dataTypes.hh"
#include "problem.hh"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

int main(int argc, char *argv[]) {
    std::ostringstream dane;
    std::string file(argv[1]);
    importData(file, dane);
    Instance *i = parse_dataset(dane);
    i->print();
    Problem problem(*i, i->n);

    if(argc < 3){
	    std::cout << "Usage: " << argv[0] << " <plik_testowy>" << " <_ |brute|johnson|neh| _ | _>"<< std::endl;
	    return 0;
    }
    if(!strcmp(argv[2], "own")) {
    	//problem.own_algorithm();
    } else if (!strcmp(argv[2], "brute")) {
    	problem.brute_force();
    } else if (!strcmp(argv[2], "johnson")) {
    	problem.johnson();
    } else if (!strcmp(argv[2], "neh")) {
	problem.NEH();
    } else if (!strcmp(argv[2], "schrage")) {
   	//problem.Schrage();
    } else if (!strcmp(argv[2], "p_schrage")) {
    	//problem.Schrage_preemptive();
    }
    std::cout << argv[1] << std::endl;

    return 0;
}
