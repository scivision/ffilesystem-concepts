set_property(DIRECTORY PROPERTY LABELS "symlink")

add_library(symlink symlink.cpp)
target_link_libraries(symlink PRIVATE windows_symlink)
target_include_directories(symlink INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
