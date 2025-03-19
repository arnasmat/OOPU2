cmake_minimum_required(VERSION 3.29)
project(OOPU2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(OOPU2 ${SOURCES})