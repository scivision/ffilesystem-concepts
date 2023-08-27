include(CheckIncludeFile)
include(CheckSymbolExists)

if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0") OR
    CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC")
    link_libraries(stdc++fs stdc++)
    set(CMAKE_REQUIRED_LIBRARIES stdc++fs stdc++)
endif()

if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
  add_compile_options($<$<AND:$<COMPILE_LANGUAGE:Fortran>,$<CONFIG:Release>>:-fno-backtrace>)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "IntelLLVM")
  add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-Rno-debug-disables-optimization>)
  add_link_options($<$<COMPILE_LANGUAGE:C,CXX>:-Rno-debug-disables-optimization>)
endif()

add_compile_definitions(
  "$<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<BOOL:${MSVC}>>:_CRT_SECURE_NO_WARNINGS;_CRT_NONSTDC_NO_WARNINGS>"
)

# fixes errors about needing -fPIE
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_POSITION_INDEPENDENT_CODE true)
endif()
