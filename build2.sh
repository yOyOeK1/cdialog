

gcc timeh.c cmdh.c fileh.c mainBuild2.c \
	-Ofast -march=native \
	-lcurses -lncurses -lncursesw -lm \
	-o ./build2Res.bin
