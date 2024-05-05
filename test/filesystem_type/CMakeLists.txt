set_property(DIRECTORY PROPERTY LABELS "filesystem_type")

add_library(filesystem_type OBJECT ../../src/filesystem_type/filesystem_type.cpp)
target_include_directories(filesystem_type PUBLIC ../../src/filesystem_type)

add_executable(test_filesystem_type_cpp test_filesystem_type.cpp)
target_link_libraries(test_filesystem_type_cpp PRIVATE filesystem_type)

add_test(NAME test_filesystem_type_Cpp COMMAND test_filesystem_type_cpp)
set_property(TEST test_filesystem_type_Cpp PROPERTY LABELS "CXX")
