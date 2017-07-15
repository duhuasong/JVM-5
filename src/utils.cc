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
