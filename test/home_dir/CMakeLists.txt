set_property(DIRECTORY PROPERTY LABELS "home_dir")

add_executable(test_home_dir test_home_dir.cpp)
target_link_libraries(test_home_dir PRIVATE "$<$<BOOL:${WIN32}>:Userenv;Advapi32>")

add_test(NAME HomeDirEnv COMMAND test_home_dir)
set_property(TEST HomeDirEnv PROPERTY LABELS "CXX")

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.22)
  add_test(NAME HomeDirNoEnv COMMAND test_home_dir)
  set_property(TEST HomeDirNoEnv PROPERTY ENVIRONMENT_MODIFICATION "HOME=unset:;USERPROFILE=unset:")
  set_property(TEST HomeDirNoEnv PROPERTY LABELS "CXX")
endif()
