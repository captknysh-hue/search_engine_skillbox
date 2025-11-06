cmake_minimum_required(VERSION 3.24)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/nlohmann_json/include)

include(FetchContent)
cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(gtest_disable_pthreads on)

FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()

set(SOURCE_FILES
        main.cpp
        ConverterJSON.cpp
        InvertedIndex.cpp
        SearchServer.cpp
)

add_executable(search_engine ${SOURCE_FILES})

add_executable(search_engine_tests
        tests/test_main.cpp
        tests/test_inverted_index.cpp
        tests/test_search_server.cpp
)

add_library(search_engine_lib InvertedIndex.cpp SearchServer.cpp ConverterJSON.cpp)

target_include_directories(search_engine_lib PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(search_engine_tests search_engine_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(search_engine_tests DISCOVERY_TIMEOUT 30)

message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "GTest source dir: ${gtest_SOURCE_DIR}")