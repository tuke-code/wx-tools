function(wxt_make_app_image target packetName friendlyName version)
  file(GLOB_RECURSE RES_FILES ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/appimage/*)

  set(workingDir ${CMAKE_BINARY_DIR}/appimage/${friendlyName})
  set(args "-DargTarget=${target}")
  list(APPEND args "-DargFriendlyName=${friendlyName}")
  list(APPEND args "-DargPacketName=${packetName}")
  list(APPEND args "-DargVersion=${version}")
  list(APPEND args "-DargWorkingDir=${workingDir}")
  list(APPEND args "-DargTool=${CMAKE_BINARY_DIR}/tools/linuxdeployqt")

  # cmake-format: off
  add_custom_target(${target}-appimage
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${workingDir} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/appimage ${workingDir} "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${workingDir}/bin "||" ${CMAKE_COMMAND} -E true
    COMMAND ${CMAKE_COMMAND} ${args} -P ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/app_image_maker.cmake
    SOURCES ${RES_FILES})
   # cmake-format: on
endfunction()
