#if defined(__linux__) && !defined(_GNU_SOURCE)
#  define _GNU_SOURCE
#endif

#include <string_view>
#include <iostream>
#include <cstdlib>
#include <system_error>

#if __has_include(<filesystem>)
#  include <filesystem>
#endif

// preferred import order for stat()
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>   // AT_* constants for statx()

#include <chrono>


bool
fs_is_dir(std::string_view path)
{
// NOTE: Windows top-level drive "C:" needs a trailing slash "C:/"
  std::error_code ec;
#ifdef __cpp_lib_filesystem
  return std::filesystem::is_directory(path, ec) && !ec;
#else
  return false;
#endif
}


bool
stat_is_dir(std::string_view path)
{
  struct stat s;
  return stat(path.data(), &s) == 0 && s.st_mode & S_IFDIR;
  // S_ISDIR not available with MSVC
}


bool
statx_is_dir(std::string_view path)
{
// Linux Glibc only
// https://www.gnu.org/software/gnulib/manual/html_node/statx.html
// https://www.man7.org/linux/man-pages/man2/statx.2.html
#ifdef STATX_MODE
  struct statx s;
  return statx(AT_FDCWD, path.data(), AT_NO_AUTOMOUNT, STATX_MODE, &s) == 0 &&
      s.stx_mode & S_IFDIR;
#else
  return false;
#endif
}


int main(int argc, char** argv){

  std::string path = argc > 1 ? argv[1] : ".";
  size_t n = argc > 2 ? std::atoi(argv[2]) : 1000;

  auto t0 = std::chrono::steady_clock::now();
    for(size_t i = 0; i < n; ++i){
        fs_is_dir(path);
    }
  auto t1 = std::chrono::steady_clock::now();

  auto tfs = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

  std::cout << n << " <filesystem> is_dir(" << path << ") " << tfs << " us\n";

  t0 = std::chrono::steady_clock::now();
    for(size_t i = 0; i < n; ++i){
        stat_is_dir(path);
    }
  t1 = std::chrono::steady_clock::now();

  auto tstat = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

  std::cout << n << " stat() is_dir(" << path << ") " << tstat << " us\n";

#ifdef STATX_MODE

  t0 = std::chrono::steady_clock::now();
    for(size_t i = 0; i < n; ++i){
        statx_is_dir(path);
    }
  t1 = std::chrono::steady_clock::now();

  auto tstatx = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

  std::cout << n << " statx() is_dir(" << path << ") " << tstatx << " us\n";
#endif

return EXIT_SUCCESS;
}
