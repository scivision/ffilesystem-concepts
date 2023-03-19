cmake_minimum_required(VERSION 3.20)

string(RANDOM LENGTH 8 ALPHABET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" Uname)
string(PREPEND Uname ${CMAKE_CURRENT_LIST_DIR}/cmake_)
string(TOLOWER ${Uname} Lname)
# creating Lname this way deliberately forces the drive/root to be lower case,
# which in general is not the case on Windows and macOS:
# * Windows upper case drive letter
# * macOS /Users/... some upper case letters

message(STATUS "touch file ${Lname}")
file(TOUCH ${Lname})

execute_process(COMMAND ${exe} "${Uname}"
OUTPUT_VARIABLE out OUTPUT_STRIP_TRAILING_WHITESPACE
)

file(REMOVE ${Lname})

# We have to have CMake resolve the name on the filesystem too to have the
# the same case as the filesystem.
cmake_path(GET Lname FILENAME resolved)
string(PREPEND resolved ${CMAKE_CURRENT_LIST_DIR}/)

cmake_path(COMPARE "${resolved}" EQUAL "${out}" ok)

if(ok)
  message(STATUS "OK: canonical(${resolved}) resolves to ${out}")
else()
  message(FATAL_ERROR "canonical(${resolved}) does not resolve to ${out}")
endif()
