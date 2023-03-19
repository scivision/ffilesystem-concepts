cmake_minimum_required(VERSION 3.20)

project(FilesystemConcepts LANGUAGES C CXX)
enable_testing()

option(fortran "use Fortran" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include(cmake/compilers.cmake)

add_subdirectory(src)

file(GENERATE OUTPUT .gitignore CONTENT "*")
