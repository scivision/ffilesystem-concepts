#include <filesystem>
#include <iterator>

#include "ffilesystem.h"

namespace fs = std::filesystem;


extern "C" size_t path_parts(const char* path, int i, char* buf, size_t buf_size) {
  fs::path p(path);
  // std::cout << "TRACE:init_path: " << p << "\n";

  fs::path::const_iterator it = p.begin();
  std::advance(it, i);

  return fs_str2char((*it).string(), buf, buf_size);
}
