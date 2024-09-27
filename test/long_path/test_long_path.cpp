#include <string>
#include <cstdlib>
#include <iostream>

#include <direct.h>

int main()
{
  char currentdir[32767];
  _getcwd(currentdir, sizeof(currentdir));

  const std::string filename = std::string(currentdir) +
"\\filename_with_256_characters_xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\
xxxxxxxxxxxxxxxxxxxxx";

  const std::string path = "\\\\?\\" + filename;

  FILE* fid = fopen(path.data(), "w");
  if(!fid){
    std::cerr << "ERROR:ffilesystem:touch:fopen " << path << "\n";
    return EXIT_FAILURE;
  }

  if(fclose(fid) != 0){
    fprintf(stderr, "ERROR:ffilesystem:touch:fclose %s => %s\n", path, strerror(errno));
    return false;

  return EXIT_SUCCESS;
}
