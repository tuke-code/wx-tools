cmake_minimum_required(VERSION 3.20)

project(
  wxTools
  VERSION 1.0.0
  LANGUAGES C CXX)

# cmake-format: off
set(CMAKE_AUTORCC ON)
set(wxBUILD_SHARED OFF CACHE BOOL "Build wxWidgets as shared libraries" FORCE)
if(WIN32)
  set(wxBUILD_USE_STATIC_RUNTIME ON CACHE BOOL "Build static runtime" FORCE)
endif()
if(WIN32 AND MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
# cmake-format: on

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_compile_definitions(WXT_RELEASE)
endif()

include(cmake/git.cmake)
include(cmake/fmt.cmake)
include(cmake/asio.cmake)
include(cmake/glog.cmake)
include(cmake/json.cmake)
include(cmake/sigslot.cmake)
include(cmake/mongoose.cmake)
include(cmake/wxWidgets.cmake)
include(cmake/CSerialPort.cmake)

include_directories(src)

# Windows XP
option(_WIN32_WINNT "Windows Version" 0x0501)
# Windows 7 option(_WIN32_WINNT "Windows Version" 0x0601)

wxt_git_get_latest_tag(${CMAKE_SOURCE_DIR} WXT)
wxt_git_get_latest_commit(${CMAKE_SOURCE_DIR} WXT)
wxt_git_get_latest_commit_time(${CMAKE_SOURCE_DIR} WXT)

add_compile_definitions(MG_DATA_SIZE=1024)
file(GLOB_RECURSE WX_TOOLS_SOURCE src/*.*)
list(APPEND WX_TOOLS_SOURCE wxTools.rc)
add_executable(wxTools ${WX_TOOLS_SOURCE})

set(PROJECT_LIBS libcserialport mongoose wx::core wx::aui glog::glog fmt::fmt)
target_link_libraries(wxTools PRIVATE ${PROJECT_LIBS})
set_target_properties(
  wxTools
  PROPERTIES ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
             TRUE WIN32_EXECUTABLE
             TRUE)

# --------------------------------------------------------------------------------------------------
# Copy res/i18n to build directory
add_custom_command(
  TARGET wxTools
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/res/i18n"
          "$<TARGET_FILE_DIR:wxTools>/i18n")

# --------------------------------------------------------------------------------------------------
# Deploy local files
file(GLOB_RECURSE WX_TOOLS_LOCAL_FILES res/*.po)
add_custom_target(
  wxTools-deploy-locale
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/res/i18n"
          "$<TARGET_FILE_DIR:wxTools>/i18n"
  SOURCES ${WX_TOOLS_LOCAL_FILES})
