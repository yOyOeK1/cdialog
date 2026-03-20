gcc cmdh.c fileh.c timeh.c ccanvas.c \
	-lpthread -lm \
	-o ccanvash.bin && ./ccanvash.bin $* 
