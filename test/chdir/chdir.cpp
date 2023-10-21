#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

namespace fs = std::filesystem;

void fs_chdir(const std::string& path){
  fs::current_path(path);
}

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

  fs::path cp = fs::current_path();
  std::cout << "Current path: " << cp.generic_string() << '\n';

  fs_chdir(std::string(argv[1]));

  std::cout << "New current path: " << fs::current_path().generic_string() << '\n';

  return EXIT_SUCCESS;
}
