cmake_minimum_required(VERSION 2.8)

project(WHEELS)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/utils SRC_LIST)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/DesignPattern SRC_LIST)

foreach(file ${SRC_LIST})
    MESSAGE(STATUS "src_list:" ${file})
endforeach()

add_library(whells STATIC ${SRC_LIST})

set(testfile main.cpp)
link_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/DesignPattern)

add_executable(SING ${testfile})
target_link_libraries(whells)
message("generate test.bin")