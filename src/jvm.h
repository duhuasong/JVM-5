#ifndef _JVM_H_
#define _JVM_H_

#include <memory>
#include <string>
#include <vector>

#include "class_loader.h"
#include "utils.h"

class JVM {
 public:
  static constexpr uint8_t kMaxArgNum = 100;

 public:
  explicit JVM(std::string&& cls, std::string&& class_path,
               std::string&& jre_path, std::vector<std::string>&& args);

 public:
  static uint8_t GetVersion() {
    return kVersion;
  }

 void Start();

 private:
  static constexpr uint8_t kVersion = 1;

  std::string cls_;
  std::string class_path_;
  std::string jre_path_;
  std::vector<std::string> args_;

  std::unique_ptr<ClassLoader> class_loader_;

 private:
  DISALLOW_COPY_AND_ASSIGN(JVM);
};

#endif  // _JVM_H_
