#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>

size_t get_max_path_components(std::string drive){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getvolumeinformationa
// https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=powershell

DWORD lpMaximumComponentLength = 0;

if(!GetVolumeInformationA(drive.c_str(), 0, 0, 0, &lpMaximumComponentLength, 0, 0, 0))
  throw std::runtime_error("GetVolumeInformation: " + drive + " " + std::system_category().message(GetLastError()));

return lpMaximumComponentLength;
}


int main(int argc, char* argv[]){

  std::string drive;
  if(argc < 2){
    drive = std::getenv("SystemDrive");
    drive += "\\";
  }
  else
    drive = argv[1];

  size_t maxcomp = get_max_path_components(drive);

  std::cout << drive << " max_path_components: " << maxcomp << "\n";

  return EXIT_SUCCESS;
}
