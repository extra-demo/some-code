project(003_ujson4c)

cmake_minimum_required(VERSION 3.10)

aux_source_directory(. DIR_TOO_SRCS)

add_subdirectory(3rdparty/json)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

add_executable(run_003 ${DIR_TOO_SRCS})
target_link_libraries(run_003 3RD_JSON)