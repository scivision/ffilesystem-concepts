set_property(DIRECTORY PROPERTY LABELS "maximums")

add_executable(max_path_windows max_path_components.cpp)
add_test(NAME max_path_windows COMMAND max_path_windows)
