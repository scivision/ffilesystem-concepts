#include <iostream>
#include <filesystem>

#include "fs_chdir.h"

namespace fs = std::filesystem;


std::string fs_getcwd(){
  return fs::current_path().generic_string();
}

bool fs_chdir(const char *path){
  std::error_code ec;
  fs::current_path(path, ec);
  if (ec){
    std::cerr << "ERROR:chdir: " << ec.message() << '\n';
    return false;
  }
  return true;
}

void fs_chdir(const std::string& path){
  fs::current_path(path);
}
