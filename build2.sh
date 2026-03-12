

gcc dogh.c timeh.c cmdh.c fileh.c mainBuild2.c \
	-Ofast -march=native \
	-lcurses -lncurses -lncursesw -lm \
	-lpthread \
	-o ./build2Res.bin
