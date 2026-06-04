#ifndef IMPORT_TOOLS_HH
#define IMPORT_TOOLS_HH

#include <sstream>
#include "dataTypes.hh"

bool importData(std::string &fileName, std::ostringstream &dest);
Instance *parse_dataset(std::ostringstream &data);

#endif // IMPORT_TOOLS_HH
