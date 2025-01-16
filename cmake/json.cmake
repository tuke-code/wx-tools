# https://github.com/nlohmann/json
set(packet_name "json-3.11.3")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/3rd/${packet_name})
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/3rd/${packet_name}.zip
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/3rd)
endif()

include_directories(${CMAKE_SOURCE_DIR}/3rd/${packet_name}/single_include)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rd/${packet_name})
