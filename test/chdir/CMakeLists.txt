set_property(DIRECTORY PROPERTY LABELS "chdir")

add_executable(chdir_c chdir.c)
add_test(NAME chdir_c COMMAND chdir_c ${CMAKE_CURRENT_SOURCE_DIR})
# avoid dealing with Windows path separators regex

add_executable(chdir_cpp chdir.cpp)
add_test(NAME chdir_cpp COMMAND chdir_cpp ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TEST chdir_cpp PROPERTY PASS_REGULAR_EXPRESSION "New current path: ${CMAKE_CURRENT_SOURCE_DIR}")
