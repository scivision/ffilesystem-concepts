set(CMAKE_C_STANDARD 11)

set(CMAKE_REQUIRED_DEFINITIONS -D__STDC_WANT_LIB_EXT1__=1)

check_symbol_exists(__STDC_LIB_EXT1__ "stdlib.h;string.h" HAVE_STDC_LIB_EXT1)

if(NOT HAVE_STDC_LIB_EXT1)
  message(STATUS "secure _s str*cpy() functions not available")
  return()
endif()

add_executable(test_strcpy_s test_strcpy_s.c)
add_test(NAME test_strcpy_s COMMAND test_strcpy_s)
