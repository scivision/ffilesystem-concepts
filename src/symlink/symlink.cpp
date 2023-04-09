#include <stdexcept>
#include <iostream>

#ifdef __MINGW32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <system_error>
#endif

#include "canonical.h"
#include "symlink.h"


void fs_create_symlink(const fs::path tgt, const fs::path lnk)
{
#ifdef __MINGW32__
  auto p = SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;
  if(fs::is_directory(tgt))
    p |= SYMBOLIC_LINK_FLAG_DIRECTORY;

  if(CreateSymbolicLink(lnk.string().c_str(), tgt.string().c_str(), p))
    return;

  DWORD err = GetLastError();
  std::string message = std::system_category().message(err);
  std::cerr << "ERROR:CreateSymbolicLink: " << err << ": " << message << "\n";
  if(err == ERROR_PRIVILEGE_NOT_HELD)
    throw std::runtime_error(R"(Enable Windows developer mode to use symbolic links:
    https://learn.microsoft.com/en-us/windows/apps/get-started/developer-mode-features-and-debugging)");
  throw std::system_error(err, std::system_category(), "CreateSymbolicLink");
#endif

  fs::is_directory(tgt)
    ? fs::create_directory_symlink(tgt, lnk)
    : fs::create_symlink(tgt, lnk);
}


bool fs_exists(const fs::path path)
{
  std::error_code ec;

  auto s = fs::status(path, ec);
  if(s.type() != fs::file_type::not_found){
    if(ec) {
      std::cerr << "ERROR:ffilesystem:exist:status: " << ec.message() << ": " << path << "\n";
      return false;
    }
  }
  return fs::exists(path);
}

bool fs_is_symlink(const fs::path path)
{

// auto s = fs::status(lnk);
// bug: doesn't work for symlinks on Windows

  if (!fs_exists(path))
    return false;

#ifdef __MINGW32__
  DWORD a = GetFileAttributes(path.string().c_str());
  if(a == INVALID_FILE_ATTRIBUTES)
    return false;
  return a & FILE_ATTRIBUTE_REPARSE_POINT;
#endif
  return fs::is_symlink(path);
}


fs::path fs_read_symlink(const fs::path path)
{
#ifdef __MINGW32__
  return fs::path(fs_win32_read_symlink(path.string()));
  // on MinGW, canonical doesn't work for symlinks
  // return fs::canonical(path);
#endif
  // canonical also resolves symlinks, but here we check that read_symlink works
  return fs::read_symlink(path);
}
