project(z_log)

set(build_target z_log)

include_directories(.)
aux_source_directory(. SRC_LIST)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

add_executable(${build_target} ${SRC_LIST})
