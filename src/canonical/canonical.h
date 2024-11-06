#ifdef __cplusplus

#include <string_view>

#ifdef _WIN32
std::string fs_win32_read_symlink(std::string_view);
#endif

std::string fs_realpath(std::string_view);

extern "C" {
#endif

size_t fs_realpath(const char*, char*, size_t);

#ifdef _WIN32
size_t fs_win32_read_symlink(const char*, char*, size_t);
#endif

#ifdef __cplusplus
}
#endif
