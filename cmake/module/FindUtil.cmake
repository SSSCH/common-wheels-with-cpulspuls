MESSAGE(STATUS "findutil.cmake in")

find_path(UTIL_INCLUDES
         Timer.h
         ${PROJECT_SOURCE_DIR}/utils)

find_library(UTIL_LIBRARIES
             NAMES myUtils
             HINTS ${PROJECT_BINARY_DIR}/lib)

if (NOT UTIL_INCLUDES)
    message("UTIL_INCLUDES not find")
endif (NOT UTIL_INCLUDES)
if (NOT UTIL_LIBRARIES)
    message("UTIL_LIBRARIES not find")
endif (NOT UTIL_LIBRARIES)

IF(UTIL_INCLUDES AND UTIL_LIBRARIES)
    SET(UTIL_FOUND TRUE)
    MESSAGE(STATUS "UTIL_FOUND true")
ENDIF(UTIL_INCLUDES AND UTIL_LIBRARIES)

IF(UTIL_FOUND)
    IF(NOT UTIL_FIND_REQUIRED)
        MESSAGE(STATUS "foundUTIL:" ${UTIL_INCLUDES})
        MESSAGE(STATUS "foundUTILtlib:" ${UTIL_LIBRARIES})
    ENDIF(NOT UTIL_FIND_REQUIRED)
ELSE(UTIL_FOUND)
    IF(UTIL_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "could not find util library")
    ENDIF(UTIL_FIND_REQUIRED)
ENDIF(UTIL_FOUND)