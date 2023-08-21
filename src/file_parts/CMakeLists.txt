set_property(DIRECTORY PROPERTY LABELS "file_parts")

add_library(file_parts OBJECT file_parts.cpp)
target_link_libraries(file_parts PRIVATE ffilesystem)
