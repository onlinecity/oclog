SET(headers
	Log.h
	Sink.h
	FileSink.h
	CerrSink.h
	ScribeSink.h
	SinkQueue.h
	LogLevel.h
)

# FindBoost
SET(Boost_USE_STATIC_LIBS OFF) # Or we get errors with -fPIC
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost 1.41 COMPONENTS date_time system filesystem REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# LibEvent
FIND_PATH(EVENT_INCLUDE_DIR event.h)
INCLUDE_DIRECTORIES(${EVENT_INCLUDE_DIR})

# Thrift
FIND_PATH(THRIFT_INCLUDE_DIR Thrift.h PATH_SUFFIXES thrift)
INCLUDE_DIRECTORIES(${THRIFT_INCLUDE_DIR}) 

# Scribe interfaces
include_directories(${CMAKE_SOURCE_DIR}/scribe)

INCLUDE_DIRECTORIES(${SCRIBE_INCLUDE_DIR})

ADD_LIBRARY(oclog SHARED ${headers} ${sources})
SET_TARGET_PROPERTIES(oclog PROPERTIES VERSION 1.0.0 SOVERSION 1 PUBLIC_HEADER "${headers}")
TARGET_LINK_LIBRARIES(oclog
    ${Boost_LIBRARIES}
    scribe_if 
    event 
	thrift 
	thriftnb 
)
	
SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
SET(CMAKE_INSTALL_HEADERDIR include CACHE PATH "Output directory for headers")
INSTALL(TARGETS oclog LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_HEADERDIR}/oclog)