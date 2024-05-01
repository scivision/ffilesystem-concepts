#if defined(__linux__)
#include <sys/vfs.h>
#include <linux/magic.h>
// https://github.com/torvalds/linux/blob/master/include/uapi/linux/magic.h
#elif defined(__APPLE__)
#include <sys/param.h>
#include <sys/mount.h>
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <memory>
#include <iostream>
#include <cstdlib>
#include <string>

#include <filesystem>


std::string filesystem_type(std::string_view path) {
  // return string name of filesystem type if known

#if defined(_WIN32)
  auto buf = std::make_unique<char[]>(MAX_PATH+1);

  if(GetVolumeInformationA(path.data(), nullptr, 0, nullptr, nullptr, nullptr, buf.get(), sizeof(buf)))
    return std::string(buf.get());

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
    case XFS_SUPER_MAGIC:
      return "xfs";
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
  path = path.root_path();

  std::cout << "filesystem: " + path.string() + " " + filesystem_type(path.string()) + "\n";

  return EXIT_SUCCESS;

}
