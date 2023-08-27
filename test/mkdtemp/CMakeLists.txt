set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_executable(test_mkdtemp test_mkdtemp.cpp)
target_link_libraries(test_mkdtemp PRIVATE mkdtemp)
add_test(NAME test_mkdtemp COMMAND test_mkdtemp)

if(fortran)
    add_executable(test_mkdtemp_fortran test_mkdtemp.f90)
    target_link_libraries(test_mkdtemp_fortran PRIVATE mkdtemp)
    add_test(NAME test_mkdtemp_fortran COMMAND test_mkdtemp_fortran)
endif()
