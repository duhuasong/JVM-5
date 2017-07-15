#ifndef _CLASS_LOADER_H_
#define _CLASS_LOADER_H_

#include <string>
#include <map>

#include "utils.h"

class Class;

class ClassEntry {
 public:
  ClassEntry(const std::string& path) : path_(path) { }

 public:
  virtual const Class* ReadClass(const std::string& class_name) = 0;

 protected:
  const std::string path_;
};

class DirectoryEntry : public ClassEntry {
 public:
  DirectoryEntry(const std::string& path) : ClassEntry(path) { }

 public:
  const Class* ReadClass(const std::string& class_name);

 private:
  DISALLOW_COPY_AND_ASSIGN(DirectoryEntry);
};

class ClassLoader {
 public:
  // Initialize the class entries..
  ClassLoader(const std::string& jre_class_path,
              const std::string& class_path) :
      jre_entry_(nullptr), user_class_entry_(new DirectoryEntry(class_path)) {
  }

 public:
  // Find class from class_map_ first, read class file if nothing found.
  const Class* FindClass(const std::string& class_name);

 private:
  std::unique_ptr<ClassEntry> jre_entry_;
  std::unique_ptr<ClassEntry> user_class_entry_;

 private:
  typedef std::map<const std::string, const Class*> MapFromNameToClass;
  // Map from class name to Class object
  MapFromNameToClass class_map_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ClassLoader);
};

#endif  // _CLASS_LOADER_H_
