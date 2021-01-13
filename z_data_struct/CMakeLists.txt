cmake_minimum_required(VERSION 3.10.1)

project(z_data_struct)

set(HEADERS
    defines.h
    z_vector.h
    z_list.h
)

set(SOURCES
    test.cpp
)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(z_data_struct ${HEADERS} ${SOURCES})