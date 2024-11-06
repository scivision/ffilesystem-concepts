#include <string>

std::string fs_make_tempdir(std::string_view);

extern "C" size_t fs_make_tempdir(char*, size_t);
