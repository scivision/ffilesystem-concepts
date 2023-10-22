#include <string>


std::string fs_get_cwd();
void fs_chdir(const std::string&);


extern "C" bool fs_chdir(const char *);
extern "C" size_t fs_get_cwd(char *, size_t);
