# https://github.com/lammertb/libcrc

set(packet_name "libcrc-master")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ThirdParty)
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/tab/gentab64.inc)
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/ThirdParty/libcrc
            ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/tab)
endif()

file(GLOB LIBCRC_H ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/include/*.*)
file(GLOB LIBCRC_C ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/src/*.*)

include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}/include)
add_library(libcrc STATIC ${LIBCRC_H} ${LIBCRC_C})
set_target_properties(libcrc PROPERTIES FOLDER "ThirdParty")
