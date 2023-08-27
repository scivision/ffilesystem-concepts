#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>

#include <filesystem>

namespace fs = std::filesystem;

#include "mkdtemp.h"

#ifdef _MSC_VER
#include <crtdbg.h>
#endif


int main(){
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

  fs::path tempdir(fs_make_tempdir("tempdir."));

  if(!fs::is_directory(tempdir))
    throw fs::filesystem_error("fs_make_tempdir: temporary directory does not exist", tempdir, std::error_code(errno, std::system_category()));

  std::cout << "temporary directory: " << tempdir << '\n';

  fs::path t2 = tempdir / "test_dir";

  if(!fs::create_directory(t2))
     throw fs::filesystem_error("fs_make_tempdir:mkdir: could not create new directory", t2, std::error_code(errno, std::system_category()));

  // cleanup
  try {
    fs::remove_all(tempdir);
    std::cout << "OK: fs_make_tempdir\n";
  } catch (fs::filesystem_error& e) {
    // typically an issue on Windows
    std::cerr << "WARNING:test_fs_make_tempdir: could not remove temporary dir: " << e.what() << '\n';
  }

  return EXIT_SUCCESS;
}
