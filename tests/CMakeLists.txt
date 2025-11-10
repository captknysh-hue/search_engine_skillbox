cmake_minimum_required(VERSION 3.16)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_SOURCES
        tests/test_main.cpp
        tests/test_inverted_index.cpp
        tests/test_search_server.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
        src/main.cpp
)

add_executable(search_engine_tests ${TEST_SOURCES})

target_link_libraries(search_engine_tests PRIVATE gtest_main)

target_include_directories(search_engine_tests PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/nlohmann_json/include
        ${PROJECT_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(search_engine_tests)

