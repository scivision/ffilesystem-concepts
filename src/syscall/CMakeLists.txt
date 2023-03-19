set_property(DIRECTORY PROPERTY LABELS "syscall")

add_library(exec exec.c)
target_include_directories(exec INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(exec PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

if(WIN32)
  add_library(create_process CreateProcess.c)
  target_include_directories(create_process PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_definitions(create_process PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)
endif()
