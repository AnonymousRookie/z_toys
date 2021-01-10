cmake_minimum_required(VERSION 3.10.1)

project(z_net)

include_directories(src)

set(HEADERS
    src/acceptor.h
    src/buffer.h
    src/callbacks.h
    src/channel.h
    src/connector.h
    src/defines.h
    src/event_loop.h
    src/event_loop_thread.h
    src/event_loop_thread_pool.h
    src/logger.h
    src/net_address.h
    src/poller.h
    src/poller_epoll.h
    src/socket.h
    src/sockets_ops.h
    src/tcp_client.h
    src/tcp_connection.h
    src/tcp_server.h
    src/time_stamp.h
    src/z_endian.h
)

set(SOURCES
    src/acceptor.cpp
    src/buffer.cpp
    src/channel.cpp
    src/connector.cpp
    src/event_loop.cpp
    src/event_loop_thread.cpp
    src/event_loop_thread_pool.cpp
    src/logger.cpp
    src/net_address.cpp
    src/poller.cpp
    src/poller_epoll.cpp
    src/socket.cpp
    src/sockets_ops.cpp
    src/tcp_client.cpp
    src/tcp_connection.cpp
    src/tcp_server.cpp
    src/time_stamp.cpp
)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(echo_client ${HEADERS} ${SOURCES} tests/echo_client.cpp)
add_executable(echo_server ${HEADERS} ${SOURCES} tests/echo_server.cpp)
