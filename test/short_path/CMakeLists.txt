set_property(DIRECTORY PROPERTY LABELS "short_path;windows")

add_library(short OBJECT ${PROJECT_SOURCE_DIR}/src/short_path/short_path.cpp)
target_include_directories(short PUBLIC ${PROJECT_SOURCE_DIR}/src/short_path)

add_executable(short_path_windows short_path_windows.cpp)
target_link_libraries(short_path_windows PRIVATE short)

add_test(NAME short_path_windows COMMAND short_path_windows)
set_property(TEST short_path_windows PROPERTY LABELS "CXX")
