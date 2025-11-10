cmake_minimum_required(VERSION 3.16)
project(search_engine_skillbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
        ConverterJSON.cpp
        InvertedIndex.cpp
        SearchServer.cpp
)

add_library(search_engine_lib ${SOURCES})
add_executable(search_engine_skillbox main.cpp)
target_link_libraries(search_engine_skillbox PRIVATE search_engine_lib)
target_include_directories(search_engine_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(search_engine_skillbox PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

