set_property(DIRECTORY PROPERTY LABELS "file_types")

add_executable(test_file_types test_file_types.cpp)
target_link_libraries(test_file_types PRIVATE file_types)
add_test(NAME file_types COMMAND test_file_types)
set_property(TEST file_types PROPERTY LABELS "CXX")
