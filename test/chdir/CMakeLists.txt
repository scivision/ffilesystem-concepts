set_property(DIRECTORY PROPERTY LABELS "chdir")

# PASS_REGULAR_EXPRESSION too fragile for path separate, Cygwin, WSL, etc.

add_executable(chdir_c chdir.c)
target_compile_definitions(chdir_c PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)
add_test(NAME chdir_c COMMAND chdir_c ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TEST chdir_c PROPERTY LABELS "C")

add_executable(chdir_cpp chdir.cpp)
add_test(NAME chdir_cpp COMMAND chdir_cpp ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TEST chdir_cpp PROPERTY LABELS "Cpp")
