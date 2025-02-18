# https://github.com/stephane/libmodbus
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/Modbus/wxtModbus.h")
  set(WXT_ENABLE_MODBUS OFF)
  return()
endif()

set(WXT_ENABLE_MODBUS ON)
set(packet_name "libmodbus-3.1.11")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/3rd/${packet_name})
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/3rd/${packet_name}.zip
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/3rd)
endif()

set(root_dir ${CMAKE_SOURCE_DIR}/3rd/${packet_name})
set(src_dir ${root_dir}/src)
include_directories(${src_dir})
if(WIN32)
  if(NOT EXISTS ${src_dir}/config.h)
    execute_process(COMMAND cscript configure.js WORKING_DIRECTORY ${src_dir}/win32)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${src_dir}/win32/config.h ${src_dir})
  endif()

  file(GLOB h_files ${src_dir}/*.h)
  file(GLOB c_files ${src_dir}/*.c)
  include_directories(${src_dir})
  add_library(libmodbus STATIC ${h_files} ${c_files})
  target_link_libraries(libmodbus PUBLIC ws2_32)
  set_target_properties(libmodbus PROPERTIES FOLDER "3rd")
endif()

if(LINUX)
  if(NOT EXISTS ${src_dir}/lib/libmodbus.la)
    # You should install autocmake libtool first.
    execute_process(COMMAND ./autogen.sh WORKING_DIRECTORY ${root_dir})
    execute_process(COMMAND ./configure --prefix=${root_dir} WORKING_DIRECTORY ${root_dir})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${root_dir}/config.h ${src_dir})
    execute_process(COMMAND make install WORKING_DIRECTORY ${root_dir})
  endif()
  link_directories(${src_dir}/lib)
endif()
