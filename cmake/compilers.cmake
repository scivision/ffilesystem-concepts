include(CheckIncludeFile)
include(CheckSymbolExists)

if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0") OR
    CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC")
    link_libraries(stdc++fs stdc++)
    set(CMAKE_REQUIRED_LIBRARIES stdc++fs stdc++)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "IntelLLVM")
  add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-Rno-debug-disables-optimization>)
  add_link_options($<$<COMPILE_LANGUAGE:C,CXX>:-Rno-debug-disables-optimization>)
endif()

add_compile_definitions(
  "$<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS;_CRT_NONSTDC_NO_WARNINGS>"
)

check_include_file("unistd.h" HAVE_UNISTD_H)
set(_mkd_inc "stdlib.h")
if(HAVE_UNISTD_H)
  list(APPEND _mkd_inc "unistd.h")
endif()
check_symbol_exists(mkdtemp "${_mkd_inc}" HAVE_MKDTEMP)

# fixes errors about needing -fPIE
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_POSITION_INDEPENDENT_CODE true)
endif()
