#if defined(__linux__)
#include <sys/vfs.h>
#include <linux/magic.h>
// https://github.com/torvalds/linux/blob/master/include/uapi/linux/magic.h
#elif defined(__APPLE__)
#include <sys/param.h>
#include <sys/mount.h>
#elif defined(_WIN32) || defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <system_error>  // std::system_category

#include <filesystem>


std::string filesystem_type(std::string_view path) {
  // return string name of filesystem type if known

#if defined(_WIN32) || defined(__CYGWIN__)
  // necessary to avoid nonsense error messages
  if(path.empty())  [[unlikely]]
    return {};

  if(std::vector<char> buf(MAX_PATH+1);
      GetVolumeInformationA(path.data(), nullptr, 0, nullptr, nullptr, nullptr, buf.data(), buf.size()))  [[likely]]
    return std::string(buf.data());

  std::cerr << "GetVolumeInformationA failed: " << std::system_category().message(GetLastError()) << std::endl;
  return std::string();
#elif defined(__linux__) || defined(__APPLE__)
  struct statfs s;
  statfs(path.data(), &s);
#endif

#if defined(__linux__)
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
      return std::to_string(s.f_type);
  }
#elif defined(__APPLE__)
  return std::string(s.f_fstypename);
#endif

  std::cerr << "Unknown operating system\n";
  return std::string();
}

int main(int argc, char* argv[]) {

  std::string p = (argc < 2) ? "/" : argv[1];
  std::string t;

  std::filesystem::path path(p);

  if(!path.is_absolute())
    path = std::filesystem::canonical(path);
#ifdef _WIN32
  path = path.root_path();
#endif

  std::cout << "filesystem: " + path.string() + " " + filesystem_type(path.string()) + "\n";

  return EXIT_SUCCESS;

}
