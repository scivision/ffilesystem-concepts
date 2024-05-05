#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>
#include <exception>

#include <filesystem>

#include "short_path.h"

namespace fs = std::filesystem;


std::string long2short(std::string_view in){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getshortpathnamew
// the path must exist

    if (!fs::exists(in))
      throw std::runtime_error("ERROR:GetShortPathName: path does not exist");

// size includes null terminator
    DWORD L = GetShortPathNameA(in.data(), nullptr, 0);
    if (L == 0)
      throw std::runtime_error("GetShortPathName: could not determine short path length");

// convert long path
    std::vector<char> buf(MAX_PATH);
    if(!GetShortPathNameA(in.data(), buf.data(), L))
      throw std::runtime_error("GetShortPathName: could not determine short path");

    std::string short_path(buf.data());

    return short_path;
}


std::string short2long(std::string_view in){
// https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getlongpathnamea
// the path must exist

    if (!fs::exists(in))
      throw std::runtime_error("GetLong: path does not exist");

// size includes null terminator
    DWORD L = GetLongPathNameA(in.data(), nullptr, 0);
    if(L == 0)
      throw std::runtime_error("GetLong: could not determine path length");

// convert short path
    std::vector<char> buf(MAX_PATH);
    if(!GetLongPathNameA(in.data(), buf.data(), L))
      throw std::runtime_error("GetLong could not determine path length");

    std::string out(buf.data());

    return out;
}
