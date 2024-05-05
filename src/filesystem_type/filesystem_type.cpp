#if defined(__linux__)
#include <sys/vfs.h>
#include <linux/magic.h>
// https://github.com/torvalds/linux/blob/master/include/uapi/linux/magic.h
#elif defined(__APPLE__) || defined(BSD)
#include <sys/param.h>
#include <sys/mount.h>
#elif defined(_WIN32) || defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <cctype> // isalpha
#include <system_error>

#include <filesystem>


#ifdef __linux__
static inline std::string fs_type_linux(std::string_view path)
{
  struct statfs s;

  if(statfs(path.data(), &s)) {
    std::cerr << "ERROR:fs_get_type: statfs(" << path << ") " << std::strerror(errno) << "\n";
    return "";
  }

  switch (s.f_type) {
    case EXT4_SUPER_MAGIC:
      return "ext4";
#ifdef EXFAT_SUPER_MAGIC
    case EXFAT_SUPER_MAGIC:
      return "exfat";
#endif
#ifdef FUSE_SUPER_MAGIC
    case FUSE_SUPER_MAGIC:
      return "fuse";
#endif
    case SQUASHFS_MAGIC:
      return "squashfs";
    case TMPFS_MAGIC:
      return "tmpfs";
    case V9FS_MAGIC:
      return "v9fs";
    // used for WSL
    // https://devblogs.microsoft.com/commandline/whats-new-for-wsl-in-windows-10-version-1903/
#ifdef XFS_SUPER_MAGIC
    case XFS_SUPER_MAGIC:
      return "xfs";
#endif
    default:
      std::cerr << "ERROR:fs_get_type(" << path << " type ID: " << s.f_type << "\n";
      return "";
  }
}
#endif


std::string fs_filesystem_type(std::string_view path)
{
  // return name of filesystem type if known

#if defined(_WIN32) || defined(__CYGWIN__)

  std::string r = std::filesystem::canonical(path).root_path().string();

  if(std::vector<char> name(MAX_PATH+1);
      GetVolumeInformationA(r.data(), NULL, 0, NULL, NULL, NULL, name.data(), name.size()))
    return name.data();

  std::cerr << "ERROR:fs_get_type: GetVolumeInformationA(" << r << ") " << std::system_category().message(GetLastError()) << "\n";
  return {};
#elif defined(__linux__)
  return fs_type_linux(path);
#elif defined(__APPLE__) || defined(BSD)
  if(struct statfs s; !statfs(path.data(), &s))
    return s.f_fstypename;
#endif

  std::cerr << "ERROR:fs_get_type: Unknown operating system\n";
  return {};
}
