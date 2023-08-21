set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_executable(test_mkdtemp test_mkdtemp.cpp)
target_link_libraries(test_mkdtemp PRIVATE $<$<NOT:$<BOOL:${HAVE_MKDTEMP}>>:mkdtemp>)
target_compile_definitions(test_mkdtemp PRIVATE
$<$<BOOL:${HAVE_MKDTEMP}>:HAVE_MKDTEMP>
)

add_test(NAME test_mkdtemp COMMAND test_mkdtemp)
