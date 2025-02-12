set(WX_TOOLS_BINARY_DIR ${CMAKE_BINARY_DIR}/assets)

function(wxt_make_zip target)
  if(WIN32)
    string(TOLOWER ${target} lower_target)
    string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} lower_system_name)
    # string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} lower_system_processor)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(TAR_FILE_NAME ${lower_target}-${lower_system_name}-x64)
    else()
      set(TAR_FILE_NAME ${lower_target}-${lower_system_name}-x86)
    endif()
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E tar "cf" ${TAR_FILE_NAME}.zip "--format=zip" ${target}
      WORKING_DIRECTORY ${WX_TOOLS_BINARY_DIR}
      COMMENT "Creating zip package")
  endif()
endfunction()
