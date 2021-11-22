#include "cpu/o3/special_inst.hh"

#include "base/trace.hh"
#include "debug/ReadingPCFile.hh"

namespace gem5 {
namespace o3 {

void PCList::addPCToList(unsigned int pc) {
  pcs.push_back(pc);
  count++;
}
void PCList::readPCListFromFile(std::string filename) {
  // file format each line contains one valid PC
  std::ifstream ifs(filename);
  assert(ifs.is_open() && "Cannot open PC List File");
  // unsigned int line;
  this->setFileName(filename);
  addPCToList(1234);
  // char *p ;
  unsigned int pc;
  while (ifs >> std::hex >> pc) {
    this->addPCToList(pc);
    // unsigned int pc = strtol( line.c_str(), &p, 16 );
    // assert(*p==0 && "not a valid input");
    // DPRINTF(ReadingPCFile, "Reading PC from File\n");
    // this->addPCToList(pc);
  }
}
}  // namespace o3
}  // namespace gem5
