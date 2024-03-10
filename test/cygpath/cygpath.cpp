// https://cygwin.com/cygwin-api/func-cygwin-conv-path.html

#include <iostream>
#include <cstdlib>
#include <cerrno>

#include <sys/cygwin.h>


std::string to_cygpath(std::string_view winpath){

  ssize_t L = cygwin_conv_path(CCP_WIN_A_TO_POSIX, winpath.data(), nullptr, 0);
  if(L < 0){
    std::cerr << "cygwin_conv_path failed: " << std::to_string(errno) << "\n";
    return {};
  }

  char *cygpath = (char *) malloc(L);
  if(cygwin_conv_path(CCP_WIN_A_TO_POSIX, winpath.data(), cygpath, L)){
    std::cerr << "cygwin_conv_path failed: " << std::to_string(errno) << "\n";
    free(cygpath);
    return {};
  }

  std::string result(cygpath);
  free(cygpath);
  return result;

}


std::string to_winpath(std::string_view cygpath){

  ssize_t L = cygwin_conv_path(CCP_POSIX_TO_WIN_A, cygpath.data(), nullptr, 0);
  if(L < 0){
    std::cerr << "cygwin_conv_path failed: " << std::to_string(errno) << "\n";
    return {};
  }

  char *winpath = (char *) malloc(L);
  if(cygwin_conv_path(CCP_POSIX_TO_WIN_A, cygpath.data(), winpath, L)){
    std::cerr << "cygwin_conv_path failed: " << std::to_string(errno) << "\n";
    free(winpath);
    return {};
  }

  std::string result(winpath);
  free(winpath);
  return result;
}


int main(){

  std::string winpath = "C:\\Users\\user\\Desktop\\test.txt";
  std::string cygpath = to_cygpath(winpath);
  std::string w2;

  std::cout << winpath << " => " << cygpath << "\n";

  w2 = to_winpath(cygpath);
  std::cout << cygpath << " => " << w2 << "\n";

  if (w2 != winpath){
    std::cerr << "Error: " << w2 << " != " << winpath << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
