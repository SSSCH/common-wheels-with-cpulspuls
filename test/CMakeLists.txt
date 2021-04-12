cmake_minimum_required(VERSION 3.7)

AUX_SOURCE_DIRECTORY(. src_list)

find_package(DesignPattern REQUIRED)
if(DESIGNPATTERN_FOUND)
    message(STATUS "find designPattern package")
    include_directories(${DESIGNPATTERN_INCLUDES})
    link_directories(${DESIGNPATTERN_LIBRARIES})
endif(DESIGNPATTERN_FOUND)

find_package(Util REQUIRED)
if(UTIL_FOUND)
    message(STATUS "find util package")
    include_directories(${UTIL_INCLUDES})
    link_directories(${UTIL_LIBRARIES})
endif(UTIL_FOUND)

add_executable(testwheel ${src_list})

target_link_libraries(testwheel designPattern)
target_link_libraries(testwheel myUtils)