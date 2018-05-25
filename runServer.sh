#!/bin/sh

mkdir -f run
make -f Makefile_server clean
make -f Makefile_server
export LD_LIBRARY_PATH=$PWD/server/Lib/:$LD_LIBRARY_PATH
./run/serverStart
