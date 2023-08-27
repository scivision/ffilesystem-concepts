set_property(DIRECTORY PROPERTY LABELS "symlink")


add_executable(test_symlink test_symlink.cpp)
target_link_libraries(test_symlink PRIVATE symlink)

add_test(NAME CppSymlink COMMAND test_symlink)

set_property(TEST CppSymlink PROPERTY LABELS "CXX")
