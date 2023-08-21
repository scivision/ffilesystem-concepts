set_property(DIRECTORY PROPERTY LABELS "syscall")

add_library(exec exec.c)
target_include_directories(exec INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
  add_library(create_process CreateProcess.c)
  target_include_directories(create_process PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
