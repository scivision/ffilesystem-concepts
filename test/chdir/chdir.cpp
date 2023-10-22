#include <iostream>
#include <cstdlib>
#include <exception>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#include "fs_chdir.h"


int main(int argc, char* argv[]){
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

  if(argc != 2)
    throw std::runtime_error("Usage: " + std::string(argv[0]) + " <path>");

  std::cout << "Current path: " << fs_get_cwd() << '\n';

  fs_chdir(std::string(argv[1]));

  std::cout << "New current path: " << fs_get_cwd() << '\n';

  return EXIT_SUCCESS;
}
