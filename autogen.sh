#! /bin/sh

autoreconf -i
[ ! -d Build ] && mkdir Build
./configure --prefix=`pwd`/Build
