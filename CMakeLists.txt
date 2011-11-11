cmake_minimum_required (VERSION 2.6)
project (oclog) 

set(CMAKE_CXX_FLAGS "-O2 -Wall -pedantic -Wno-long-long -Wno-variadic-macros -Wno-return-type")


#add_subdirectory (scribe)
add_subdirectory (src) 

ENABLE_TESTING()
add_subdirectory (test)
