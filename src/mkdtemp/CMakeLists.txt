set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

if(NOT HAVE_MKDTEMP)
  add_library(mkdtemp mkdtemp.cpp)
  target_include_directories(mkdtemp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_library(mkdtemp_f mkdtemp_f.cpp)
target_compile_definitions(mkdtemp_f PRIVATE $<$<BOOL:${HAVE_MKDTEMP}>:HAVE_MKDTEMP>)
target_link_libraries(mkdtemp_f PRIVATE $<$<NOT:$<BOOL:${HAVE_MKDTEMP}>>:mkdtemp>)
