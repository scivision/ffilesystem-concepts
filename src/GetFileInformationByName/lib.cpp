#include <string_view>
#include <string>
#include <iostream>

#include <Windows.h>


std::wstring
fs_win32_to_wide(std::string_view n)
{
  // assuming input is null-terminated and fourth argument is -1, then L includes the null terminator
  // https://docs.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar
  std::string ns(n);
  if (int L = MultiByteToWideChar(CP_UTF8, 0, ns.c_str(), -1, nullptr, 0); L > 0)
  {
    std::wstring w(L, '\0');
    if(MultiByteToWideChar(CP_UTF8, 0, ns.c_str(), -1, w.data(), L) == L) {
      w.pop_back();
      return w;
    }
  }

  std::cerr << "Failed to convert string to wide string: " << n << "\n";
  return {};
}


bool dontuse_GetFileSimilar(std::string_view path1,std::string_view path2) {
  // GetFileInformationByName has trouble with relative symlinks - it says they're not the same
  // thus we need to use GetFileInformationByHandle instead

// https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/ns-ntifs-file_stat_basic_information
  // GetFileInformationByName in Windows >= 24H2
  // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getfileinformationbyname
  // https://github.com/rust-lang/rust/issues/130169
  FILE_STAT_BASIC_INFORMATION by_name1{}, by_name2{};

  if ( GetFileInformationByName(fs_win32_to_wide(path1).c_str(), FileStatBasicByNameInfo, &by_name1, sizeof(by_name1)) &&
      GetFileInformationByName(fs_win32_to_wide(path2).c_str(), FileStatBasicByNameInfo, &by_name2, sizeof(by_name2))) {
    if (by_name1.VolumeSerialNumber.QuadPart == by_name2.VolumeSerialNumber.QuadPart &&
        by_name1.FileId.QuadPart == by_name2.FileId.QuadPart)
      return true;
  }
  // .FileID and .VolumeSerialNumber are LARGE_INTEGER
  return false;
}
