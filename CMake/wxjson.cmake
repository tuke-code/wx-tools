# https://sourceforge.net/projects/wxcode/files/Components/ https://github.com/catalinr/wxjson.git
set(packet_name "wxjson-master")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ThirdParty)
endif()

include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/include)
