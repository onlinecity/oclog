SET(headers
	Log.h
	Sink.h
	FileSink.h
	CerrSink.h
	ScribeSink.h
	SinkQueue.h
	LogLevel.h
	macros.h
    hexdump.h
)

SET(sources
    Sink.cpp
    ScribeSink.cpp
    FileSink.cpp
    hexdump.cpp
)

SET(scribeheaders
    ${CMAKE_SOURCE_DIR}/scribe/FacebookBase.h
    ${CMAKE_SOURCE_DIR}/scribe/FacebookService.h
    ${CMAKE_SOURCE_DIR}/scribe/fb303_constants.h
    ${CMAKE_SOURCE_DIR}/scribe/fb303_types.h
    ${CMAKE_SOURCE_DIR}/scribe/scribe_constants.h
    ${CMAKE_SOURCE_DIR}/scribe/scribe.h
    ${CMAKE_SOURCE_DIR}/scribe/scribe_types.h
)

SET(scribesources
    ${CMAKE_SOURCE_DIR}/scribe/FacebookBase.cpp
    ${CMAKE_SOURCE_DIR}/scribe/FacebookService.cpp
    ${CMAKE_SOURCE_DIR}/scribe/fb303_constants.cpp
    ${CMAKE_SOURCE_DIR}/scribe/fb303_types.cpp
    ${CMAKE_SOURCE_DIR}/scribe/scribe_constants.cpp
    ${CMAKE_SOURCE_DIR}/scribe/scribe.cpp
    ${CMAKE_SOURCE_DIR}/scribe/scribe_types.cpp
)

# FindBoost
SET(Boost_USE_STATIC_LIBS OFF) # Or we get errors with -fPIC
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost 1.41 COMPONENTS date_time system filesystem thread REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# LibEvent
FIND_PATH(EVENT_INCLUDE_DIR event.h)
INCLUDE_DIRECTORIES(${EVENT_INCLUDE_DIR})
FIND_LIBRARY(EVENT_LIB event)

# Thrift
FIND_PATH(THRIFT_INCLUDE_DIR Thrift.h PATH_SUFFIXES thrift)
INCLUDE_DIRECTORIES(${THRIFT_INCLUDE_DIR}) 
FIND_LIBRARY(THRIFT_LIB thrift)
FIND_LIBRARY(THRIFT_NB_LIB thriftnb)

# Scribe interfaces
include_directories(${CMAKE_SOURCE_DIR}/scribe)

INCLUDE_DIRECTORIES(${SCRIBE_INCLUDE_DIR})

ADD_LIBRARY(oclog SHARED ${headers} ${scribeheaders} ${sources} ${scribesources})
SET_TARGET_PROPERTIES(oclog PROPERTIES VERSION 1.0.0 SOVERSION 1 PUBLIC_HEADER "${headers}" PRIVATE_HEADER "${scribeheaders}" )
TARGET_LINK_LIBRARIES(oclog
    ${Boost_LIBRARIES}
    ${EVENT_LIB}
    ${THRIFT_LIB}
    ${THRIFT_NB_LIB}
)
	
SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
SET(CMAKE_INSTALL_HEADERDIR include CACHE PATH "Output directory for headers")
INSTALL(TARGETS oclog 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_HEADERDIR}/oclog
    PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_HEADERDIR}/oclog
)