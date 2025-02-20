function(wxt_make_package target packetName friendlyName version)
  file(GLOB_RECURSE RES_FILES ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/app/*)

  # target to lower case
  string(TOLOWER ${target} lower_target)
  # Remove all spaces
  string(REGEX REPLACE " " "" lower_target ${lower_target})

  set(args "-DargTarget=${target}")
  list(APPEND args "-DargPacketName=${packetName}")
  list(APPEND args "-DargFriendlyName=${friendlyName}")
  list(APPEND args "-DargVersion=${version}")
  list(APPEND args "-DargWorkingDir=${CMAKE_BINARY_DIR}/deb/${target}")
  list(APPEND args "-DargLowerTargetName=${lower_target}")
  list(APPEND args "-DargTool=${CMAKE_SOURCE_DIR}/tools/linuxdeployqt")
  list(APPEND args "-DargSrcDir=${CMAKE_SOURCE_DIR}")

  # cmake-format: off
  add_custom_target(${target}-package
    COMMAND ${CMAKE_COMMAND} -E remove_directory {CMAKE_BINARY_DIR}/deb/${target} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/deb/${target} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/app ${CMAKE_BINARY_DIR}/deb/${target} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${target}> ${CMAKE_BINARY_DIR}/deb/${target}/usr/bin/${packetName}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/res/files/history.txt ${CMAKE_BINARY_DIR}/deb/${target}/usr/share/doc/${packetName}/history.txt
    COMMAND ${CMAKE_COMMAND} ${args} -P ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/deb_maker.cmake
    SOURCES ${RES_FILES})
  # cmake-format: on
endfunction()
