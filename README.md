
Installation
--------

If you want to use the scribe sink you'll need libevent and thrift.

```bash
cmake .
make
sudo make install
```

Usage
--------

Basic usage:

```cpp
#include <oclog/Log.h>
using namespace oc::log;
OC_LOG(CerrSink,"test1",LOG_DEBUG) << "Hello world " << 1;
OC_LOG(FileSink,"test2",LOG_ALERT) << "Hello world " << 2;
OC_LOG(ScribeSink,"test3",LOG_ERROR) << "Hello world " << 3;
```

Set the LogLevel:

```cpp
#include <oclog/Log.h>
using namespace oc::log;

OC_LOG(CerrSink,"test1",LOG_DEBUG) << "Hello world " << 1;

Log<CerrSink>::getLevel() = LOG_ERROR;
OC_LOG(CerrSink,"test1",LOG_DEBUG) << "no output";

#define OC_LOG_MAX_LEVEL oc::log::LOG_ALERT
OC_LOG(CerrSink,"test1",LOG_ERROR) << "no output either";

```

Log to a specific destination:

```cpp
#include <oclog/Log.h>
using namespace oc::log;
Log<FileSink>("test1", LOG_DEBUG,"other.log").get() << "Hello World"; // log to file other.log
Log<ScribeSink>("test2", LOG_DEBUG,"1.2.3.4","9000").get() << "Hello World"; // log to scribe on ip 1.2.3.4 port 900

```


CMake
--------

Include the following in your CMake files to gain access to deps (libevent, libthift, libthriftnb) and the lib (oclog).

```CMake
# LibEvent
FIND_PATH(EVENT_INCLUDE_DIR event.h)
INCLUDE_DIRECTORIES(${EVENT_INCLUDE_DIR})
FIND_LIBRARY(EVENT_LIB event)

# Thrift
FIND_PATH(THRIFT_INCLUDE_DIR Thrift.h PATH_SUFFIXES thrift)
INCLUDE_DIRECTORIES(${THRIFT_INCLUDE_DIR}) 
FIND_LIBRARY(THRIFT_LIB thrift)
FIND_LIBRARY(THRIFT_NB_LIB thriftnb)

# OC Log
FIND_PATH(OCLOG_INCLUDE_DIR Log.h PATH_SUFFIXES oclog)
INCLUDE_DIRECTORIES(${OCLOG_INCLUDE_DIR}) 
FIND_LIBRARY(OCLOG_LIB oclog)
```

You'll also need boost if you don't have it already.

Then add the libs to your ```TARGET_LINK_LIBRARIES``` ie:

```CMake
target_link_libraries(unittest 
    ${Boost_LIBRARIES}
    ${EVENT_LIB}
    ${THRIFT_LIB}
    ${THRIFT_NB_LIB}
    ${OCLOG_LIB}
)
```

