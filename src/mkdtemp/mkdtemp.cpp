// C++ approach to making a unique temporary directory
#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <random>
#include <string>

#include <stdexcept>

#include <filesystem>

namespace fs = std::filesystem;

#include "mkdtemp.h"
#include "ffilesystem.h"

// CTAD C++17 random string generator
// https://stackoverflow.com/a/444614

template <typename T = std::mt19937>
auto random_generator() -> T {
    auto constexpr seed_bytes = sizeof(typename T::result_type) * T::state_size;
    auto constexpr seed_len = seed_bytes / sizeof(std::seed_seq::result_type);
    auto seed = std::array<std::seed_seq::result_type, seed_len>();
    auto dev = std::random_device();
    std::generate_n(begin(seed), seed_len, std::ref(dev));
    auto seed_seq = std::seed_seq(begin(seed), end(seed));
    return T{seed_seq};
}

auto generate_random_alphanumeric_string(std::size_t len) -> std::string {
    static constexpr auto chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    thread_local auto rng = random_generator<>();
    auto dist = std::uniform_int_distribution{{}, std::strlen(chars) - 1};
    auto result = std::string(len, '\0');
    std::generate_n(begin(result), len, [&]() { return chars[dist(rng)]; });
    return result;
}

extern "C" size_t mkdtemp_f(char* result, size_t buffer_size){
  // Fortran / C / C++ interface function

  std::string tmpdir = fs_make_tempdir("tempdir.");

  return fs_str2char(tmpdir, result, buffer_size);
}


std::string fs_make_tempdir(std::string prefix)
{
  // make unique temporary directory starting with prefix

  size_t Lname = 16;  // arbitrary length for random string

  fs::path tdir = fs::temp_directory_path();

  fs::path t;
  do {
    t = (tdir / (prefix + generate_random_alphanumeric_string(Lname)));
  } while (fs::is_directory(t));

  if (!fs::create_directory(t))
    throw fs::filesystem_error("fs_make_tempdir:mkdir: could not create temporary directory", t, std::error_code(errno, std::system_category()));

  return t.generic_string();
}
