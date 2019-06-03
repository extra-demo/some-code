project(curl_002)

cmake_minimum_required(VERSION 3.10)

aux_source_directory(. DIR_TOO_SRCS)

find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

add_executable(run_002 ${DIR_TOO_SRCS})
target_link_libraries(run_002 ${CURL_LIBRARIES})