// C++ approach to making a unique temporary directory
#include <algorithm> // for generate_n
#include <array>     // for array
#include <functional>
#include <random>
#include <string>
#include <iterator> // for begin, end

#include <iostream>

#include <filesystem>

namespace fs = std::filesystem;

#include "mkdtemp.h"
#include "ffilesystem.h"

// CTAD C++17 random string generator
// https://stackoverflow.com/a/444614
// https://en.cppreference.com/w/cpp/language/class_template_argument_deduction

#ifdef __cpp_deduction_guides  // C++17
template <typename T = std::mt19937>

static auto random_generator() -> T {
  auto constexpr seed_bytes = sizeof(typename T::result_type) * T::state_size;
  auto constexpr seed_len = seed_bytes / sizeof(std::seed_seq::result_type);
  auto seed = std::array<std::seed_seq::result_type, seed_len>();
  auto dev = std::random_device();
  std::generate_n(std::begin(seed), seed_len, std::ref(dev));
  auto seed_seq = std::seed_seq(std::begin(seed), std::end(seed));
  return T{seed_seq};
}
#endif

std::string generate_random_alphanumeric_string(const std::string::size_type len)
{
#ifdef __cpp_deduction_guides
  constexpr std::string_view chars =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
  thread_local auto rng = random_generator<>();
  auto dist = std::uniform_int_distribution{{}, chars.length() - 1};
  auto result = std::string(len, '\0');
  std::generate_n(std::begin(result), len, [&]() { return chars[dist(rng)]; });
  return result;
#else
  fs_print_error("" , "generate_random_alphanumeric_string needs C++17 or newer");
  return {};
#endif
}

size_t fs_make_tempdir(char* result, size_t buffer_size){
  // Fortran / C / C++ interface function

  std::string tmpdir = fs_make_tempdir("tempdir.");

  return fs_str2char(tmpdir, result, buffer_size);
}


std::string fs_make_tempdir(std::string_view prefix)
{
  // make unique temporary directory starting with prefix

  size_t Lname = 16;  // arbitrary length for random string

  fs::path tdir = fs::temp_directory_path();

  fs::path t;
  do {
    t = (tdir / (std::string(prefix) + generate_random_alphanumeric_string(Lname)));
  } while (fs::is_directory(t));

  if (!fs::create_directory(t))
    std::cerr << "fs_make_tempdir:mkdir: could not create temporary directory" << t << "\n";

  return t.generic_string();

}
