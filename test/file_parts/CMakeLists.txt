set_property(DIRECTORY PROPERTY LABELS "file_parts")

if(fortran)
add_executable(test_file_parts file_parts.f90)
set_property(TARGET test_file_parts PROPERTY LINKER_LANGUAGE Fortran)
# Intel/NVHPC needs linker_language fortran else error "undefined reference to `main'"
target_link_libraries(test_file_parts PRIVATE file_parts)
add_test(NAME file_parts COMMAND test_file_parts)
endif()
