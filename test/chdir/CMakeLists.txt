set_property(DIRECTORY PROPERTY LABELS "chdir")

# PASS_REGULAR_EXPRESSION too fragile for path separate, Cygwin, WSL, etc.

# -- C
add_executable(chdir_c chdir.c)
add_test(NAME chdir_c COMMAND chdir_c ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TEST chdir_c PROPERTY LABELS "C")

# -- C++
add_executable(test_chdir_cpp chdir.cpp)
target_link_libraries(test_chdir_cpp PRIVATE chdir_cpp)

add_test(NAME chdirCpp COMMAND test_chdir_cpp ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TEST chdirCpp PROPERTY LABELS "CXX")

# -- Fortran
if(fortran)
  add_executable(test_chdir_fortran chdir.f90)
  target_link_libraries(test_chdir_fortran PRIVATE chdir_cpp)

  add_test(NAME chdirFortran COMMAND test_chdir_fortran ${CMAKE_CURRENT_SOURCE_DIR})
endif()
