set_property(DIRECTORY PROPERTY LABELS "canonical")

# --- C

add_library(canonical_c ${PROJECT_SOURCE_DIR}/src/canonical/canonical.c)
target_include_directories(canonical_c PUBLIC ${PROJECT_SOURCE_DIR}/src/canonical/)

# --- C++

add_library(windows_symlink OBJECT ${PROJECT_SOURCE_DIR}/src/canonical/windows_read_symlink.cpp)
target_include_directories(windows_symlink INTERFACE ${PROJECT_SOURCE_DIR}/src/canonical/)

add_library(canonical_cpp ${PROJECT_SOURCE_DIR}/src/canonical/canonical.cpp)
target_include_directories(canonical_cpp INTERFACE ${PROJECT_SOURCE_DIR}/src/canonical/)
target_link_libraries(canonical_cpp PRIVATE windows_symlink)


# --- tests
set(langs CXX)

add_executable(test_canonical_CXX test_canonical.cpp)
target_link_libraries(test_canonical_CXX PRIVATE canonical_cpp)

if(fortran)
  list(APPEND langs Fortran)
  add_executable(test_canonical_Fortran test_canonical.f90)
  target_link_libraries(test_canonical_Fortran PRIVATE canonical_c)
endif()

file(CREATE_LINK ${CMAKE_CURRENT_LIST_FILE} ${CMAKE_CURRENT_BINARY_DIR}/test.lnk SYMBOLIC)

foreach(lang IN LISTS langs)
  add_test(NAME ResolveLink${lang} COMMAND test_canonical_${lang} ${CMAKE_CURRENT_BINARY_DIR}/test.lnk)
  add_test(NAME CanonicalNotFound${lang} COMMAND test_canonical_${lang} "not-exist-file")
endforeach()

# --- Ccase sensitive
include(${CMAKE_CURRENT_LIST_DIR}/case_sense.cmake)

foreach(lang IN ITEMS CXX)
  add_test(NAME CaseInsensitive${lang} COMMAND test_canonical_${lang} ${lower_name})
endforeach()

# --- test properties

set_property(TEST CaseInsensitiveCXX ResolveLinkCXX PROPERTY LABELS "CXX")

set_property(TEST CaseInsensitiveCXX PROPERTY DISABLED ${case_sensitive})
set_property(TEST ResolveLinkCXX PROPERTY PASS_REGULAR_EXPRESSION "CMakeLists.txt\n$")

if(WIN32 AND BUILD_SHARED_LIBS)
    get_property(test_names DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
    set_property(TEST ${test_names} PROPERTY ENVIRONMENT_MODIFICATION "PATH=path_list_append:${PROJECT_BINARY_DIR}/bin")
endif()
