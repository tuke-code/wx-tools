cmake_minimum_required(VERSION 3.20)

project(
  eTools
  VERSION 1.0.0
  LANGUAGES C CXX)

set(CMAKE_AUTORCC ON)

set(wxBUILD_SHARED
    OFF
    CACHE BOOL "Build wxWidgets as shared libraries" FORCE)
set(wxBUILD_USE_STATIC_RUNTIME
    ON
    CACHE BOOL "Build static runtime" FORCE)

include(CMake/asio.cmake)
include(CMake/glog.cmake)
include(CMake/sigslot.cmake)
include(CMake/wxWidgets.cmake)
include(CMake/websocketpp.cmake)

include_directories(Source)

file(GLOB_RECURSE E_TOOLS_SOURCE Source/*.*)
list(APPEND E_TOOLS_SOURCE eTools.rc)
add_executable(eTools ${E_TOOLS_SOURCE})
target_link_libraries(eTools glog::glog wx::core wx::aui)
set_target_properties(
  eTools
  PROPERTIES ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
             TRUE WIN32_EXECUTABLE
             TRUE)
