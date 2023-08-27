#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void copytree(const std::string source, const std::string dest, bool overwrite)
{
  // recursively copy files and directories
  auto opt = fs::copy_options::recursive;
  if(overwrite)
    opt |= fs::copy_options::overwrite_existing;

  try {
     fs::copy(source, dest, opt);
  } catch (fs::filesystem_error& e) {
#ifdef __MINGW32__
    std::cerr << "copytree: MinGW is known to have a bug if the destination directory exists, even if empty\n";
#endif
    throw e;
  }
}

void touch(const std::string path)
{
  // create a file if it doesn't exist, or update the last write time if it does
  fs::path p(path);

  if(fs::exists(p) && fs::is_regular_file(p)){
    fs::last_write_time(p, fs::file_time_type::clock::now());
    return;
  }

  if(!fs::exists(p.parent_path()))
    fs::create_directories(p.parent_path());

  fs::path file(p);
  std::ofstream ofs(file.string());
  ofs.close();

}
