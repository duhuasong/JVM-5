#!/bin/sh

# Build zlib.
./configure --prefix=../../include
make -j8
make install

# Build minizip.
cd contrib/minizip
make -j8
cp libunz.a ../../../../include/lib
