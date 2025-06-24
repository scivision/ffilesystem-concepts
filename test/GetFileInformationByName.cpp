// Demonstrate Windows >= 24H2 API GetFileInformationByName
// in June 2025, MinGW/MSYS2 didn't have this API yet.

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <string_view>


int main(){
    std::wstring_view path = L".";

    FILE_STAT_BASIC_INFORMATION f;

    if (GetFileInformationByName(path.data(),
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
