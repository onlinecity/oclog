set(unitheaders
	LogTest.h
)

SET(Boost_USE_STATIC_LIBS OFF) # Or we get errors with -fPIC
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost 1.41 COMPONENTS date_time system filesystem thread REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# Thrift
FIND_PATH(THRIFT_INCLUDE_DIR Thrift.h PATH_SUFFIXES thrift)
INCLUDE_DIRECTORIES(${THRIFT_INCLUDE_DIR})

# Scribe interfaces
include_directories(${CMAKE_SOURCE_DIR}/scribe)

# Main lib
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(unittest ${unitheaders} testrun.cpp)
target_link_libraries(unittest cppunit oclog ${Boost_LIBRARIES})
add_test(cpp-unit-test unittest)
