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

check_symbol_exists(mkdtemp "stdlib.h" HAVE_MKDTEMP)
check_include_file("stdint.h" HAVE_STDINT_H)
check_include_file("config.h" HAVE_CONFIG_H)
check_include_file("unistd.h" HAVE_UNISTD_H)

# fixes errors about needing -fPIE
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_POSITION_INDEPENDENT_CODE true)
endif()
