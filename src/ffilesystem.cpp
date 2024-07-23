#include <iostream>
#include <cstring>

#include "ffilesystem.h"


size_t fs_char2char(const char* in, char* out, size_t buffer_size)
{
  // string to char*, for Fortran interface
  if(std::strlen(in) >= buffer_size){
    out = nullptr;
    std::cerr << "ERROR:ffilesystem: output buffer too small: " << in << "\n";
    return 0;
  }

  std::strcpy(out, in);
  return std::strlen(out);
}


size_t fs_str2char(std::string_view in, char* out, size_t buffer_size)
{
  // string to char*, for Fortran interface
  if(in.length() >= buffer_size){
    out = nullptr;
    std::cerr << "ERROR:ffilesystem: output buffer too small: " << in << "\n";
    return 0;
  }

  std::strcpy(out, in.data());
  return std::strlen(out);
}
