cmake_minimum_required(VERSION 3.16)
project(search_engine_skillbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_SOURCES
        test_main.cpp
        test_inverted_index.cpp
        test_search_server.cpp
)

add_executable(search_engine_tests ${TEST_SOURCES})

target_link_libraries(search_engine_tests PRIVATE
        search_engine_lib
        gtest_main
)

target_include_directories(search_engine_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(search_engine_tests)

