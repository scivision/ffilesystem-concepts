#ifdef __MINGW32__

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <stdexcept>


std::string fs_win32_read_symlink(const std::string path)
{
  // this resolves Windows symbolic links (reparse points and junctions)
  // it also resolves the case insensitivity of Windows paths to the disk case
  // References:
  // https://stackoverflow.com/a/50182947
  // https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
  // https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfinalpathnamebyhandlea

  HANDLE h = CreateFileA(path.c_str(), 0, 0, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
  if(h == INVALID_HANDLE_VALUE)
    throw std::runtime_error("ERROR:win32_read_symlink:CreateFile open " + path);

  CHAR buf[MAX_PATH];

  DWORD L = GetFinalPathNameByHandleA(h, buf, MAX_PATH, FILE_NAME_NORMALIZED);
  CloseHandle(h);
  if (L == ERROR_PATH_NOT_FOUND)
    throw std::runtime_error("ERROR:win32_read_symlink:GetFinalPathNameByHandle: path not found " + path);
  if (L == ERROR_NOT_ENOUGH_MEMORY)
    throw std::runtime_error("ERROR:win32_read_symlink:GetFinalPathNameByHandle: buffer too small " + path);
  if (L == ERROR_INVALID_PARAMETER)
    throw std::runtime_error("ERROR:win32_read_symlink:GetFinalPathNameByHandle: invalid parameter " + path);
  if (L == 0)
    throw std::runtime_error("ERROR:win32_read_symlink:GetFinalPathNameByHandle: unknown error " + path);

  std::string r(buf);
#ifdef __cpp_lib_starts_ends_with
  if (r.starts_with("\\\\?\\"))
#else
  if (r.substr(0, 4) == "\\\\?\\")
#endif
    r = r.substr(4);

  return r;
}

#endif
