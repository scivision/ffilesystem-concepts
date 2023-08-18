set_property(DIRECTORY PROPERTY LABELS "file_parts")

if(fortran)
add_executable(test_file_parts file_parts.f90)
target_link_libraries(test_file_parts PRIVATE file_parts)
add_test(NAME file_parts COMMAND test_file_parts)
endif()
