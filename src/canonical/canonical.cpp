#include <iostream>
#include <cstdlib>
#include <filesystem>

#include "canonical.h"

namespace fs = std::filesystem;

std::string fs_realpath(std::string path)
{
  fs::path in(path);

  if(!fs::exists(in)) {
    std::cerr << "Error: " << in << " does not exist\n";
    return {};
  }

  fs::path out = fs::canonical(in);
#ifdef __MINGW32__
  std::string r = fs_win32_read_symlink(out.string());
  if (r.empty()) {
    std::cerr << "Error: " << out.string() << " failed win32_read_symlink\n";
    return {};
  }

  out = fs::path(r);
#endif

  return out.generic_string();
}
