#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#ifdef _WIN32
#include <userenv.h> // GetUserProfileDirectoryA
#include <shlobj.h> // SHGetKnownFolderPath
#else
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <unistd.h>
#endif


#ifdef _WIN32
std::string windows_userenv_homedir()
{
  // works on MSYS2, MSVC, oneAPI.
  // must link UserEnv;Advapi32
  DWORD L = MAX_PATH;
  std::vector<char> buf(L);
  // process with query permission
  HANDLE hToken = nullptr;
  bool ok = OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken) != 0 &&
            GetUserProfileDirectoryA(hToken, buf.data(), &L);

  CloseHandle(hToken);
  if (!ok)
    throw std::runtime_error("GetUserProfileDirectory: "  + std::system_category().message(GetLastError()));

  return std::string(buf.data());
}


std::string shlobj_homedir()
{
  #pragma warning( disable : 4244 )
  // works on MSYS2, MSVC, oneAPI.
  // must link Shell32
  wchar_t* buf = nullptr;
  if (SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &buf) != S_OK)
    throw std::runtime_error("SHGetFolderPath: "  + std::system_category().message(GetLastError()));

  // NOTE: lossy conversion, only works for ASCII
  std::wstring w(buf);
  CoTaskMemFree(static_cast<void*>(buf));
  return std::string(w.begin(), w.end());
}
#endif

std::string fs_homedir()
{

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
  return shlobj_homedir();
#else
  if (const char *h = getpwuid(geteuid())->pw_dir; h)
    return std::string(h);

  throw std::runtime_error("getpwuid: "  + std::system_category().message(errno));
#endif

}

int main() {
  std::cout << fs_homedir() << "\n";
  return 0;
}
