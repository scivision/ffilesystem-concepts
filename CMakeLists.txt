cmake_minimum_required(VERSION 3.14...3.27)

project(FilesystemConcepts LANGUAGES C CXX)
enable_testing()

option(fortran "use Fortran" ON)
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

# test + library
foreach(d IN ITEMS canonical file_types lib_dir symlink syscall)
  add_subdirectory(src/${d})
  add_subdirectory(test/${d})
endforeach()

# standalone tests
set(satest chdir is_exe iterdir space_avail)
if(WIN32)
  list(APPEND satest case_sensitive maximums short_path)
endif()

foreach(d IN LISTS satest)
  add_subdirectory(test/${d})
endforeach()
