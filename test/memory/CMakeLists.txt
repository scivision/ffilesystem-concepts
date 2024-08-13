set_property(DIRECTORY PROPERTY LABELS "memory")

add_executable(test_memory_c test_memory.c)
add_test(NAME memoryC COMMAND test_memory_c)
set_property(TEST memoryC PROPERTY LABELS "C")
