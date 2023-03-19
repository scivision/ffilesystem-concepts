// https://man7.org/linux/man-pages/man3/realpath.3.html
// https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/realpath.3.html
// https://linux.die.net/man/3/realpath
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fullpath-wfullpath?view=msvc-170

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "canonical.h"


size_t fs_realpath(const char* path, char* r, size_t buffer_size)
{

#ifdef _MSC_VER
  if (_access_s(path, 0) != 0){
    fprintf(stderr, "ERROR: path does not exist: %s\n", path);
    return 0;
  }
#else
  // <unistd.h>
  if (access(path, F_OK) != 0){
    fprintf(stderr, "ERROR: path does not exist: %s\n", path);
    return 0;
  };
#endif

  char* t;
#ifdef _WIN32
  t = _fullpath(r, path, buffer_size);
  if(t)
    fs_win32_read_symlink(t, r, buffer_size);
#else
  t = realpath(path, r);
#endif

  if(!t){
    printf("Error: realpath: %s\n", strerror(errno));
    return 0;
  }

  return strlen(r);
}
