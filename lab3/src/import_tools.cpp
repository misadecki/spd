#include "import_tools.hh"
#include <string>

#define MAX_LEN 128

bool importData(std::string& file_name, std::ostringstream& dest) {
  FILE * file = fopen(file_name.c_str(), "r");
  if(!file) {
    std::cerr << "importData: Error opening file" << std::endl;
    return false;
  }
  std::string word;
  char buf[MAX_LEN];

  while(fgets(buf, MAX_LEN, file)) {
    dest << buf;
  }

  if (fclose(file) != 0) {
    std::cerr << "importData: Error closing file" << std::endl;
    return false;
  }

  return true;
}

/*
 * Parse data from stringstream to vector of tasks.
 * Returns number of tasks
 */
Instance *parse_dataset(std::ostringstream &data) {
	std::istringstream input;
	std::string word;
	int n, m;

	input.str(data.str());
	input >> n;
	input >> m;

	Instance *instance = new Instance(n,m,input);
	return instance;
}
