set_property(DIRECTORY PROPERTY LABELS "UNC")

if(NOT WIN32)
  return()
endif()

add_executable(test_unc_cpp test_unc.cpp)

add_test(NAME UNC_CPP COMMAND test_unc_cpp)
set_property(TEST UNC_CPP PROPERTY SKIP_RETURN_CODE 77)
