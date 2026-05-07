#!/bin/sh

gcc -DCNN_TCP_SERVER_TEST cnn_config_data.c ctcpS.c -o ctcpS.bin &&
./ctcpS.bin
