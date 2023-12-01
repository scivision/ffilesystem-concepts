set_property(DIRECTORY PROPERTY LABELS "copytree")

add_library(copytree ${PROJECT_SOURCE_DIR}/src/copytree/copytree.cpp)
target_include_directories(copytree PUBLIC ${PROJECT_SOURCE_DIR}/src/copytree/)

add_executable(test_copytree test_copytree.cpp)
target_link_libraries(test_copytree PRIVATE copytree)

add_test(NAME CopyTree COMMAND test_copytree)
set_property(TEST CopyTree PROPERTY DISABLED $<BOOL:${MINGW}>)
set_property(TEST CopyTree PROPERTY LABELS "CXX")
