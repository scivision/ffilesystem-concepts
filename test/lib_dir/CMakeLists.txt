set_property(DIRECTORY PROPERTY LABLES "lib_dir")

if(fortran)

add_executable(test_lib_dir main.f90)
target_link_libraries(test_lib_dir PRIVATE get_lib)

add_test(NAME LibDirFortran COMMAND test_lib_dir)

endif()
