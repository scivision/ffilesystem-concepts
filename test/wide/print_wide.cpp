#include <iostream>
#include <string>
#include <cstdlib>
#include <locale>

int main(){
    std::wcout.imbue(std::locale("en_US.UTF-8"));  // need this for std::wcout to work

    std::wstring s = L"こんにちは、世界！";
    std::wcout << s << std::endl;
    std::cout << s.size() << std::endl;

    if (s.size() != 9) {
      std::cerr << "Error: expected size 9\n";
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
