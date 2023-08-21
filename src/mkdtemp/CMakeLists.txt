set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

if(NOT HAVE_MKDTEMP)
  add_library(mkdtemp mkdtemp.cpp)
  target_include_directories(mkdtemp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_definitions(mkdtemp PRIVATE
  $<$<BOOL:${HAVE_UNISTD_H}>:HAVE_UNISTD_H>
  $<$<BOOL:${WIN32}>:Win32>
  )
endif()
