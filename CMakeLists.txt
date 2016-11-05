cmake_minimum_required (VERSION 2.8.1)
project(torrent-client)

string (COMPARE EQUAL "${CMAKE_SIZEOF_VOID_P}" "8" IS64BITS)

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

if(NOT YAML_CPP_INCLUDEDIR)
  message(FATAL_ERROR "YAML_CPP_INCLUDEDIR is not set!")
endif()

if(NOT LIB_YAML_CPP_RELEASE)
  message(FATAL_ERROR "LIB_YAML_CPP_RELEASE is not set!")
endif()

if(NOT LIB_YAML_CPP_DEBUG)
  message(FATAL_ERROR "LIB_YAML_CPP_DEBUG is not set!")
endif()

include_directories(include ${BOOST_INCLUDEDIR} ${LIBTORRENT_INCLUDEDIR} ${YAML_CPP_INCLUDEDIR})

add_executable(torrent-client src/main.cpp)

target_link_libraries(torrent-client optimized ${LIBTORRENT_RELEASE} ${LIB_YAML_CPP_RELEASE} ${LIBBOOST_SYSTEM_RELEASE})

target_link_libraries(torrent-client debug ${LIBTORRENT_DEBUG} ${LIB_YAML_CPP_DEBUG} ${LIBBOOST_SYSTEM_DEBUG})

add_definitions(-DBOOST_ALL_NO_LIB)
