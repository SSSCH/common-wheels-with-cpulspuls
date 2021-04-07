cmake_minimum_required(VERSION 2.8)
message(STATUS "goto util")
#aux_source_directory only add *.cpp file, not add .h file
#[[aux_source_directory(. lib_list)
foreach(file ${lib_list})
    message(${file})
endforeach()]]

set(lib_list
        syncQueue.h
        threadPoll.cpp
        threadPoll.h
        Timer.cpp
        Timer.h)

add_library(util STATIC ${lib_list})