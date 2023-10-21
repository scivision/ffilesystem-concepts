set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_executable(test_home_dir test_home_dir.cpp)
target_link_libraries(test_home_dir PRIVATE $<$<BOOL:${WIN32}>:Userenv>)

add_test(NAME HomeDir COMMAND test_home_dir)
