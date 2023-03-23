#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "canonical.h"


#define MAXP 256

int main(int argc, char* argv[]){

  char in[MAXP], out[MAXP];

  if(argc != 2){
    fprintf(stderr, "Usage: %s <path>\n", argv[0]);
    return EXIT_FAILURE;
  }

  strcpy(in, argv[1]);

  if(!fs_realpath(in, out, MAXP)){
    fprintf(stderr, "test_canonical_c: failed to canonicalize path: %s\n", in);
    return EXIT_FAILURE;
  }

  printf("%s\n", out);

  return EXIT_SUCCESS;
}
