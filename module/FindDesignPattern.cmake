find_path(DESIGNPATTERN_INCLUDES
        singleton.h
        ${PROJECT_SOURCE_DIR}/DesignPattern/singleton.h)

find_library(DESIGNPATTERN_LIBRARIES NAMES designPattern PATH ${PROJECT_BINARY_DIR}/lib)

IF(DESIGNPATTERN_INCLUDES AND DESIGNPATTERN_LIBRARIES)
    SET(DESIGNPATTERN_FOUND TRUE)
    MESSAGE(STATUS "DESIGNPATTERN_FOUND true")
ENDIF(DESIGNPATTERN_INCLUDES AND DESIGNPATTERN_LIBRARIES)

IF(DESIGNPATTERN_FOUND)
    IF(NOT DESIGNPATTERN_FIND_REQUIRED)
        MESSAGE(STATUS "founddesignpattern:" ${DESIGNPATTERN_INCLUDES})
        MESSAGE(STATUS "founddesignpatterntlib:" ${DESIGNPATTERN_LIBRARIES})
    ENDIF(NOT DESIGNPATTERN_FIND_REQUIRED)
ELSE(TEST_FOUND)
    IF(DESIGNPATTERN_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "could not find hello library")
    ENDIF(DESIGNPATTERN_FIND_REQUIRED)
ENDIF(DESIGNPATTERN_FOUND)