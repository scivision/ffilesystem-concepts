#include <iostream>
#include <cstdlib>
#include <filesystem>

#include "canonical.h"

namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  fs::path in(argv[1]);

  if(!fs::exists(in)) {
    std::cerr << "Error: " << in << " does not exist\n";
    return EXIT_FAILURE;
  }

  fs::path out = fs::canonical(in);
#ifdef __MINGW32__
  std::string r = fs_win32_read_symlink(out.string());
  if (r.empty()) {
    std::cerr << "Error: " << out.string() << " failed win32_read_symlink\n";
    return EXIT_FAILURE;
  }

  out = fs::path(r);
#endif

  std::cout << out.generic_string() << '\n';

  return EXIT_SUCCESS;

}
