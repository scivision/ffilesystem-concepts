set_property(DIRECTORY PROPERTY LABELS "file_types")

add_library(file_types ${PROJECT_SOURCE_DIR}/src/file_types/file_status.cpp)
target_include_directories(file_types PUBLIC ${PROJECT_SOURCE_DIR}/src/file_types)
target_link_libraries(file_types PRIVATE "$<$<BOOL:${WIN32}>:wsock32;ws2_32>") # Iphlpapi)

add_executable(test_file_types test_file_types.cpp)
target_link_libraries(test_file_types PRIVATE file_types)
add_test(NAME file_types COMMAND test_file_types)
set_property(TEST file_types PROPERTY LABELS "CXX")
