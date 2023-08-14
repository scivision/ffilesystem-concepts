#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <memory>
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;


std::string long2short(const std::string in){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getshortpathnamew
// the path must exist

    if (!fs::exists(in)){
      std::cerr << "ERROR:GetShortPathName: " << in << " does not exist\n";
      return {};
    }

    long length = 0;
    auto buf = std::make_unique<char[]>(MAX_PATH);
// size includes null terminator
    length = GetShortPathNameA(in.c_str(), nullptr, 0);
    if (length == 0) {
      std::cerr << "ERROR:GetShortPathName: could not determine short path length\n";
      return {};
    }

// convert long path
    length = GetShortPathNameA(in.c_str(), buf.get(), length);
    if (length == 0) {
      std::cerr << "ERROR:GetShortPathName: could not determine short path\n";
      return {};
    }

    std::string short_path(buf.get());

    return short_path;
}


std::string short2long(const std::string in){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getlongpathnamea
// the path must exist

    if (!fs::exists(in)){
      std::cerr << "ERROR:GetLong: " << in << " does not exist\n";
      return {};
    }

    long length = 0;
    auto buf = std::make_unique<char[]>(MAX_PATH);

// size includes null terminator
    length = GetLongPathNameA(in.c_str(), nullptr, 0);
    if (length == 0) {
      std::cerr << "ERROR:GetLong: could not determine short path length\n";
      return {};
    }

// convert short path
    length = GetLongPathNameA(in.c_str(), buf.get(), length);
    if (length == 0) {
      std::cerr << "ERROR:GetLong could not determine short path\n";
      return {};
    }

    std::string out(buf.get());

    return out;
}


int main(int argc, char** argv){

    std::string long_path;

    if(argc < 2)
      long_path = std::getenv("PROGRAMFILES");
    else
      long_path = argv[1];

    std::string short_path = long2short(long_path);
    if (short_path.empty())
      return EXIT_FAILURE;

    std::cout << long_path << " => " << short_path << '\n';

    std::string long_path2 = short2long(short_path);
    if (long_path2.empty())
      return EXIT_FAILURE;

    std::cout << short_path << " => " << long_path2 << '\n';

    return EXIT_SUCCESS;
}
