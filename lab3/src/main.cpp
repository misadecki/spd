#include "import_tools.hh"
#include "instance.hh"
#include "problem.hh"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]) {
    if(argc < 3){
	    std::cout << "Usage: " << argv[0] << " <plik_testowy>" << " <brute|LSA|LPT|PD|PTAS|FPTAS>"<< std::endl;
	    return 0;
    }
    std::ostringstream dane;
    std::string file(argv[1]);
    importData(file, dane);
    Instance *i = parse_dataset(dane);
    //i->print();
    Problem problem(*i, i->n, 2, 2);

    if (!strcmp(argv[2], "brute")) {
    	problem.brute_force(i->pj, i->n);
    } else if (!strcmp(argv[2], "LSA")) {
    	problem.LSA();
    } else if (!strcmp(argv[2], "LPT")) {
	problem.LPT();
    } else if (!strcmp(argv[2], "PD")) {
   	problem.PD();
    } else if (!strcmp(argv[2], "PTAS")) {
    	problem.PTAS();
    } else if (!strcmp(argv[2], "FPTAS")) {
    	problem.FPTAS();
    }
    std::cout << argv[1] << std::endl;

    return 0;
}
