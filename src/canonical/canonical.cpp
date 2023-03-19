#include <iostream>
#include <cstdlib>
#include <filesystem>

#include "canonical.h"

namespace fs = std::filesystem;

std::string fs_realpath(std::string path)
{
  fs::path in(path);

  if(!fs::exists(in)) {
    std::cerr << "Error: " << in << " does not exist\n";
    return {};
  }

  fs::path out = fs::canonical(in);
#ifdef __MINGW32__
  std::string r = fs_win32_read_symlink(out.string());
  if (r.empty()) {
    std::cerr << "Error: " << out.string() << " failed win32_read_symlink\n";
    return {};
  }

  out = fs::path(r);
#endif

  return out.generic_string();
}


int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  std::string in(argv[1]);

  std::string out = fs_realpath(in);
  if (out.empty()) {
    std::cerr << "Error: " << in << " failed fs_realpath\n";
    return EXIT_FAILURE;
  }

  std::cout << out << '\n';

  return EXIT_SUCCESS;

}
