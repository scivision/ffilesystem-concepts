add_executable(test_copytree test_copytree.cpp)
target_link_libraries(test_copytree PRIVATE copytree)

add_test(NAME CopyTree COMMAND test_copytree)
set_property(TEST CopyTree PROPERTY DISABLED $<BOOL:${MINGW}>)
