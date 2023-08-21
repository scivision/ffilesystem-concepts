#include <cstdlib>
#include <iostream>
#include <cstring>

#ifndef HAVE_MKDTEMP
#include "mkdtemp.h"
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

#include <filesystem>

namespace fs = std::filesystem;


int main(){

  fs::path tmppath = fs::temp_directory_path() / "tempdir.XXXXXX";

  auto buf = std::make_unique<char[]>(MAX_PATH);
  std::strcpy(buf.get(), tmppath.string().c_str());

  char *tmpdir = mkdtemp(buf.get());

  if (!tmpdir){
    std::cerr << "ERROR:mkdtemp: could not create temporary directory\n";
    return EXIT_FAILURE;
  }

  std::cout << "temporary directory: " << tmpdir << '\n';

  // cleanup
  fs::remove_all(tmpdir);

  std::cout << "OK: mkdtemp\n";

  return EXIT_SUCCESS;
}
