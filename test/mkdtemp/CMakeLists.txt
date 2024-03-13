set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_library(mkdtemp OBJECT ${PROJECT_SOURCE_DIR}/src/mkdtemp/mkdtemp.cpp)
target_include_directories(mkdtemp PUBLIC ${PROJECT_SOURCE_DIR}/src/mkdtemp)
target_link_libraries(mkdtemp PRIVATE ffilesystem)

add_executable(test_mkdtemp_cpp test_mkdtemp.cpp)
target_link_libraries(test_mkdtemp_cpp PRIVATE mkdtemp)
add_test(NAME mkdtempCpp COMMAND test_mkdtemp_cpp)
set_property(TEST mkdtempCpp PROPERTY LABELS "CXX")

if(fortran)
    add_executable(test_mkdtemp_fortran test_mkdtemp.f90)
    target_link_libraries(test_mkdtemp_fortran PRIVATE mkdtemp)
    set_property(TARGET test_mkdtemp_fortran PROPERTY LINKER_LANGUAGE Fortran)
    # Intel/NVHPC needs linker_language fortran else error "undefined reference to `main'"


    add_test(NAME mkdtemp_fortran COMMAND test_mkdtemp_fortran)
    set_property(TEST mkdtemp_fortran PROPERTY LABELS "Fortran")
endif()
