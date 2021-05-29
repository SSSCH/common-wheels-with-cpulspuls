cmake_minimum_required(VERSION 2.8)

project(COMMON_WHEELS_WITH_CPULSPULS)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/module)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++14 -pthread")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(DesignPattern designPattern)
add_subdirectory(utils util)
add_subdirectory(test testwheel)


#[[
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
message("generate test.bin")]]
