cmake_minimum_required(VERSION 3.7)
#aux_source_directory(./ lib_list)
message(STATUS "goto designPattern")
set(lib_list singleton.h)



add_library(designPattern STATIC ${lib_list})

set_target_properties(designPattern PROPERTIES LINKER_LANGUAGE CXX)