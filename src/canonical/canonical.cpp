#include <iostream>
#include <cstdlib>
#include <filesystem>

#include "canonical.h"

namespace fs = std::filesystem;

std::string fs_realpath(std::string path)
{
  fs::path in(path);

  bool exists = fs::exists(in);

  fs::path out;
  if(exists){
    out = fs::canonical(in);
  }
  else{
    out = fs::weakly_canonical(in);
  }
#ifdef __MINGW32__
  if(exists){
    std::string r = fs_win32_read_symlink(out.string());
    if (r.empty()) {
      std::cerr << "Error: " << out.string() << " failed win32_read_symlink\n";
      return {};
    }
    out = fs::path(r);
  }
#endif

  return out.generic_string();
}
