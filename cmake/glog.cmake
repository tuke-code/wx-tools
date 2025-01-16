set(packet_name "glog-0.7.1")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name}.zip
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ThirdParty)
endif()

set(WITH_GTEST
    OFF
    CACHE BOOL "" FORCE)
set(WITH_GFLAGS
    OFF
    CACHE BOOL "" FORCE)
set(BUILD_TESTING
    OFF
    CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS
    OFF
    CACHE BOOL "Build shared libraries" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/${packet_name})
