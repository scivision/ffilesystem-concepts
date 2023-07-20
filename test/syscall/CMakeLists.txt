set_property(DIRECTORY PROPERTY LABELS "syscall")

add_executable(test_exec test_exec.c)
target_link_libraries(test_exec PRIVATE exec)

add_test(NAME Exec COMMAND test_exec)

set_property(TEST Exec PROPERTY LABELS "C")

if(WIN32)
add_executable(test_create_process test_create_process.c)
target_link_libraries(test_create_process PRIVATE create_process)

add_test(NAME CreateProcess COMMAND test_create_process)
set_property(TEST CreateProcess PROPERTY LABELS "C")
endif()
