set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_executable(test_mkdtemp test_mkdtemp.cpp)
target_link_libraries(test_mkdtemp PRIVATE $<$<NOT:$<BOOL:${HAVE_MKDTEMP}>>:mkdtemp>)
target_compile_definitions(test_mkdtemp PRIVATE
$<$<BOOL:${HAVE_MKDTEMP}>:HAVE_MKDTEMP>
)

add_test(NAME test_mkdtemp COMMAND test_mkdtemp)

if(fortran)
add_executable(test_mkdtemp_fortran test_mkdtemp.f90)
target_link_libraries(test_mkdtemp_fortran PRIVATE mkdtemp_f)
add_test(NAME test_mkdtemp_fortran COMMAND test_mkdtemp_fortran)

endif()
