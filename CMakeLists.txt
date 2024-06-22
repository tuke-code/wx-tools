cmake_minimum_required(VERSION 3.20)

project(
  eTools
  VERSION 1.0.0
  LANGUAGES C CXX)

set(CMAKE_AUTORCC ON)

set(wxBUILD_SHARED
    OFF
    CACHE BOOL "Build wxWidgets as shared libraries" FORCE)
if(WIN32)
  set(wxBUILD_USE_STATIC_RUNTIME
      ON
      CACHE BOOL "Build static runtime" FORCE)
endif()

if(WIN32)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

include(CMake/json.cmake)
include(CMake/asio.cmake)
include(CMake/glog.cmake)
include(CMake/libcrc.cmake)
include(CMake/sigslot.cmake)
include(CMake/wxWidgets.cmake)
include(CMake/websocketpp.cmake)
include(CMake/CSerialPort.cmake)

include_directories(Source)

# Windows XP, Windows 7
option(_WIN32_WINNT "Windows Version" 0x0501)
# option(_WIN32_WINNT "Windows Version" 0x0601)

file(GLOB_RECURSE E_TOOLS_SOURCE Source/*.*)
list(APPEND E_TOOLS_SOURCE eTools.rc)
add_executable(eTools ${E_TOOLS_SOURCE})

set(PROJECT_LIBS libcserialport)
list(APPEND PROJECT_LIBS libcrc)
list(APPEND PROJECT_LIBS glog::glog)
list(APPEND PROJECT_LIBS nlohmann_json)
list(APPEND PROJECT_LIBS wx::core wx::aui)
target_link_libraries(eTools PRIVATE ${PROJECT_LIBS})
set_target_properties(
  eTools
  PROPERTIES ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
             TRUE WIN32_EXECUTABLE
             TRUE)
