#include <string>


std::string fs_getcwd();

void fs_chdir(const std::string& path);

extern "C" bool fs_chdir(const char *path);
