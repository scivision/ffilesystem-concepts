set_property(DIRECTORY PROPERTY LABELS "caseSensitive")

add_executable(case_sensitive_windows case_sensitive.cpp)
add_test(NAME case_sensitive_windows COMMAND case_sensitive_windows)
set_property(TEST case_sensitive_windows PROPERTY LABELS "Cpp")
