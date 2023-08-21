set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

if(NOT HAVE_MKDTEMP)
  add_library(mkdtemp mkdtemp.c mt19937-64.c)
  target_include_directories(mkdtemp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_definitions(mkdtemp PRIVATE
  $<$<BOOL:${HAVE_STDINT_H}>:HAVE_STDINT_H>
  $<$<BOOL:${HAVE_CONFIG_H}>:HAVE_CONFIG_H>
  $<$<BOOL:${HAVE_UNISTD_H}>:HAVE_UNISTD_H>
  $<$<BOOL:${WIN32}>:Win32>
  )
endif()
