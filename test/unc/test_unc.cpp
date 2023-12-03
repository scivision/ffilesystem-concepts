#include <filesystem>
#include <cstdlib>
#include <iostream>

static_assert(__cpp_lib_filesystem, "C++17 std::filesystem is not available.");

namespace fs = std::filesystem;

int main(){

  int err = 0;
  bool xfail = false;
#ifdef __MINGW32__
  xfail = true;
#endif

  fs::path bserv("\\\\server\\share\\\\path\\");
  fs::path rserv("//server/share//path/");

  fs::path n_bserv = bserv.lexically_normal();
  fs::path n_rserv = rserv.lexically_normal();
  if (n_bserv == n_rserv){
    std::cout << "PASSED: path: " << n_bserv << " == " << n_rserv << "\n";
  }
  else {
    err++;
    std::cerr << "FAILED: path: " << n_bserv << " != " << n_rserv << "\n";
  }

  fs::path p3("//host/a/b/../c");
  fs::path p3n = p3.lexically_normal();
  fs::path p3n_r("\\\\host\\a\\c");

  if (p3n == p3n_r){
    std::cout << "PASSED: path: " << p3n << " == " << p3n_r << "\n";
  }
  else {
    err++;
    std::cerr << "FAILED: path: " << p3n << " != " << p3n_r << "\n";
  }

  std::string p3s = p3n.string();
  if (p3s == "\\\\host\\a\\c"){
    std::cout << "PASSED: string: " << p3s << " == \\\\host\\a\\c\n";
  }
  else {
    err++;
    std::cerr << "FAILED: string: " << p3s << " != \\\\host\\a\\c\n";
  }

  std::string p3gs = p3n.generic_string();
  if (p3gs == "//host/a/c"){
    std::cout << "PASSED: generic string: " << p3gs << " == //host/a/c\n";
  }
  else {
    err++;
    std::cerr << "FAILED: generic string: " << p3gs << " != //host/a/c\n";
  }

  fs::path dlocal("\\\\?\\C:\\path\\x\\..");
  fs::path blocal("C:\\path\\y\\..\\");

  fs::path n_dlocal = fs::weakly_canonical(dlocal);
  fs::path n_blocal = blocal.lexically_normal();

  if (n_dlocal == n_blocal){
    std::cout << "PASSED: long_path: " << n_dlocal << " == " << n_blocal << "\n";
  }
  else {
    err++;
    std::cerr << "FAILED: long_path: " << n_dlocal << " != " << n_blocal << "\n";
  }

  if (err != 0){
    std::cerr << "FAILED: UNC tests\n";
    if(xfail){
      std::cerr << "XFAIL: UNC tests failed due to known bugs in MinGW compiler\n";
      return 77;
    }
    else {
      return EXIT_FAILURE;
    }
  }

  std::cout << "OK: UNC tests passed\n";
  return EXIT_SUCCESS;
}
