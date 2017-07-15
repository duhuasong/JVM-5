#include "jvm.h"

static void PrintUsage() {
  std::cout << "./jvm -Xjre JRE_PATH -cp CLASS_PATH CLASS ARG0 ARG1 ...\n";
  return;
}

static bool CheckEnvs(const std::string& jre_path,
                      const std::string& class_path,
                      const std::string& cls) {
  if (jre_path.empty() || class_path.empty() || cls.empty()) {
    PrintUsage();
    return false;
  }
  return true;
}

static bool ParseCmd(int argc, char* argv[], std::string& cls,
                     std::string& class_path, std::string& jre_path,
                     std::vector<std::string>& args) {
  const uint8_t kOptionLoc = 1;

  if ((argc < 2) ||
      (std::strcmp(argv[kOptionLoc], "-h") == 0) ||
      (std::strcmp(argv[kOptionLoc], "-help") == 0)) {
    PrintUsage();
    return false;
  }

  if ((std::strcmp(argv[kOptionLoc], "-v") == 0) ||
      (std::strcmp(argv[kOptionLoc], "-version") == 0)) {
    std::cout << "Version: " << JVM::GetVersion() << std::endl;
    return false;
  }

  int cmd_loc;
  for (cmd_loc = kOptionLoc; cmd_loc < argc; cmd_loc++) {
    if (std::strcmp(argv[cmd_loc], "-cp") == 0) {
      class_path = argv[++cmd_loc];
    } else if (std::strcmp(argv[cmd_loc], "-Xjre") == 0) {
      jre_path = argv[++cmd_loc];
    } else {
      cls = argv[cmd_loc++];
      break;
    }
  }

  for (int j = 0; cmd_loc < argc; cmd_loc++, j++) {
    args.push_back(argv[cmd_loc]);
  }
  return true;
}

JVM::JVM(std::string&& cls, std::string&& class_path, std::string&& jre_path,
         std::vector<std::string>&& args) :
    cls_(cls), class_path_(class_path), jre_path_(jre_path), args_(args),
    class_loader_(new ClassLoader(jre_path_, class_path_))
 { }

void JVM::Start() {
  const Class* cls = class_loader_->FindClass(cls_);
  if (cls == nullptr) {
#if JVM_DEBUG
    std::cerr << "JVM::Start cannot find " << cls_ << std::endl;
#endif
  }

  // Execute.
  return;
}

int main(int argc, char* argv[]) {
  std::string cls;
  std::string class_path;
  std::string jre_path;
  std::vector<std::string> args;

  if (!ParseCmd(argc, argv, cls, class_path, jre_path, args)) {
    return 0;
  }

  if (!CheckEnvs(jre_path, class_path, cls)) {
    return 0;
  }

#ifdef JVM_DEBUG
  std::cout << "Start JVM: jre_path=" << jre_path << ", class_path="
            << class_path << ", class=" << cls;
  std::cout << ", args=[";
  for (std::string arg : args) {
    std::cout << arg << " ";
  }
  std::cout << "]" << std::endl;
#endif

  // new JVM and start.
  JVM jvm(std::move(cls), std::move(class_path), std::move(jre_path),
          std::move(args));
  jvm.Start();

  return 1;
}
