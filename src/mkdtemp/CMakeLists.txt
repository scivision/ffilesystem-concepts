set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_library(mkdtemp mkdtemp.cpp)
target_include_directories(mkdtemp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mkdtemp PRIVATE ffilesystem)
