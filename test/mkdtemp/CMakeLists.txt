set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_executable(test_mkdtemp_cpp test_mkdtemp.cpp)
target_link_libraries(test_mkdtemp_cpp PRIVATE mkdtemp)
add_test(NAME mkdtempCpp COMMAND test_mkdtemp_cpp)
set_property(TEST mkdtempCpp PROPERTY LABELS "CXX")

if(fortran)
    add_executable(test_mkdtemp_fortran test_mkdtemp.f90)
    target_link_libraries(test_mkdtemp_fortran PRIVATE mkdtemp)

    add_test(NAME mkdtemp_fortran COMMAND test_mkdtemp_fortran)
    set_property(TEST mkdtemp_fortran PROPERTY LABELS "Fortran")
endif()
