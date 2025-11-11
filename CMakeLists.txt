cmake_minimum_required(VERSION 3.16)
project(search_engine_skillbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
cmake_policy(SET CMP0135 NEW)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/nlohmann_json/include)

add_subdirectory(src)
add_subdirectory(tests)