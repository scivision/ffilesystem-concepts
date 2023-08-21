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


extern "C" size_t mkdtemp_f(char* result, size_t buffer_size){
  fs::path tmppath = fs::temp_directory_path() / "tempdir.XXXXXX";

  auto buf = std::make_unique<char[]>(MAX_PATH);
  std::strcpy(buf.get(), tmppath.string().c_str());

  char *tmpdir = mkdtemp(buf.get());
  if (!tmpdir){
    std::cerr << "ERROR:mkdtemp: could not create temporary directory\n";
    return 0;
  }

  std::strcpy(result, buf.get());

  return std::strlen(result);
}
