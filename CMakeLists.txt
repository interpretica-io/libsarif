cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(libsarif)

add_subdirectory(thirdparty/nlohmann_json)

file (GLOB LIB_SOURCE_FILES "src/*.c")
set(SOURCES ${LIB_SOURCE_FILES})

add_library(libsarif INTERFACE)
target_link_libraries(libsarif INTERFACE nlohmann_json)

export (
	TARGETS
		libsarif
	FILE
		libsarif-targets.cmake
)
