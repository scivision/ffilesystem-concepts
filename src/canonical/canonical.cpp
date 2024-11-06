#include <filesystem>

#include "canonical.h"


std::string fs_realpath(std::string_view path)
{
  const std::filesystem::path in(path);

  const bool exists = std::filesystem::exists(in);

  std::filesystem::path out = std::filesystem::weakly_canonical(in);
#ifdef __MINGW32__
  if(exists)
    out = std::filesystem::path(fs_win32_read_symlink(out.string()));
#endif

  return out.generic_string();
}
