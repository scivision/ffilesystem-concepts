add_executable(bench_is_dir bench_is_dir.cpp)
add_test(NAME is_dir COMMAND bench_is_dir)
set_property(TEST is_dir PROPERTY LABELS "CXX")
