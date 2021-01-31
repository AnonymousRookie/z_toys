cmake_minimum_required(VERSION 3.10.1)

project(z_design_pattern)

set(HEADERS
    z_observer.h
)

set(SOURCES
    test.cpp
    z_observer.cpp
)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(z_design_pattern ${HEADERS} ${SOURCES})