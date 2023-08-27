set_property(DIRECTORY PROPERTY LABELS "syscall")

add_library(exec_C exec.c)
target_include_directories(exec_C INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(exec_CXX exec.cpp)
target_include_directories(exec_CXX INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


if(WIN32)
  add_library(create_process CreateProcess.c)
  target_include_directories(create_process PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
