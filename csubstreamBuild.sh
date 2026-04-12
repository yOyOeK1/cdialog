#!/bin/sh

gcc ./csubstream.c -o csubstream.test.bin && \
	echo "build OK" && \
	ls -alh ./csubstream.test.bin && ./csubstream.test.bin $* 
