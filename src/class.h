#ifndef _CLASS_H_
#define _CLASS_H_

#include <string>
#include <memory>

class Class {
 public:
  Class(std::unique_ptr<char> data) : data_(std::move(data)) { }

 private:
  std::unique_ptr<char> data_;
};

#endif  // _CLASS_H_
