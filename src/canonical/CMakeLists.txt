set_property(DIRECTORY PROPERTY LABELS "canonical")

include(CheckCXXSymbolExists)

check_cxx_symbol_exists(__cpp_lib_starts_ends_with "string" HAVE_STRING_START_WITH)

# --- C

add_library(canonical_c canonical.c
$<$<BOOL:${WIN32}>:windows_read_symlink.c>
)
target_include_directories(canonical_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# --- C++

add_library(windows_symlink OBJECT windows_read_symlink.cpp)
target_include_directories(windows_symlink INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(canonical_cpp canonical.cpp)
target_include_directories(canonical_cpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(canonical_cpp PRIVATE windows_symlink)
