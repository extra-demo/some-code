project(curl_004)

cmake_minimum_required(VERSION 3.10)

aux_source_directory(. DIR_TOO_SRCS)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_subdirectory(3rdparty/json)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

add_executable(run_004 ${DIR_TOO_SRCS})
target_link_libraries(run_004 ${CURL_LIBRARIES})
target_link_libraries(run_004 3RD_JSON)