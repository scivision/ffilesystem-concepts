set_property(DIRECTORY PROPERTY LABELS "mkdtemp")

add_executable(test_home_dir test_home_dir.cpp)
target_link_libraries(test_home_dir PRIVATE $<$<BOOL:${WIN32}>:Userenv>)

add_test(NAME HomeDirEnv COMMAND test_home_dir)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.22)
  add_test(NAME HomeDirNoEnv COMMAND test_home_dir)
  set_property(TEST HomeDirNoEnv PROPERTY ENVIRONMENT_MODIFICATION "HOME=unset:;USERPROFILE=unset:")
endif()
