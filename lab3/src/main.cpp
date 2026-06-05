#include "import_tools.hh"
#include "instance.hh"
#include "problem.hh"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

int main(int argc, char *argv[]) {
    if(argc < 3){
	    std::cout << "Usage: " << argv[0] << " <plik_testowy>" << " <brute|johnson|neh|fneh|bnb>"<< std::endl;
	    return 0;
    }
    std::ostringstream dane;
    std::string file(argv[1]);
    importData(file, dane);
    Instance *i = parse_dataset(dane);
    //i->print();
    Problem problem(*i, i->n);

    if (!strcmp(argv[2], "brute")) {
    	problem.brute_force();
    } else if (!strcmp(argv[2], "johnson")) {
    	problem.johnson();
    } else if (!strcmp(argv[2], "neh")) {
	problem.NEH();
    } else if (!strcmp(argv[2], "fneh")) {
   	problem.FNEH();
    } else if (!strcmp(argv[2], "bnb")) {
    	problem.branch_and_bound();
    }
    std::cout << argv[1] << std::endl;

    return 0;
}
