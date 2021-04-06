cmake_minimum_required(VERSION 3.7)

AUX_SOURCE_DIRECTORY(. src_list)

find_package(designPattern REQUIRED)
if(DESIGNPATTERN_FOUND)
    message("find designPattern")
    include_directories(${DESIGNPATTERN_INCLUDES})
    link_directories(${DESIGNPATTERN_LIBRARIES})
endif(DESIGNPATTERN_FOUND)

#[[find_package(util REQUIRED)
if(UTIL_FOUND)
    include_directories(${UTIL_INCLUDES})
    link_directories(${UTIL_LIBRARIES})
endif(UTIL_POUND)]]

add_executable(testwheel ${src_list})
target_link_libraries(designPattern)
target_link_libraries(util)