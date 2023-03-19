set_property(DIRECTORY PROPERTY LABELS "file_types")

add_library(file_types file_status.cpp)
target_compile_definitions(file_types PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)
target_include_directories(file_types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(file_types PRIVATE "$<$<BOOL:${WIN32}>:wsock32;ws2_32>") # Iphlpapi)
