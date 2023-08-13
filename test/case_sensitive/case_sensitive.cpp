#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

// this example doesn't necessarily work as expected, but was a small example of what one would try.

// Discussion of general issues across operating systems.
// https://github.com/dotnet/runtime/issues/14321

int is_case_sensitive(std::string drive){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationa

  if (drive.empty()){
    std::cerr << "ERROR: No drive specified.\n";
    return EXIT_FAILURE;
  }

  if (!fs::exists(drive)){
    std::cerr << "ERROR: " << drive << " does not exist.\n";
   return -1;
  }

  DWORD lpFileSystemFlags=0;

  if(!GetVolumeInformationA(drive.c_str(), 0, 0, 0, 0, &lpFileSystemFlags, 0, 0)){
    DWORD err = GetLastError();
    std::cerr << "ERROR:GetVolumeInformation: " << drive << " " << err << ": " << std::system_category().message(err) << "\n";
    return -1;
  }

  bool case_sense = FILE_CASE_SENSITIVE_SEARCH & lpFileSystemFlags;

  return case_sense;
}


int main(int argc, char* argv[]){

  std::string drive;
  if(argc < 2){
    drive = std::getenv("SystemDrive");
  }
  else
    drive = argv[1];

  fs::path p(drive);

  if (!p.has_root_path()){
    std::cerr << "ERROR: " << drive << " is not a valid path.\n";
    return EXIT_FAILURE;
  }

  drive = p.root_name().string();

  if(drive.back() != '\\')
    drive.push_back('\\');

  int case_sens = is_case_sensitive(drive);
  if (case_sens < 0)
    return EXIT_FAILURE;

  std::cout << drive << " case sensitive: " << bool(case_sens) << "\n";

  return EXIT_SUCCESS;
}
