
inc="-I/home/yoyo/src/mosquitto-2.0.13/include "
libsDir="-L/home/yoyo/src/mosquitto-2.0.13/bu/lib "



gcc cmdh.c fileh.c timeh.c ccanvas.c \
	-lmosquitto -lrt -lm -lpthread -lcurses -lncurses -lncursesw \
	-o ccanvash.bin $inc $libsDir && ./ccanvash.bin $* 
