set_property(DIRECTORY PROPERTY LABELS "Cygwin")

add_executable(test_cygpath cygpath.cpp)

add_test(NAME CygwinPath COMMAND test_cygpath)
