#include <iostream>
#include <string>
#include <cstring>
#include <memory>

#ifdef _WIN32
#include <userenv.h>
#else
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <unistd.h>
#endif

std::string fs_homedir() {

  auto r = std::getenv(
#ifdef _WIN32
  "USERPROFILE"
#else
  "HOME"
#endif
  );

  if(r && std::strlen(r) > 0) {
    std::cout << "get_homedir: used env var ";
    return std::string(r);
  }

  std::cout << "get_homedir: using fallback\n";
  std::string homedir;
#ifdef _WIN32
  // works on MSYS2, MSVC, oneAPI.
  DWORD L = MAX_PATH;
  auto buf = std::make_unique<char[]>(L);
  // process with query permission
  HANDLE hToken = 0;
  if(!OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken))
    throw std::runtime_error("OpenProcessToken(GetCurrentProcess): "  + std::system_category().message(GetLastError()));

  bool ok = GetUserProfileDirectoryA(hToken, buf.get(), &L);
  CloseHandle(hToken);
  if (!ok)
    throw std::runtime_error("GetUserProfileDirectory: "  + std::system_category().message(GetLastError()));

  homedir = std::string(buf.get());
#else
  const char *h = getpwuid(geteuid())->pw_dir;
  if (!h)
    throw std::runtime_error("getpwuid: "  + std::system_category().message(errno));
  homedir = std::string(h);
#endif

  std::cout << "get_homedir: used fallback ";
  return homedir;
}

int main() {
  std::cout << fs_homedir() << std::endl;
  return 0;
}
