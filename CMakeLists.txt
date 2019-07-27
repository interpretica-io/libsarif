cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

include(ExternalProject)
set(SARIF_SCHEMA "sarif-2.1.0-rtm.4.json")
include(${CMAKE_SOURCE_DIR}/deps/nlohmann_json.cmake)

project(libsarif)

file (GLOB LIB_SOURCE_FILES "src/*.c")
set(SOURCES ${LIB_SOURCE_FILES})

add_library(libsarif INTERFACE)
target_include_directories(libsarif INTERFACE include)

set(LibSarifIncludeDir ${NlohmannJsonIncludeDir} ${include})
