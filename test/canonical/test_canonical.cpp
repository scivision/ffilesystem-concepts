#include <iostream>
#include <cstdlib>
#include <string>

#include "canonical.h"


int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  std::string in(argv[1]);

  std::string out = fs_realpath(in);
  if (out.empty()) {
    std::cerr << "Error: " << in << " failed test_link\n";
    return EXIT_FAILURE;
  }

  std::cout << out << '\n';

  return EXIT_SUCCESS;

}
