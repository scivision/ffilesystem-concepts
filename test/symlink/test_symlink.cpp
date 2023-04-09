// Check that filesystem is capable of symbolic links with this compiler.

#include <iostream>
#include <cstdlib>

#include "symlink.h"

#ifdef _MSC_VER
#include <crtdbg.h>
#endif


int main(int argc, char **argv){

#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

auto tgt_f = fs::canonical(argv[0]);
auto tgt_d = tgt_f.parent_path();

if(!fs::is_regular_file(tgt_f))
  throw std::runtime_error("target file " + tgt_f.string() + " is not a regular file");
if(!fs::is_directory(tgt_d))
  throw std::runtime_error("target directory " + tgt_d.string() + " is not a directory");

// MSVC-like fails if the symlink already exists
auto lnk_f = tgt_d / "file.lnk";
if (fs_exists(lnk_f))
  fs::remove(lnk_f);
fs_create_symlink(tgt_f, lnk_f);

auto lnk_d = tgt_d / "dir.lnk";
if (fs_exists(lnk_d))
  fs::remove(lnk_d);
fs_create_symlink(tgt_d, lnk_d);

if(!fs_is_symlink(lnk_f))
  fs::is_regular_file(lnk_f)
  ? throw std::runtime_error(lnk_f.string() + " detected as regular file instead of symlink")
  : throw std::runtime_error(lnk_f.string() + " is not a symlink");
if(fs_is_symlink(tgt_f))
  throw std::runtime_error(tgt_f.string() + " detected as symlink instead of regular file");

if(!fs_is_symlink(lnk_d))
  fs::is_directory(lnk_d)
  ? throw std::runtime_error(lnk_d.string() + " detected as directory instead of symlink")
  : throw std::runtime_error(lnk_d.string() + " is not a symlink");
if(fs_is_symlink(tgt_d))
  throw std::runtime_error(tgt_d.string() + " detected as symlink instead of directory");

auto f = fs_read_symlink(lnk_f);
auto d = fs_read_symlink(lnk_d);
if (f != tgt_f)
  throw std::runtime_error("FILE: " + lnk_f.string() + " is a symlink to " + f.string() + " instead of " + tgt_f.string());
if (d != tgt_d)
  throw std::runtime_error("DIRECTORY: " + lnk_d.string() + " is a symlink to " + d.string() + " instead of " + tgt_d.string());

std::cout << "OK: " << lnk_f << " symlink to FILE " << tgt_f << "\n";
std::cout << "OK: " << lnk_d << " symlink to DIRECTORY " << tgt_d << "\n";

return EXIT_SUCCESS;
}
