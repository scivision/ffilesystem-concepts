include(CheckIncludeFile)
include(CheckSymbolExists)

if(CMAKE_VERSION VERSION_LESS 3.25 AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(LINUX true)
endif()

if(NOT MSVC AND NOT DEFINED ffilesystem_stdcpp_version)

message(CHECK_START "Checking C++ standard library version")
# Intel, IntelLLVM and NVHPC on Linux use GNU libstdc++, so we need to extract the libstdc++ version
try_run(ffilesystem_stdcpp_run ffilesystem_stdcpp_build_ok
  ${CMAKE_CURRENT_BINARY_DIR}/libstdcpp_version
  SOURCES ${CMAKE_CURRENT_LIST_DIR}/libstdcpp_version.cpp
  RUN_OUTPUT_VARIABLE _stdcpp_version
)

if(NOT ffilesystem_stdcpp_run EQUAL 0)
  message(CHECK_FAIL "Could not determine GNU libstdc++ version ${ffilesystem_stdcpp_build_ok} ${ffilesystem_stdcpp_run} ${_stdcpp_version}")
else()
  string(STRIP "${_stdcpp_version}" _stdcpp_version)
  set(ffilesystem_stdcpp_version "${_stdcpp_version}" CACHE STRING "C++ standard library version")
  message(CHECK_PASS "${ffilesystem_stdcpp_version}")
endif()

endif()

if(ffilesystem_stdcpp_run EQUAL 0)
  if(ffilesystem_stdcpp_version MATCHES "GNU ([0-9]+)")
    if(CMAKE_MATCH_1 LESS 9)
      set(GNU_stdfs stdc++fs stdc++)
    else()
      message(VERBOSE "GNU libstdc++ ${ffilesystem_stdcpp_version} is new enough to not need -lstdc++")
    endif()
  else()
    message(VERBOSE "Did not determine GNU libstdc++ version ${ffilesystem_stdcpp_version}")
  endif()
endif()


if(GNU_stdfs)
  set(CMAKE_REQUIRED_LIBRARIES ${GNU_stdfs})
  message(STATUS "adding C++ library flags ${GNU_stdfs}")
  link_libraries(${GNU_stdfs})
endif()


add_compile_options("$<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang,GNU>:-Wold-style-cast>")

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
