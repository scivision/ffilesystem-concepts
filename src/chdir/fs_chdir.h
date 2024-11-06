#include <string_view>
#include <cstdint>


std::string fs_get_cwd();
void fs_chdir(std::string_view);


extern "C" bool fs_chdir(const char *);
extern "C" size_t fs_get_cwd(char *, size_t);
