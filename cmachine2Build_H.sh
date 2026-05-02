#!/bin/sh

echo "Build .h for cmachine files ... "

./build_h_from_c.sh ./cmTools.c > ./cmTools.h
./build_h_from_c.sh ./cmInits.c > ./cmInits.h
./build_h_from_c.sh ./cmachine2.c > ./cmachine2.h 

echo "- - - DONE"
