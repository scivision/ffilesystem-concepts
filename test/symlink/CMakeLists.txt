set_property(DIRECTORY PROPERTY LABELS "symlink")

add_library(symlink ${PROJECT_SOURCE_DIR}/src/symlink/symlink.cpp)
target_include_directories(symlink INTERFACE ${PROJECT_SOURCE_DIR}/src/symlink/)
target_link_libraries(symlink PRIVATE windows_symlink)

add_executable(test_symlink test_symlink.cpp)
target_link_libraries(test_symlink PRIVATE symlink)

add_test(NAME CppSymlink COMMAND test_symlink)

set_property(TEST CppSymlink PROPERTY LABELS "CXX")
