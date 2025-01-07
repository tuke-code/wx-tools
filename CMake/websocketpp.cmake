set(packet_name "websocketpp-0.8.2")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ThirdParty)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
