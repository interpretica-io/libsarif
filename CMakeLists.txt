cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(libsarif)

include(thirdparty/nlohmann-json.cmake)

add_library(libsarif INTERFACE)
target_include_directories(libsarif INTERFACE include)
target_link_libraries(libsarif INTERFACE nlohmann_json)

export (
	TARGETS
		libsarif
	FILE
		libsarif-targets.cmake
)
