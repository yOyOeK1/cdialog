#!/bin/sh

gcc ./ctermh.c -o ctermh.test.bin \
	-DCTERMTEST && \
	ls -alh ./ctermh.test.bin && \
	echo "DONE" && \
	./ctermh.test.bin $*
