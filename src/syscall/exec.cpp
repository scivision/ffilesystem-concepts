// from: https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87152177
// https://linux.die.net/man/3/execlp

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory> // std::make_unique
#include <cstring>
#include <exception>

#ifdef _MSC_VER
#include <process.h>
#else
#include <cerrno>
#include <unistd.h>
#endif


void execute_process(std::string_view cmd)
{
  // "cmd" should be sanitized by caller
  // more than one argument needs to be split up into an array of strings
  // and perhap dealt to execvp() instead of execlp()

  auto buf = std::make_unique<char[]>(8191);
  std::strcpy(buf.get(), cmd.data());

#ifdef _MSC_VER
  // don't directly specify "cmd.exe" in exec() for security reasons
  char* comspec = std::getenv("COMSPEC");
  if(!comspec)
    throw std::runtime_error("ERROR: environment variable COMSPEC not defined");

  intptr_t ir = _execl(comspec, "cmd", "/c", buf.get(),  nullptr);
  if(static_cast<int>(ir) == -1)
    throw std::runtime_error("ERROR: _execl failed");

#else
  if (execlp(buf.get(), buf.get(), nullptr) == -1)
    throw std::runtime_error("ERROR: execlp: " + std::to_string(errno));
#endif
}
