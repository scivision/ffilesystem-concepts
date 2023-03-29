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

# --- project properties

# Necessary for shared library with Visual Studio / Windows oneAPI -- creates .lib file to acommpany .dll
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

# Rpath options necessary for shared library install to work correctly in user projects
set(CMAKE_INSTALL_NAME_DIR ${CMAKE_INSTALL_FULL_LIBDIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_FULL_LIBDIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()
