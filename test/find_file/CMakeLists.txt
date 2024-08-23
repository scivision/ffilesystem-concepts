set_property(DIRECTORY PROPERTY LABELS "find_file")

add_executable(test_find_file_cpp test_find_file.cpp)
add_test(NAME find_file_cpp COMMAND test_find_file_cpp CMakeLists.txt ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TEST find_file_cpp PROPERTY LABELS "CXX")
