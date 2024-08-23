// Find all files with name under path
// Usage: test_find_file <filename> [search_path] [count]
// filename: name of the file to find
// search_path: path to search recursively under, default is current directory
// count: maximum number of files to find, default is 0 (find all)
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

if(argc < 2)
{
    std::cerr << "Usage: " << argv[0] << " <filename> [search_path] [count]\n";
    return EXIT_FAILURE;
}

std::string_view name = argv[1];

std::string p = ".";
if (argc > 2)
    p = argv[2];

size_t count = 0;
if (argc > 3)
    count = std::stoi(argv[3]);

fs::path path = fs::weakly_canonical(p);

if(!fs::is_directory(path))
{
    std::cerr << "Error: " << path << " is not a directory\n";
    return EXIT_FAILURE;
}

size_t N = 0;
for (auto const& d : fs::recursive_directory_iterator{path})
{
    if (d.path().filename() == name && fs::is_regular_file(d)){
      std::cout << fs::canonical(d.path()).generic_string() << "\n";
      N++;
      if(N == count)
        break;
    }
}

if(N == 0){
  std::cerr << name << " not found under " << path << "\n";
  return EXIT_FAILURE;
}

return EXIT_SUCCESS;
}
