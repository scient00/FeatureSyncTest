#!/bin/sh

svrIp = "127.0.0.1";
svrPort = 7777;
dbPath = "./rsface.db";

mkdir -f run
make -f Makefile_client clean
make -f Makefile_client
export LD_LIBRARY_PATH=$PWD/client/Lib/:$LD_LIBRARY_PATH
./run/clientStart $svrIp $svrPort $dbPath
