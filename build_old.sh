#!/bin/bash

LIBTORRENT=`pkg-config --libs --cflags libtorrent-rasterbar`
LIBYAML=`pkg-config --libs --cflags yaml-cpp`
LIBBOOST="-lboost_filesystem"

function run {
	echo $@
	$@
}

run g++ -O3 src/main.cpp -DTORRENT_USE_READV=0 -o torrent-client $LIBTORRENT $LIBBOOST $LIBYAML
