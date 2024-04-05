set_property(DIRECTORY PROPERTY LABLES "lib_dir")

# shared: prints full path to shared library file  e.g. /path/to/mylib.[dylib,so,dll]
# static: prints full path to main executable file  e.g.  /path/to/main.exe

add_library(get_lib SHARED ${PROJECT_SOURCE_DIR}/src/lib_dir/lib.c)
if(WIN32 OR CYGWIN)
  target_compile_definitions(get_lib PRIVATE MY_DLL_NAME="$<TARGET_FILE_NAME:get_lib>")
else()
  target_link_libraries(get_lib PRIVATE ${CMAKE_DL_LIBS})
endif()

if(fortran)

add_executable(test_lib_dir main.f90)
target_link_libraries(test_lib_dir PRIVATE get_lib)

add_test(NAME lib_dir_Fortran COMMAND test_lib_dir)

set_tests_properties(lib_dir_Fortran PROPERTIES
PASS_REGULAR_EXPRESSION $<TARGET_FILE:get_lib>
LABELS "Fortran"
)

endif()
