# JSON for modern C++
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(
  nlohmann_json
  GIT_REPOSITORY "https://github.com/maximmenshikov/json.git"
  CONFIGURE_COMMAND ""
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  SOURCE_DIR "${CMAKE_BINARY_DIR}/nlohmann_json"
)
ExternalProject_Get_Property(nlohmann_json source_dir)
set(NlohmannJsonInclude_dir ${source_dir}/include)
