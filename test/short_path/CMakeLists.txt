set_property(DIRECTORY PROPERTY LABELS "short_path;windows")

add_executable(short_path_windows short_path_windows.cpp)
add_test(NAME short_path_windows COMMAND short_path_windows)
set_property(TEST short_path_windows PROPERTY LABELS "CXX")
