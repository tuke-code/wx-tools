set(packet_name "wxWidgets-3.2.6")

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${packet_name}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/3rd)
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/3rd/${packet_name}/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar x ${CMAKE_SOURCE_DIR}/3rd/${packet_name}.7z
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/3rd/${packet_name})
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/3rd/${packet_name})
include_directories(${CMAKE_SOURCE_DIR}/3rd/${packet_name}/include)
