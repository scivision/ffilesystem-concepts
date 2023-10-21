#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <exception>

namespace fs = std::filesystem;

// this example doesn't necessarily work as expected, but was a small example of what one would try.

// Discussion of general issues across operating systems.
// https://github.com/dotnet/runtime/issues/14321

bool is_case_sensitive(std::string drive){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationa

  if (drive.empty())
    throw std::runtime_error("No drive specified.");

  if (!fs::exists(drive))
    throw std::runtime_error(drive + " does not exist.");

  DWORD lpFileSystemFlags=0;

  if(!GetVolumeInformationA(drive.c_str(), 0, 0, 0, 0, &lpFileSystemFlags, 0, 0))
    throw std::runtime_error("GetVolumeInformation: " + drive + " " + std::system_category().message(GetLastError()));

  return bool(FILE_CASE_SENSITIVE_SEARCH & lpFileSystemFlags);
}


int main(int argc, char* argv[]){

  std::string drive;
  if(argc < 2){
    drive = std::getenv("SystemDrive");
  }
  else
    drive = argv[1];

  fs::path p(drive);

  if (!p.has_root_path())
    throw std::runtime_error(drive + " is not a valid path.");

  drive = p.root_name().string();

  if(drive.back() != '\\')
    drive.push_back('\\');

  std::cout << drive << " case sensitive: " << is_case_sensitive(drive) << "\n";

  return EXIT_SUCCESS;
}
