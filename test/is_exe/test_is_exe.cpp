#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

bool fs_is_exe(std::string path)
{

  fs::path p(path);

  if (!fs::is_regular_file(p))
    return false;

  auto s = fs::status(p);

  auto i = s.permissions() & (fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec);
  return i != fs::perms::none;
}

int main(int argc, char** argv)
{

if(argc < 2){
  std::cerr << "Usage: " << argv[0] << " <path>\n";
  return EXIT_FAILURE;
}

std::cout << "is_exe(" << argv[1] << ") = " << fs_is_exe(argv[1]) << '\n';

return EXIT_SUCCESS;
}
