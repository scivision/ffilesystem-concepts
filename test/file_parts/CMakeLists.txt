set_property(DIRECTORY PROPERTY LABELS "file_parts")

add_library(file_parts OBJECT ${PROJECT_SOURCE_DIR}/src/file_parts/file_parts.cpp)
target_link_libraries(file_parts PRIVATE ffilesystem)

if(NOT fortran)
  return()
endif()

add_executable(test_file_parts file_parts.f90)
set_property(TARGET test_file_parts PROPERTY LINKER_LANGUAGE Fortran)
# Intel/NVHPC needs linker_language fortran else error "undefined reference to `main'"
target_link_libraries(test_file_parts PRIVATE file_parts)
add_test(NAME file_parts COMMAND test_file_parts)
set_property(TEST file_parts PROPERTY LABELS "Fortran")
