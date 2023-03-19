cmake_minimum_required(VERSION 3.20)
project(IterDir LANGUAGES CXX)
enable_testing()

set_property(DIRECTORY PROPERTY LABELS "iterdir")

find_package(Python COMPONENTS Interpreter)

add_executable(iterdir iterdir.cpp)
add_test(NAME IterDirCPP COMMAND iterdir "${CMAKE_SOURCE_DIR}")

if(Python_Interpreter_FOUND)
  add_test(NAME IterDirPython
  COMMAND Python::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/iterdir.py "${CMAKE_SOURCE_DIR}"
  )
  set_property(TEST IterDirPython PROPERTY LABELS "python")
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")
