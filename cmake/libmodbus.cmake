# https://github.com/stephane/libmodbus
set(packet_name "libmodbus-3.1.11")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/3rd/${packet_name})
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/3rd/${packet_name}.zip
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/3rd)
endif()

set(work_dir ${CMAKE_SOURCE_DIR}/3rd/${packet_name}/src/win32)
set(target_dir ${CMAKE_SOURCE_DIR}/3rd/${packet_name}/src)
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/3rd/${packet_name}/src/config.h)
  execute_process(COMMAND cscript configure.js WORKING_DIRECTORY ${work_dir})
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${work_dir}/config.h ${target_dir})
endif()

file(GLOB h_files ${target_dir}/*.h)
file(GLOB c_files ${target_dir}/*.c)
include_directories(${target_dir})
add_library(libmodbus STATIC ${h_files} ${c_files})
target_link_libraries(libmodbus PUBLIC ws2_32)
set_target_properties(libmodbus PROPERTIES FOLDER "3rd")
