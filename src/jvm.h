#ifndef _JVM_H_
#define _JVM_H_

#include <memory>
#include <string>

#include "class_loader.h"
#include "utils.h"

class JVM {
 public:
  static constexpr uint8_t kMaxArgNum = 100;

 public:
  JVM(const std::string& cls) { }

 public:
  static uint8_t GetVersion() {
    return kVersion;
  }

 private:
  static constexpr uint8_t kVersion = 1;

  std::string class_;
  std::string jre_class_path_;
  std::string class_path_;
  std::string args_[kMaxArgNum];

 private:
  DISALLOW_COPY_AND_ASSIGN(JVM);
};

#endif  // _JVM_H_
