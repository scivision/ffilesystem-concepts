#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#if __has_include(<atlcore.h>)
#include <atlcore.h>
#endif
#endif

#include <iostream>
#include <cstdlib>

bool long_paths_enabled() {

#ifdef _WIN32
#if __has_include(<atlcore.h>)
// https://github.com/ninja-build/ninja/commit/eddafdd7e733241f92900035953f6bcf7c7677e3
  IFDYNAMICGETCACHEDFUNCTIONTYPEDEF(L"ntdll", BOOLEAN(WINAPI*)(), "RtlAreLongPathsEnabled", RtlAreLongPathsEnabled)
    returnRtlAreLongPathsEnabled();
#else
  // Probe ntdll.dll for RtlAreLongPathsEnabled, and call it if it exists.
  HINSTANCE ntdll_lib = ::GetModuleHandleW(L"ntdll");
  if (ntdll_lib) {
    typedef BOOLEAN(WINAPI FunctionType)();
    auto* func_ptr = reinterpret_cast<FunctionType*>(
        ::GetProcAddress(ntdll_lib, "RtlAreLongPathsEnabled"));
    if (func_ptr) {
      std::cout << "RtlAreLongPathsEnabled found\n";
      return (*func_ptr)();
    }
  }
  return false;

#endif
#else
return true;
#endif

}

int main() {
  auto e = long_paths_enabled();
  std::cout << "Windows long paths enabled: " << e << "\n";
#ifdef _WIN32
  std::cout << "MAX_PATH: " << MAX_PATH << "\n";
#endif
  return EXIT_SUCCESS;
}
