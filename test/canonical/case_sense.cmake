if(DEFINED case_sensitive)
  return()
endif()

string(RANDOM LENGTH 8 ALPHABET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" actual_name)
string(PREPEND actual_name ${CMAKE_CURRENT_BINARY_DIR}/cmake_)
string(TOLOWER ${actual_name} Lname)
# creating Lname this way deliberately forces the drive/root to be lower case,
# which in general is not the case on Windows and macOS:
# * Windows upper case drive letter
# * macOS /Users/... some upper case letters

if(EXISTS ${actual_name})
  set(case_sensitive false CACHE BOOL "case insensitive build filesystem")
  message(STATUS "touch file ${Lname}")
  file(TOUCH ${Lname})
else()
  set(case_sensitive true CACHE BOOL "case sensitive build filesystem")
endif()

message(STATUS "case_sensitive=${case_sensitive}")

set(actual_name ${actual_name} CACHE FILEPATH "actual path of file" FORCE)
set(Lname ${Lname} CACHE FILEPATH "lower case form of file path" FORCE)
