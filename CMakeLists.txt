cmake_minimum_required(VERSION 3.16)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/nlohmann_json/include)

add_executable(search_engine
        main.cpp
        ConverterJSON.cpp
        InvertedIndex.cpp
        SearchServer.cpp
)

add_executable(search_engine_tests
        tests/test_main.cpp
        tests/test_inverted_index.cpp
        tests/test_search_server.cpp
        InvertedIndex.cpp
        SearchServer.cpp
        ConverterJSON.cpp
)

target_link_libraries(search_engine_tests PRIVATE gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(search_engine_tests DISCOVERY_TIMEOUT 30)