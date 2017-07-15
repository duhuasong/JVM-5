#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <iomanip>
#include <sys/stat.h>

#define DISALLOW_COPY_AND_ASSIGN(Class)     \
 private:                                   \
  Class(const Class &) = delete;            \
  Class& operator=(const Class&) = delete;  \

namespace OS {

bool IsFileExistent(const std::string& filename);

}  // namespace OS

void DumpBinary(const char* data, size_t size);

#endif  // _UTILS_H_
