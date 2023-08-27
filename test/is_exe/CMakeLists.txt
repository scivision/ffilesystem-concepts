set_property(DIRECTORY PROPERTY LABELS "is_exe")

add_executable(test_is_exe_cpp test_is_exe.cpp)
add_test(NAME is_exe_cpp COMMAND test_is_exe_cpp  ${CMAKE_CURRENT_LIST_FILE})
set_property(TEST is_exe_cpp PROPERTY LABELS "CXX")
