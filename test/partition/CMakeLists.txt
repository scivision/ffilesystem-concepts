set_property(DIRECTORY PROPERTY LABELS "partition")

add_executable(test_partition_cpp test_partition.cpp)

add_test(NAME partitionCpp COMMAND test_partition_cpp)
set_property(TEST partitionCpp PROPERTY LABELS "CXX")
