#include "filesystem_type.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]){

  std::string p;
  p = (argc < 2) ? "." : argv[1];

  if(std::string name = fs_filesystem_type(p); !name.empty()){
    std::cout << "Filesystem type: " << name << "\n";
    return EXIT_SUCCESS;
  }

  std::cerr << "Could not determine filesystem type" << "\n";

  return EXIT_SUCCESS;
}
