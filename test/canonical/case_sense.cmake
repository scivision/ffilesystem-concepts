set(cased_name ${CMAKE_CURRENT_BINARY_DIR}/CaseSensitiveCheck)
string(TOLOWER ${cased_name} lower_name)

if(NOT EXISTS ${cased_name})
  message(STATUS "touch file ${cased_name}")
  file(TOUCH ${cased_name})
endif()

file(REAL_PATH ${lower_name} actual_name)

message(VERBOSE "Actual name: ${actual_name}  cased_name ${cased_name}")

if(cased_name STREQUAL actual_name)
  set(case_sensitive false)
else()
  set(case_sensitive true)
endif()

cmake_path(GET actual_name ROOT_PATH root)

message(STATUS "Case Sensitive filesystem ${root} ${case_sensitive}")
