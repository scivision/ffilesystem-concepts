set_property(DIRECTORY PROPERTY LABELS "syscall")

add_library(exec_C ${PROJECT_SOURCE_DIR}/src/syscall/exec.c)
target_include_directories(exec_C INTERFACE ${PROJECT_SOURCE_DIR}/src/syscall)

add_library(exec_CXX ${PROJECT_SOURCE_DIR}/src/syscall/exec.cpp)
target_include_directories(exec_CXX INTERFACE ${PROJECT_SOURCE_DIR}/src/syscall)


if(WIN32)
  add_library(create_process ${PROJECT_SOURCE_DIR}/src/syscall/CreateProcess.c)
  target_include_directories(create_process PUBLIC ${PROJECT_SOURCE_DIR}/src/syscall)
endif()

add_executable(test_exec_C test_exec.c)
target_link_libraries(test_exec_C PRIVATE exec_C)
add_test(NAME ExecC COMMAND test_exec_C)
set_property(TEST ExecC PROPERTY LABELS "C")

add_executable(test_exec_CXX test_exec.cpp)
target_link_libraries(test_exec_CXX PRIVATE exec_CXX)
add_test(NAME ExecCXX COMMAND test_exec_CXX)
set_property(TEST ExecCXX PROPERTY LABELS "CXX")

if(WIN32)
add_executable(test_create_process test_create_process.c)
target_link_libraries(test_create_process PRIVATE create_process)

add_test(NAME CreateProcess COMMAND test_create_process)
set_property(TEST CreateProcess PROPERTY LABELS "C")
endif()
