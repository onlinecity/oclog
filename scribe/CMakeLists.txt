SET(headers
    FacebookBase.h
    FacebookService.h
    fb303_constants.h
    fb303_types.h
    scribe_constants.h
    scribe.h
    scribe_types.h
)

SET(sources
    FacebookBase.cpp
    FacebookService.cpp
    fb303_constants.cpp
    fb303_types.cpp
    scribe_constants.cpp
    scribe.cpp
    scribe_types.cpp
)


# FindBoost
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME ON)

FIND_PACKAGE(Boost 1.41 COMPONENTS system filesystem REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# LibEvent
FIND_PATH(EVENT_INCLUDE_DIR event.h)
INCLUDE_DIRECTORIES(${EVENT_INCLUDE_DIR})

# Thrift
FIND_PATH(THRIFT_INCLUDE_DIR Thrift.h PATH_SUFFIXES thrift)
INCLUDE_DIRECTORIES(${THRIFT_INCLUDE_DIR}) 

ADD_LIBRARY(scribe_if STATIC ${headers} ${sources})
SET_TARGET_PROPERTIES(scribe_if PROPERTIES VERSION 1.0.0 SOVERSION 1 PUBLIC_HEADER "${headers}")
TARGET_LINK_LIBRARIES(scribe_if
    ${Boost_LIBRARIES} 
    event 
	thrift 
	thriftnb 
)
