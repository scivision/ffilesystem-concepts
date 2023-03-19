if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0") OR
    CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC")
    link_libraries(stdc++fs stdc++)
    set(CMAKE_REQUIRED_LIBRARIES stdc++fs stdc++)
endif()

# fixes errors about needing -fPIE
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_POSITION_INDEPENDENT_CODE true)
endif()
