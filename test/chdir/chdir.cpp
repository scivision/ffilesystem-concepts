#include <filesystem>
#include <iostream>
#include <cstdlib>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

namespace fs = std::filesystem;

int main(int argc, char* argv[]){
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

  if(argc != 2){
    std::cerr << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  fs::path cp = fs::current_path();
  std::cout << "Current path: " << cp.generic_string() << '\n';

  fs::path dnew(argv[1]);

  if(!fs::exists(dnew)){
    std::cerr << "Error: " << dnew << " does not exist\n";
    return EXIT_FAILURE;
  }
  fs::current_path(dnew);

  std::cout << "New current path: " << fs::current_path().generic_string() << '\n';

  return EXIT_SUCCESS;
}
