#!/bin/bash

function usage()
{
  echo
  echo Usage:
  echo \ \ \ \ ./build \<type\>
  echo Available types:
  echo \ \ \ \ * Release
  echo \ \ \ \ * Debug
}

if [ -z "$1" ]
  then
    usage
    exit 1
fi

if [[ "$1" != "Release" && "$1" != "Debug" ]]; then
  echo Error: unavailable \<type\> $1
  usage
  exit 1
fi

if [ ! -d bin/$PDK_PLATFORM_NAME/$1 ]; then
  mkdir -p bin/$PDK_PLATFORM_NAME/$1
fi

pushd bin/linux64

cmake -DCMAKE_BUILD_TYPE=$1 \
  -DBOOST_INCLUDEDIR=$PDK_BOOST_INCLUDEDIR \
  -DLIBBOOST_SYSTEM_DEBUG=$PDK_BOOST_LIBRARYDIR_DEBUG/libboost_system-mt-sd.a \
  -DLIBBOOST_SYSTEM_RELEASE=$PDK_BOOST_LIBRARYDIR_RELEASE/libboost_system-mt-s.a \
  -DLIBBOOST_RANDOM_DEBUG=$PDK_BOOST_LIBRARYDIR_DEBUG/libboost_random-mt-sd.a \
  -DLIBBOOST_RANDOM_RELEASE=$PDK_BOOST_LIBRARYDIR_RELEASE/libboost_random-mt-s.a \
  -DLIBBOOST_CHRONO_DEBUG=$PDK_BOOST_LIBRARYDIR_DEBUG/libboost_chrono-mt-sd.a \
  -DLIBBOOST_CHRONO_RELEASE=$PDK_BOOST_LIBRARYDIR_RELEASE/libboost_chrono-mt-s.a \
  -DLIBTORRENT_DEBUG=$PDK_LIBTORRENT_LIBRARYDIR_DEBUG/libtorrent-rasterbar.a \
  -DLIBTORRENT_RELEASE=$PDK_LIBTORRENT_LIBRARYDIR_RELEASE/libtorrent-rasterbar.a \
  -DLIBTORRENT_INCLUDEDIR=$PDK_LIBTORRENT_INCLUDEDIR_RELEASE \
  -DJSON_INCLUDEDIR=$PDK_JSON_INCLUDEDIR \
  -DCMAKE_INSTALL_PREFIX=/home/user/Documents/torrent-client/bin/linux64/output \
  -DUSE_JSON=on \
  -G "Unix Makefiles" \
  ../../

make

popd