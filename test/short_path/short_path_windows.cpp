#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <memory>
#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>
#include <filesystem>

namespace fs = std::filesystem;


std::string long2short(const std::string in){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getshortpathnamew
// the path must exist

    if (!fs::exists(in)){
      std::cerr << "ERROR:GetShortPathName: " << in << " does not exist\n";
      return {};
    }

    auto buf = std::make_unique<char[]>(MAX_PATH);
// size includes null terminator
    DWORD L=0;
    L = GetShortPathNameA(in.c_str(), nullptr, 0);
    if (L == 0)
      throw std::runtime_error("GetShortPathName: could not determine short path length");

// convert long path
    if(!GetShortPathNameA(in.c_str(), buf.get(), L))
      throw std::runtime_error("GetShortPathName: could not determine short path");

    std::string short_path(buf.get());

    return short_path;
}


std::string short2long(const std::string in){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getlongpathnamea
// the path must exist

    if (!fs::exists(in))
      throw std::runtime_error("GetLong: " + in + " does not exist");

    auto buf = std::make_unique<char[]>(MAX_PATH);

// size includes null terminator
    DWORD L=0;
    L = GetLongPathNameA(in.c_str(), nullptr, 0);
    if (L == 0)
      throw std::runtime_error("GetLong: could not determine path length");

// convert short path
    if(!GetLongPathNameA(in.c_str(), buf.get(), L))
      throw std::runtime_error("GetLong could not determine path length");

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

    std::cout << long_path << " => " << short_path << '\n';

    std::string long_path2 = short2long(short_path);

    std::cout << short_path << " => " << long_path2 << '\n';

    return EXIT_SUCCESS;
}
