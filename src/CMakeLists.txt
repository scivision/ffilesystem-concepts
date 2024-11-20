add_library(ffilesystem ffilesystem.cpp locale.cpp)
target_include_directories(ffilesystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE locale.cpp PROPERTY COMPILE_OPTIONS $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-declarations>)
