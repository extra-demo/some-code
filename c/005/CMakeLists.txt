project(curl_json_005)

cmake_minimum_required(VERSION 3.7)

aux_source_directory(. DIR_TOO_SRCS)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_subdirectory(3rdparty/json)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(run_005 ${DIR_TOO_SRCS})
#target_link_libraries(run_005 ${CURL_LIBRARIES} 3RD_JSON m)
target_link_libraries(run_005 ${CURL_LIBRARIES} 3RD_JSON)