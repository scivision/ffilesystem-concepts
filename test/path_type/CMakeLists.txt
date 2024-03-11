if(fortran)
add_executable(path_type main.f90)

add_test(NAME path_type COMMAND path_type)
set_property(TEST path_type PROPERTY LABELS "Fortran")
endif()
