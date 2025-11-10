cmake_minimum_required(VERSION 3.16)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
        ConverterJSON.cpp
        InvertedIndex.cpp
        SearchServer.cpp
        main.cpp
)
add_executable(search_engine ${SOURCES})
target_include_directories(search_engine PRIVATE ${PROJECT_SOURCE_DIR}/include)

