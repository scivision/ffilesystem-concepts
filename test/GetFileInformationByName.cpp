// Demonstrate Windows >= 24H2 API GetFileInformationByName
// in June 2025, MinGW/MSYS2 didn't have this API yet.

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <string_view>
#include <source_location>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif


int main(){
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

    std::string_view narrow_path = std::source_location::current().file_name();

    // Convert narrow string to wide string
    int wide_size = MultiByteToWideChar(CP_UTF8, 0, narrow_path.data(), static_cast<int>(narrow_path.size()), nullptr, 0);
    std::wstring wide_path(wide_size, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, narrow_path.data(), static_cast<int>(narrow_path.size()), wide_path.data(), wide_size);

    FILE_STAT_BASIC_INFORMATION f;

    std::cout << "GetFileInformationByName for: " << narrow_path << "\n";

    if (GetFileInformationByName(wide_path.c_str(),
                                  FileStatBasicByNameInfo,
                                  &f,
                                  sizeof(f)))

    {
        std::wcout << L"FileId             0x" << std::hex << f.FileId.QuadPart << L"\n";
        std::wcout << L"VolumeSerialNumber 0x" << f.VolumeSerialNumber.QuadPart << L"\n";

        std::wcout << L"CreationTime       0x" << f.CreationTime.QuadPart << L"\n";
        std::wcout << L"LastAccessTime     0x" << f.LastAccessTime.QuadPart << L"\n";
        std::wcout << L"LastWriteTime      0x" << f.LastWriteTime.QuadPart << L"\n";
        std::wcout << L"ChangeTime         0x" << f.ChangeTime.QuadPart << L"\n";
        std::wcout << L"AllocationSize     0x" << f.AllocationSize.QuadPart << L"\n";
        std::wcout << L"EndOfFile          0x" << f.EndOfFile.QuadPart << L"\n";
        std::wcout << L"FileAttributes     0x" << f.FileAttributes << L"\n";
        std::wcout << L"ReparseTag         0x" << f.ReparseTag << L"\n";
        std::wcout << L"NumberOfLinks      " << std::dec << f.NumberOfLinks << L"\n";
        return 0;
    }


  std::cerr << "GetFileInformationByName failed with error " << GetLastError() << "\n";
  return 1;

}
