#include "copytree.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(){

    auto tmp = fs::temp_directory_path();

    auto ds = tmp / "copytree_test/source";
    auto dd = tmp / "copytree_test/dest";

    auto name = "file1.txt";
    auto src = ds / name;
    auto dst = dd / name;


    fs::create_directories(ds);
    touch(src.string());

    copytree(ds.string(), dd.string(), true);

    if(!fs::is_regular_file(dst)){
        std::cerr << dst << " is not a regular file\n";
        return EXIT_FAILURE;
    }

    std::cout << "OK: copytree: " << src.generic_string() << " => " << dst.generic_string() << "\n";

    return EXIT_SUCCESS;
}
