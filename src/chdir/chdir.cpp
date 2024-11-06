#include <iostream>
#include <string_view>
#include <filesystem>

#include "fs_chdir.h"
#include "ffilesystem.h"

namespace fs = std::filesystem;


size_t fs_get_cwd(char * path, size_t buffer_size)
{
  return fs_str2char(fs_get_cwd(), path, buffer_size);
}

std::string fs_get_cwd()
{
  return fs::current_path().generic_string();
}


bool fs_chdir(const char *path)
{
  std::error_code ec;
  fs::current_path(path, ec);
  if (ec){
    std::cerr << "ERROR:chdir: " << ec.message() << '\n';
    return false;
  }
  return true;
}

void fs_chdir(std::string_view path)
{
  fs::current_path(path);
}
