# * argTarget: cmake target
# * argPacketName: packet name of deb packet
# * argFriendlyName: desktop entry file name
# * argVersion: the application version
# * argWorkingDir: working dir
# * argLowerTargetName: lower case of argTarget, such as "wxTools" -> "wxtools"
# * argTool: linuxdeployqt tool path
# * argSrcDir: project source dir
# * DargPackageType: deb or appimage

set(control_file ${argWorkingDir}/DEBIAN/control)
set(old_text argPacketName)
set(new_text ${argPacketName})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${control_file})

set(old_text argVersion)
set(new_text ${argVersion})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${control_file})

set(desktop_file_name_tmp ${argWorkingDir}/usr/share/applications/app.desktop)
set(desktop_file_name ${argWorkingDir}/usr/share/applications/${argPacketName}.desktop)
execute_process(COMMAND ${CMAKE_COMMAND} -E rename ${desktop_file_name_tmp} ${desktop_file_name})

set(old_text argFriendlyName)
set(new_text ${argFriendlyName})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})
set(old_text argPacketName)
set(new_text ${argPacketName})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})
set(old_text argTarget)
set(new_text ${argTarget})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})

# Rename the icon
set(old_text ${argWorkingDir}/usr/share/icons/icon.png)
set(new_text ${argWorkingDir}/usr/share/icons/${argPacketName}.png)
execute_process(COMMAND ${CMAKE_COMMAND} -E rename ${icon_file_name_tmp} ${icon_file_name})

set(old_text icon.png)
set(new_text ${argPacketName})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})

# cmake-format: off
if(${argPackageType} STREQUAL "deb")
  execute_process(COMMAND ${argTool} usr/share/applications/${argPacketName}.desktop -always-overwrite -bundle-non-qt-libs WORKING_DIRECTORY ${argWorkingDir})
  execute_process(COMMAND ${CMAKE_COMMAND} -E rm AppRun -f WORKING_DIRECTORY ${argWorkingDir})
  execute_process(COMMAND ${CMAKE_COMMAND} -E rm ${argPacketName}.desktop -f WORKING_DIRECTORY ${argWorkingDir})
  execute_process(COMMAND ${CMAKE_COMMAND} -E rm ${argPacketName}.png -f WORKING_DIRECTORY ${argWorkingDir})
  execute_process(COMMAND dpkg -b ./ ${argLowerTargetName}-${argVersion}-amd64.deb WORKING_DIRECTORY ${argWorkingDir})
else()
  execute_process(COMMAND ${CMAKE_COMMAND} -E env VERSION=v${argVersion} ${argTool} usr/share/applications/${argPacketName}.desktop -always-overwrite -bundle-non-qt-libs -appimage WORKING_DIRECTORY ${argWorkingDir})
endif()
# cmake-format: on
