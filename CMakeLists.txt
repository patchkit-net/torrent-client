cmake_minimum_required (VERSION 3.1.0)
project(torrent-client)

option(USE_JSON "use JSON as serialization output")
option(USE_YAML "use YAML as serialization output")

# static runtime linking

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

if(NOT (USE_JSON OR USE_YAML))
  message(FATAL_ERROR "Neither USE_JSON nor USE_YAML are set!")
endif()

if(USE_JSON AND USE_YAML)
  message(FATAL_ERROR "Both USE_JSON and USE_YAML are set!")
endif()

# boost

if(NOT BOOST_INCLUDEDIR)
  message(FATAL_ERROR "BOOST_INCLUDEDIR is not set!")
endif()

if(NOT LIBBOOST_SYSTEM_RELEASE)
  message(FATAL_ERROR "LIBBOOST_SYSTEM_RELEASE is not set!")
endif()

if(NOT LIBBOOST_SYSTEM_DEBUG)
  message(FATAL_ERROR "LIBBOOST_SYSTEM_DEBUG is not set!")
endif()

if(NOT LIBBOOST_RANDOM_RELEASE)
  message(FATAL_ERROR "LIBBOOST_RANDOM_RELEASE is not set!")
endif()

if(NOT LIBBOOST_RANDOM_DEBUG)
  message(FATAL_ERROR "LIBBOOST_RANDOM_DEBUG is not set!")
endif()

# libtorrent

if(NOT LIBTORRENT_INCLUDEDIR)
  message(FATAL_ERROR "LIBTORRENT_INCLUDEDIR is not set!")
endif()

if(NOT LIBTORRENT_RELEASE)
  message(FATAL_ERROR "LIBTORRENT_RELEASE is not set!")
endif()

if(NOT LIBTORRENT_DEBUG)
  message(FATAL_ERROR "LIBTORRENT_DEBUG is not set!")
endif()

# yaml-cpp

if(USE_YAML)
  add_definitions(-DUSE_YAML)
  if(NOT YAML_CPP_INCLUDEDIR)
    message(FATAL_ERROR "YAML_CPP_INCLUDEDIR is not set!")
  endif()

  if(NOT LIB_YAML_CPP_RELEASE)
    message(FATAL_ERROR "LIB_YAML_CPP_RELEASE is not set!")
  endif()

  if(NOT LIB_YAML_CPP_DEBUG)
    message(FATAL_ERROR "LIB_YAML_CPP_DEBUG is not set!")
  endif()
endif()

# json

if(USE_JSON)
  set (CMAKE_CXX_STANDARD 11)
  add_definitions(-DUSE_JSON)
  if(NOT JSON_INCLUDEDIR)
    message(FATAL_ERROR "JSON_INCLUDEDIR is not set!")
  endif()
endif()

include_directories(include ${BOOST_INCLUDEDIR} ${LIBTORRENT_INCLUDEDIR})

if(USE_YAML)
  include_directories(${YAML_CPP_INCLUDEDIR})
endif()

if(USE_JSON)
  include_directories(${JSON_INCLUDEDIR})
endif()

add_executable(torrent-client src/main.cpp)

message("heremessage!")
message(${LIBBOOST_RANDOM_RELEASE})

target_link_libraries(torrent-client optimized ${LIBBOOST_RANDOM_RELEASE} ${LIBBOOST_SYSTEM_RELEASE} ${LIBTORRENT_RELEASE} Iphlpapi.lib)

# target_link_libraries(torrent-client debug ${LIBBOOST_SYSTEM_DEBUG} ${LIBBOOST_RANDOM_DEBUG} ${LIBTORRENT_DEBUG})

if(USE_YAML)
  target_link_libraries(torrent-client optimized ${LIB_YAML_CPP_RELEASE})

  target_link_libraries(torrent-client debug ${LIB_YAML_CPP_DEBUG})
endif()

add_definitions(-DBOOST_ALL_NO_LIB)
