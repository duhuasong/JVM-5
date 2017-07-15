#include "utils.h"

namespace OS {

bool IsFileExistent(const std::string& filename) {
  struct stat status;
  if (stat(filename.c_str(), &status) == 0) {
    return S_ISREG(status.st_mode);
  } else {
    return false;
  }
}

}  // namespace OS

void DumpBinary(const char* data, size_t size) {
  for (int i = 0; i < size; i++) {
    std::cout << std::setfill('0') << std::setw(2) << std::hex;
    std::cout << (data[i] & 0xff);
  }
  std::cout << std::dec << std::endl;
}
