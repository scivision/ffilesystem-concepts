add_executable(test_wide_cpp test_wide.cpp)

# the MSVC compiler requires this option or it triples the size of the non-English L"" strings and fails the test
# Windows oneAPI is fine without this flag
target_compile_options(test_wide_cpp PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
target_include_directories(test_wide_cpp PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(test_wide_cpp PRIVATE ffilesystem)

add_test(NAME test_wide_cpp COMMAND test_wide_cpp)

add_executable(print_wide_cpp print_wide.cpp)
