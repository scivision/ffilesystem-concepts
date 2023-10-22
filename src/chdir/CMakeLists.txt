set_property(DIRECTORY PROPERTY LABELS "chdir")

add_library(chdir_cpp OBJECT chdir.cpp)
target_include_directories(chdir_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
