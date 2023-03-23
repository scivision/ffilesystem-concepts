#ifdef __linux__
#define _GNU_SOURCE
#endif

#include <string.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#ifndef MY_DLL_NAME
#define MY_DLL_NAME NULL
#endif
#endif

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(__CYGWIN__)
#include <windows.h>
#elif defined(HAVE_DLADDR)
#include <dlfcn.h>
#endif


size_t get_libpath(char* path)
{

#if defined(_WIN32) || defined(__CYGWIN__)
  if (GetModuleFileName(GetModuleHandle(MY_DLL_NAME), path, MAX_PATH) !=0)
    return strlen(path);
#elif defined(HAVE_DLADDR)
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
