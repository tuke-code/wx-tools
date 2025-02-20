# * argTarget: cmake target
# * argPacketName: packet name of deb packet
# * argFriendlyName: desktop entry file name
# * argVersion: the application version
# * argAppImageTool: appimage tool
# * argWorkingDir: working dir

set(icon_tmp ${argWorkingDir}/share/icons/icon.png)
#execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${icon_tmp} "../" WORKING_DIRECTORY ${argWorkingDir})

set(icon ${argWorkingDir}/share/icons/${argPacketName}.png)
execute_process(COMMAND ${CMAKE_COMMAND} -E rename ${icon_tmp} ${icon})

# The desktop file must end with LF, you can use vscode to edit the file and save it with LF
set(desktop_file_name_tmp ${argWorkingDir}/share/applications/desktop.desktop)
set(desktop_file_name ${argWorkingDir}/share/applications/${argFriendlyName}.desktop)
execute_process(COMMAND ${CMAKE_COMMAND} -E rename ${desktop_file_name_tmp} ${desktop_file_name})

set(old_text argFriendlyName)
set(new_text ${argFriendlyName})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})

set(old_text argPacketName)
set(new_text ${argPacketName})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})

set(old_text icon.png)
set(new_text ${argPacketName})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})

set(old_text argTarget)
set(new_text ${argTarget})
execute_process(COMMAND sed -i s/${old_text}/${new_text}/g ${desktop_file_name})

# Deploy and create AppImage
execute_process(COMMAND ${CMAKE_COMMAND} -E env VERSION=v${argVersion} ${argTool} share/applications/${argFriendlyName}.desktop  -always-overwrite -bundle-non-qt-libs -appimage WORKING_DIRECTORY ${argWorkingDir})