set_property(DIRECTORY PROPERTY LABELS "copytree")

add_library(copytree copytree.cpp)
target_include_directories(copytree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
