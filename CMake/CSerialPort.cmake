# https://github.com/itas109/CSerialPort

set(packet_name "CSerialPort-4.3.1")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ThirdParty)
endif()

include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
