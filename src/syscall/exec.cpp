// from: https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87152177
// https://linux.die.net/man/3/execlp

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory> // std::make_unique
#include <cstring>

#ifdef _MSC_VER
#include <process.h>
#else
#include <unistd.h>
#endif


int execute_process(const std::string cmd)
{
  // "cmd" should be sanitized by caller
  // more than one argument needs to be split up into an array of strings
  // and perhap dealt to execvp() instead of execlp()

  auto buf = std::make_unique<char[]>(8191);
  std::strcpy(buf.get(), cmd.c_str());

#ifdef _MSC_VER
  // don't directly specify "cmd.exe" in exec() for security reasons
  char* comspec = std::getenv("COMSPEC");
  if(!comspec){
    std::cerr << "ERROR: environment variable COMSPEC not defined\n";
    return -1;
  }
  intptr_t ir = _execl(comspec, "cmd", "/c", buf.get(),  nullptr);
  return static_cast<int>(ir);
#else
  return execlp(buf.get(), buf.get(), nullptr);
#endif
}
