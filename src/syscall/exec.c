// from: https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87152177
// https://linux.die.net/man/3/execlp

#include <stddef.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <process.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>

int execute_process(const char* cmd)
{
  // "cmd" should be sanitized by caller
  // more than one argument needs to be split up into an array of strings
  // and perhap dealt to execvp() instead of execlp()

#ifdef _MSC_VER
  // don't directly specify "cmd.exe" in exec() for security reasons
  char* comspec = getenv("COMSPEC");
  if(!comspec){
    fprintf(stderr, "ERROR: environment variable COMSPEC not defined\n");
    return -1;
  }
  intptr_t ir = _execl(comspec, "cmd", "/c", cmd,  NULL);
  return (int)ir;
#else
  return execlp(cmd, cmd, NULL);
#endif
}
