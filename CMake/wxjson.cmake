# * https://sourceforge.net/projects/wxcode/files/Components/
# * https://github.com/catalinr/wxjson.git
# * 需要将jsonreader.cpp文件中的union byte定义屏蔽
set(packet_name "wxjson-master")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ThirdParty)
endif()

include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
