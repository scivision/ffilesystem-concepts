cmake_minimum_required(VERSION 3.22)

project(FilesystemConcepts LANGUAGES C CXX)
enable_testing()

option(fortran "use Fortran" ON)
include(CheckLanguage)
check_language(Fortran)
if(fortran)
  enable_language(Fortran)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include(cmake/compilers.cmake)
include(options.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

foreach(d IN ITEMS canonical file_types lib_dir syscall)
  add_subdirectory(src/${d})
  add_subdirectory(test/${d})
endforeach()

add_subdirectory(test/chdir)
add_subdirectory(test/iterdir)
add_subdirectory(test/space_avail)
