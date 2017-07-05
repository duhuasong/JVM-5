#ifndef _UTILS_H_
#define _UTILS_H_

#define DISALLOW_COPY_AND_ASSIGN(Class)     \
 private:                                   \
  Class(const Class &) = delete;            \
  Class& operator=(const Class&) = delete;  \

#endif  // _UTILS_H_
