# https://github.com/palacaze/sigslot

set(packet_name "sigslot-1.2.2")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/3rd/${packet_name})
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/3rd/${packet_name}.zip
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/3rd)
endif()

include_directories(${CMAKE_SOURCE_DIR}/3rd/${packet_name}/include)
