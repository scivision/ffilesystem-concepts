cmake_minimum_required(VERSION 3.15...3.28)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Please use out of source build like:
  cmake -Bbuild")
endif()

project(FilesystemConcepts LANGUAGES C CXX)
enable_testing()

option(fortran "use Fortran" ON)
if(fortran)
  enable_language(Fortran)
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_Fortran_COMPILER_ID STREQUAL "NVHPC")
# bug in CMake for NVHPC "-Werror all-warnings" not valid flag
  set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
endif()

include(cmake/compilers.cmake)
include(options.cmake)

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

# test + library
foreach(d IN ITEMS canonical chdir copytree file_parts file_types lib_dir mkdtemp symlink syscall)
  add_subdirectory(src/${d})
  add_subdirectory(test/${d})
endforeach()

# standalone tests
set(satest home_dir is_exe iterdir space_avail)
if(WIN32)
  list(APPEND satest case_sensitive maximums short_path)
endif()

foreach(d IN LISTS satest)
  add_subdirectory(test/${d})
endforeach()

file(GENERATE OUTPUT .gitignore CONTENT "*")
