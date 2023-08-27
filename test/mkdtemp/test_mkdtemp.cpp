#include <cstdlib>
#include <iostream>
#include <cstring>
#include <memory> // std::make_unique
#include <stdexcept>

#ifndef HAVE_MKDTEMP
#include "mkdtemp.h"
#endif

#if __has_include(<unistd.h>)
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

  if (std::strlen(tmpdir) == 0){
    std::cerr << "ERROR:test_mkdtemp: temporary directory name empty\n";
    return EXIT_FAILURE;
  }

  std::cout << "temporary directory: " << tmpdir << '\n';

  // cleanup
  std::error_code ec;
  fs::remove(tmpdir, ec);
  if(ec)
    // typically an issue on Windows
    std::cerr << "WARNING:test_mkdtemp: could not remove temporary dir: " << ec.message() << '\n';
  else
    std::cout << "OK: mkdtemp\n";

  return EXIT_SUCCESS;
}
