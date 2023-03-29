set_property(DIRECTORY PROPERTY LABELS "canonical")

# --- C

add_executable(test_canonical_c test_canonical.c)
target_link_libraries(test_canonical_c PRIVATE canonical_c)
target_compile_definitions(test_canonical_c PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

add_test(NAME CanonicalNotFoundC COMMAND test_canonical_c "not-exist-file")

file(CREATE_LINK ${CMAKE_CURRENT_LIST_FILE} ${CMAKE_CURRENT_BINARY_DIR}/test.lnk SYMBOLIC)
add_test(NAME ResolveLinkC
COMMAND test_canonical_c ${CMAKE_CURRENT_BINARY_DIR}/test.lnk
)

include(${CMAKE_CURRENT_LIST_DIR}/case_sense.cmake)

add_test(NAME CaseInsensitiveC
COMMAND test_canonical_c ${Lname}
)

# --- C++

add_executable(test_canonical_cpp test_canonical.cpp)
target_link_libraries(test_canonical_cpp PRIVATE canonical_cpp)

add_test(NAME CanonicalNotFoundCPP COMMAND test_canonical_cpp "not-exist-file")

add_test(NAME ResolveLinkCPP
COMMAND test_canonical_cpp ${CMAKE_CURRENT_BINARY_DIR}/test.lnk
)

add_test(NAME CaseInsensitiveCPP
COMMAND test_canonical_cpp ${Lname})
# --- Fortran
if(fortran)
  add_executable(exe_dir_f test_canonical.f90)
  target_link_libraries(exe_dir_f PRIVATE canonical_c)

  add_test(NAME FortranExeDir COMMAND exe_dir_f)
endif()


# --- test properties

set_property(TEST CaseInsensitiveC CaseInsensitiveCPP PROPERTY DISABLED ${case_sensitive})
set_property(TEST ResolveLinkC ResolveLinkCPP PROPERTY PASS_REGULAR_EXPRESSION "CMakeLists.txt\n$")

if(WIN32 AND BUILD_SHARED_LIBS)
    get_property(test_names DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
    set_property(TEST ${test_names} PROPERTY ENVIRONMENT_MODIFICATION "PATH=path_list_append:${PROJECT_BINARY_DIR}/bin")
endif()
