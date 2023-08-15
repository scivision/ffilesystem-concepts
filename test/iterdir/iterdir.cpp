#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>

namespace fs = std::filesystem;

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

int main(int argc, char* argv[])
{
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

  if (argc == 2 || (argc == 3 && std::string(argv[2]) != "-r")){
    std::cout << "std::filesystem::directory_iterator:\n";
    for (auto const& d : fs::directory_iterator{fs::path(argv[1])})
    {
      if (fs::is_directory(d))
        std::cout << d.path() << "\n";
    }
  }
  else {
    std::cout << "\nstd::filesystem::recursive_directory_iterator:\n";
    for (auto const& d : fs::recursive_directory_iterator{fs::path(argv[1])})
    {
      if (fs::is_directory(d))
        std::cout << d.path() << "\n";
    }
  }

  return EXIT_SUCCESS;
}
