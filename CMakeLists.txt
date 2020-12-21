cmake_minimum_required(VERSION 3.13)
project(Parser)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(SOURCE_DEBUG_FILES tests.cpp)

set(SOURCE_FILES Situation.h EarleyParser.h EarleyParser.cpp)

add_executable(earley_parser ${SOURCE_FILES} ${SOURCE_DEBUG_FILES})
target_link_libraries(earley_parser gtest gtest_main)