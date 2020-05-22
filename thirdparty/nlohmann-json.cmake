# nlohmann-json build rules
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY 	"https://github.com/maximmenshikov/json"
  GIT_TAG 			"develop"
  CMAKE_ARGS 		-DJSON_BuildTests=OFF -DJSON_MultipleHeaders=ON -GNinja
)

FetchContent_MakeAvailable(nlohmann_json)
