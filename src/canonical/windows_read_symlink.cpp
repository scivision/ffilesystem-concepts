#ifdef __MINGW32__

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <iostream>


std::string fs_win32_read_symlink(std::string_view path)
{
  // this resolves Windows symbolic links (reparse points and junctions)
  // it also resolves the case insensitivity of Windows paths to the disk case
  // References:
  // https://stackoverflow.com/a/50182947
  // https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
  // https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfinalpathnamebyhandlea

  HANDLE h = CreateFileA(path.data(), 0, 0, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
  if(h == INVALID_HANDLE_VALUE){
    std::cerr << "ERROR:win32_read_symlink:CreateFile open\n";
    return {};
  }

  std::string r(MAX_PATH, '\0');

  DWORD L = GetFinalPathNameByHandleA(h, r.data(), r.size(), FILE_NAME_NORMALIZED);
  CloseHandle(h);

  switch (L) {
    case ERROR_PATH_NOT_FOUND:
      std::cerr << "ERROR:win32_read_symlink:GetFinalPathNameByHandle: path not found\n";
    case ERROR_NOT_ENOUGH_MEMORY:
      std::cerr << "ERROR:win32_read_symlink:GetFinalPathNameByHandle: buffer too small\n";
    case ERROR_INVALID_PARAMETER:
      std::cerr << "ERROR:win32_read_symlink:GetFinalPathNameByHandle: invalid parameter\n";
    case 0:
      std::cerr << "ERROR:win32_read_symlink:GetFinalPathNameByHandle: unknown error\n";
  }
  if(L < 1)
    return {};

  r.resize(L);

#ifdef __cpp_lib_starts_ends_with
  if (r.starts_with("\\\\?\\"))
#else
  if (r.substr(0, 4) == "\\\\?\\")
#endif
    r = r.substr(4);

  return r;
}

#endif
