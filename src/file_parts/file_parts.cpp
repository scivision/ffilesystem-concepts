#include <filesystem>
#include <iostream>
#include <cstring>
#include <iterator>

namespace fs = std::filesystem;


size_t fs_str2char(std::string s, char* result, size_t buffer_size)
{
  // string to char*, for Fortran interface
  if(s.length() >= buffer_size){
    result = nullptr;
    std::cerr << "ERROR:ffilesystem: output buffer too small for string: " << s << "\n";
    return 0;
  }

  std::strcpy(result, s.data());
  return std::strlen(result);
}


extern "C" size_t path_parts(const char* path, int i, char* buf, size_t buf_size) {
  fs::path p(path);
  // std::cout << "TRACE:init_path: " << p << "\n";

  fs::path::const_iterator it = p.begin();
  std::advance(it, i);

  return fs_str2char((*it).string(), buf, buf_size);
}
