#include <fstream>
#include <sstream>

#include "class.h"
#include "class_loader.h"

static Class* ReadClassFile(const std::string& filename) {
  constexpr const char* CLASS_EXT = ".class";
  const std::string full_name(filename + CLASS_EXT);

  if (!OS::IsFileExistent(full_name)) {
#ifdef JVM_DEBUG
    std::cout << "ReadClassFile: " << full_name << " is not existent\n.";
#endif
    return nullptr;
  }

  // Use ate in order to get the file size;
  std::ifstream input(full_name, std::ifstream::ate | std::ifstream::binary);
  if (!input) {
    std::cerr << "Open " << full_name << " fails\n";
    return nullptr;
  }

  size_t size = input.tellg();
  input.seekg(std::ios_base::beg);

  std::unique_ptr<char> data(new char[size]);
  input.read(data.get(), size);

#ifdef JVM_DEBUG
  std::cout << "Read " << full_name << ", size=" << size << "\nData=";
  DumpBinary(data.get(), size);
#endif
  return new Class(std::move(data));
}

const Class* DirectoryEntry::ReadClass(const std::string& class_name) {
  const std::string full_name(path_ + "/" + class_name);
  return ReadClassFile(full_name);
}

const Class* ClassLoader::FindClass(const std::string& class_name) {
  // Find the class_map_ at first.
  auto iter = class_map_.find(class_name);
  if (iter != class_map_.end()) {
    return iter->second;
  }

  // Read class file if nothing found.
  // TODO: Read from jre_entry_ first.
  const Class* cls = user_class_entry_->ReadClass(class_name);

  if (cls != nullptr) {
    class_map_.emplace(std::make_pair(class_name, cls));
#ifdef JVM_DEBUG
    std::cout << "ClassLoader::FindClass: Add " << class_name << " into class_map_.\n";
#endif
    return cls;
  }
  std::cerr << "Cannot load " << class_name << std::endl;
  return nullptr;
}
