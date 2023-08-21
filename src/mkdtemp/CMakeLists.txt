set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

if(NOT HAVE_MKDTEMP)
  add_library(mkdtemp mkdtemp.cpp)
  target_include_directories(mkdtemp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_definitions(mkdtemp PRIVATE
  )
endif()
