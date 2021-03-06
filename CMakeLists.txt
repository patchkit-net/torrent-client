cmake_minimum_required (VERSION 3.1.0)
project(torrent-client)

option(USE_JSON "use JSON as serialization output")
option(USE_YAML "use YAML as serialization output")

# static runtime linking

if(WIN32)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT") 
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd") 
endif()

# json and yaml

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

if(NOT LIBBOOST_CHRONO_RELEASE)
  message(FATAL_ERROR "LIBBOOST_CHRONO_RELEASE is not set!")
endif()

if(NOT LIBBOOST_CHRONO_DEBUG)
  message(FATAL_ERROR "LIBBOOST_CHRONO_DEBUG is not set!")
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

find_package(Threads REQUIRED)
add_executable(torrent-client src/main.cpp)

target_link_libraries(torrent-client optimized ${LIBTORRENT_RELEASE})
target_link_libraries(torrent-client optimized ${LIBBOOST_SYSTEM_RELEASE})
target_link_libraries(torrent-client optimized ${LIBBOOST_RANDOM_RELEASE})
target_link_libraries(torrent-client optimized ${LIBBOOST_CHRONO_RELEASE})
if(CMAKE_USE_PTHREADS_INIT)
    target_link_libraries(torrent-client optimized ${CMAKE_THREAD_LIBS_INIT})
endif()
if(WIN32)
    target_link_libraries(torrent-client optimized Iphlpapi.lib)
endif()

target_link_libraries(torrent-client debug ${LIBTORRENT_DEBUG})
target_link_libraries(torrent-client debug ${LIBBOOST_SYSTEM_DEBUG})
target_link_libraries(torrent-client debug ${LIBBOOST_RANDOM_DEBUG})
target_link_libraries(torrent-client debug ${LIBBOOST_CHRONO_DEBUG})
if(CMAKE_USE_PTHREADS_INIT)
    target_link_libraries(torrent-client debug ${CMAKE_THREAD_LIBS_INIT})
endif()
if(WIN32)
    target_link_libraries(torrent-client debug Iphlpapi.lib)
endif()

if(USE_YAML)
  target_link_libraries(torrent-client optimized ${LIB_YAML_CPP_RELEASE})

  target_link_libraries(torrent-client debug ${LIB_YAML_CPP_DEBUG})
endif()

add_definitions(-DBOOST_ALL_NO_LIB)