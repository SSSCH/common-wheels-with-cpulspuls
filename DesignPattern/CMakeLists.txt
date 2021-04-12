cmake_minimum_required(VERSION 2.8)
#aux_source_directory(./ lib_list)
message(STATUS "goto designPattern")
set(lib_list singleton.h
             builder.cpp
             builder.h
             prototype.h)



add_library(designPattern STATIC ${lib_list})

set_target_properties(designPattern PROPERTIES LINKER_LANGUAGE CXX)