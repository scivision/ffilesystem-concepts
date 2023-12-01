set_property(DIRECTORY PROPERTY LABLES "lib_dir")

# shared: prints full path to shared library file  e.g. /path/to/mylib.[dylib,so,dll]
# static: prints full path to main executable file  e.g.  /path/to/main.exe

if(NOT (WIN32 OR CYGWIN))
  set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_DL_LIBS})
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)
  endif()
  check_symbol_exists(dladdr "dlfcn.h" HAVE_DLADDR)
  if(NOT HAVE_DLADDR)
    message(STATUS "dladdr() not found in dl library ${CMAKE_DL_LIBS}")
  endif()
endif()

add_library(get_lib SHARED ${PROJECT_SOURCE_DIR}/src/lib_dir/lib.c)
if(WIN32 OR CYGWIN)
  target_compile_definitions(get_lib PRIVATE MY_DLL_NAME="$<TARGET_FILE_NAME:get_lib>")
else()
  target_link_libraries(get_lib PRIVATE ${CMAKE_DL_LIBS})
  target_compile_definitions(get_lib PRIVATE $<$<BOOL:${HAVE_DLADDR}>:HAVE_DLADDR>)
endif()

if(fortran)

add_executable(test_lib_dir main.f90)
target_link_libraries(test_lib_dir PRIVATE get_lib)

add_test(NAME LibDirFortran COMMAND test_lib_dir)

set_property(TEST LibDirFortran PROPERTY LABELS "Fortran")

endif()
