#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>  // strerror

#ifdef _MSC_VER
#include <crtdbg.h>
#else
#include <unistd.h>
#endif

#define MAXP 256


void get_cwd(char* cwd){

  if(getcwd(cwd, MAXP)) return;

  fprintf(stderr, "ERROR: getcwd: %s\n", strerror(errno));
  exit(EXIT_FAILURE);
}


int main(int argc, char* argv[]){
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

  if(argc != 2){
    fprintf(stderr, "Usage: %s <path>\n", argv[0]);
    return EXIT_FAILURE;
  }


  char cwd[MAXP];
  get_cwd(cwd);
  printf("Current path: %s \n", cwd);

  if(chdir(argv[1]) != 0){
    fprintf(stderr, "ERROR: chdir: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  get_cwd(cwd);
  printf("New current path: %s \n", cwd);

  return EXIT_SUCCESS;
}
