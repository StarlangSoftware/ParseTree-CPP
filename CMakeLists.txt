cmake_minimum_required(VERSION 3.13)
project(ParseTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(ParseTree SearchDirectionType.h Symbol.cpp Symbol.h)

target_link_libraries(ParseTree Dictionary)
