cmake_minimum_required(VERSION 3.22...3.27)

project(FilesystemConcepts LANGUAGES C CXX)
enable_testing()

option(fortran "use Fortran" ON)
include(CheckLanguage)
check_language(Fortran)
if(fortran)
  enable_language(Fortran)
endif()

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

foreach(d IN ITEMS canonical file_types lib_dir symlink syscall)
  add_subdirectory(src/${d})
  add_subdirectory(test/${d})
endforeach()

foreach(d IN ITEMS chdir iterdir space_avail)
  add_subdirectory(test/${d})
endforeach()
