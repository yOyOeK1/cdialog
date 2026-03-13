

inc="-I/home/yoyo/Apps/mosquitto-2.0.13/include "
libsDir="-L/home/yoyo/Apps/mosquitto-2.0.13/bu/lib "


gcc \
	mqtth.c dogh.c timeh.c cmdh.c fileh.c mainBuild2.c \
	$inc $libsDir \
	-Ofast -march=native \
	-fno-builtin \
	-Wimplicit-function-declaration \
	-Wno-error=int-conversion \
	-lcurses -lncurses -lncursesw -lm \
	-lpthread \
	-lmosquitto -lrt \
	-o ./build2Res.bin
