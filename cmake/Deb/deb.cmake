function(wxt_make_deb target packetName friendlyName version)
  file(GLOB_RECURSE RES_FILES ${CMAKE_SOURCE_DIR}/cmake/Deb/*)

  set(args "-DargTarget=${target}")
  list(APPEND args "-DargPacketName=${packetName}")
  list(APPEND args "-DargFriendlyName=${friendlyName}")
  list(APPEND args "-DargVersion=${version}")
  list(APPEND args "-DargWorkingDir=${CMAKE_BINARY_DIR}/deb/${target}")

  # cmake-format: off
  add_custom_target(${target}-deb
    COMMAND ${CMAKE_COMMAND} -E remove_directory {CMAKE_BINARY_DIR}/deb/${target} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/deb/${target} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/cmake/Deb/app ${CMAKE_BINARY_DIR}/deb/${target} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/deb/${target}/opt/${packetName}
    COMMAND ${CMAKE_COMMAND} ${args} -P ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/deb_maker.cmake
    SOURCES ${RES_FILES})
  # cmake-format: on
endfunction()
