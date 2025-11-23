add_library(ffilesystem ffilesystem.cpp locale.cpp)
target_include_directories(ffilesystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "15.0")
  set_source_files_properties(locale.cpp PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations")
  # this avoids
  # ffilesystem-concepts/src/locale.cpp:36:8: warning: 'template<class _Codecvt, class _Elem, class _Wide_alloc, class _Byte_alloc> class std::__cxx11::wstring_convert' is deprecated [-Wdeprecated-declarations]
  # 36 |   std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
endif()

set_property(SOURCE locale.cpp PROPERTY COMPILE_OPTIONS $<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-declarations>)
