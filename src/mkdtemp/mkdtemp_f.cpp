#include <memory>  // std::make_unique
#include <filesystem>
#include <cstring>
#include <iostream>

namespace fs = std::filesystem;

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

#ifndef HAVE_MKDTEMP
#include "mkdtemp.h"
#endif

#if __has_include(<unistd.h>)
#include <unistd.h>
#endif

#include "ffilesystem.h"


extern "C" size_t mkdtemp_f(char* result, size_t buffer_size){
  // Fortran / C / C++ interface function
  fs::path tmppath = fs::temp_directory_path() / "tempdir.XXXXXX";

  auto buf = std::make_unique<char[]>(MAX_PATH);
  std::strcpy(buf.get(), tmppath.string().c_str());

  try {
    char *tmpdir = mkdtemp(buf.get());
  } catch (std::runtime_error& e) {
    std::cerr << "ERROR:mkdtemp: " << e.what() << "\n";
    return 0;
  }

  return fs_char2char(buf.get(), result, buffer_size);
}
