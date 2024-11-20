#ifdef __cplusplus
#include <string_view>

extern "C" {
#endif

size_t fs_str2char(std::string_view, char*, size_t);
size_t fs_char2char(const char*, char*, size_t);

#ifdef __cplusplus
}
#endif

std::string fs_to_narrow(const std::wstring_view);
