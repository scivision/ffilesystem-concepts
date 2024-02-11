#include <stdlib.h>

#include "execute_process.h"


int main(void){
  if(execute_process("whoami"))
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
