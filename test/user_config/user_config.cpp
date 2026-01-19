#include <string>

#include "ffilesystem.h" // for fs_getenv

// on Windows, need to link
// Ole32: CoTaskMemFree
// Shell32: SHGetKnownFolderPath
// uuid: FOLDERID_LocalAppData



#if defined(_WIN32)
#include <Objbase.h> // IWYU pragma: keep   for CoTaskMemFree
#include <KnownFolders.h> // for FOLDERID_LocalAppData
#include <shlobj.h> // for SHGetKnownFolderPath
#endif

std::string fs_user_config_dir()
{
#if defined(_WIN32)
  // https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
  // https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-cotaskmemfree

  PWSTR s = nullptr;
  HRESULT ok = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &s);

  CoTaskMemFree(s);

  if (ok == S_OK && !s.empty())
    return fs_win32_to_narrow(s);
#else

  if(auto h = fs_getenv("XDG_CONFIG_HOME"); h)
    return h.value();

  if(auto h = fs_getenv("HOME"); h)
    return h.value() + "/.config";

#endif

  fs_print_error("", __func__);
  return {};
}
