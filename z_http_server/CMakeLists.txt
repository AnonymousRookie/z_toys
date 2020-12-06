project(z_http_server)

set(build_target z_http_server)

include_directories(.)
aux_source_directory(. SRC_LIST)

if (CMAKE_COMPILER_IS_GNUCXX)
   set(CMKAE_CXX_FLAGS "-std=c++11 -phread")
endif()

add_executable(${build_target} ${SRC_LIST})
