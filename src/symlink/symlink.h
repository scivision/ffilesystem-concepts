#include <filesystem>

#ifndef __cpp_lib_filesystem
#error "No C++17 filesystem support"
#endif

namespace fs = std::filesystem;


void fs_create_symlink(const fs::path, const fs::path);
bool fs_exists(const fs::path);
bool fs_is_symlink(const fs::path);
fs::path fs_read_symlink(const fs::path);
