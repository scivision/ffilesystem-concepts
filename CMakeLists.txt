cmake_minimum_required(VERSION 3.22...3.32)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Please use out of source build like:
  cmake -Bbuild")
endif()

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
# This project isn't using C++ modules; avoid bugs in module scanning CMake 3.28, 3.29 with GCC 14.1 on WIndows

project(FilesystemConcepts LANGUAGES C CXX)

enable_testing()

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

include(options.cmake)
if(fortran)
  enable_language(Fortran)
endif()


include(cmake/compilers.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# CPPcheck
if(cppcheck)
  find_program(cppcheck_exe NAMES cppcheck REQUIRED)
  set(cppcheck_opts --enable=all --inline-suppr --quiet --suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck.supp)
  set(CMAKE_C_CPPCHECK ${cppcheck_exe} --std=c11 ${cppcheck_opts})
  set(CMAKE_CXX_CPPCHECK ${cppcheck_exe} --std=c++20 ${cppcheck_opts})
endif()

# utilities
add_subdirectory(src)

set(satest canonical chdir copytree
  file_parts file_types filesystem_type
  find_file
  home_dir
  is_dir
  is_exe
  iterdir lib_dir mkdtemp
  memory
  space_avail symlink syscall path_type
  strcpy_s)
if(WIN32)
  list(APPEND satest case_sensitive maximums short_path unc)
elseif(CYGWIN)
  list(APPEND satest cygpath)
endif()

foreach(d IN LISTS satest)
  add_subdirectory(test/${d})
endforeach()

file(GENERATE OUTPUT .gitignore CONTENT "*")
