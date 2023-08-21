#include <cstdlib>
#include <filesystem>

#include "canonical.h"

namespace fs = std::filesystem;

std::string fs_realpath(const std::string path)
{
  fs::path in(path);

  bool exists = fs::exists(in);

  fs::path out = exists ? fs::canonical(in) : fs::weakly_canonical(in);
#ifdef __MINGW32__
  if(exists)
    out = fs::path(fs_win32_read_symlink(out.string()));
#endif

  return out.generic_string();
}
