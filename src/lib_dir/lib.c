#ifdef __linux__
#define _GNU_SOURCE
#endif

#include <string.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#ifndef MY_DLL_NAME
#define MY_DLL_NAME NULL
#endif
#elif __has_include(<dlfcn.h>)
#include <dlfcn.h>
#endif


size_t get_libpath(char* path)
{

#if defined(_WIN32) || defined(__CYGWIN__)
  if (GetModuleFileName(GetModuleHandle(MY_DLL_NAME), path, MAX_PATH) !=0){
    // replace \ with /
    for (char* p = path; *p != '\0'; p++) {
      if (*p == '\\')
        *p = '/';
    }
    return strlen(path);
  }
#elif __has_include(<dlfcn.h>)
 Dl_info info;

 if (dladdr(get_libpath, &info))
 {
   strcpy(path, info.dli_fname);
   return strlen(path);
 }
#endif
  return 0;
  // always have a return
}
