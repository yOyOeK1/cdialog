#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>


void ctermSize( int *col, int *row ){
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );
	*col = w.ws_col;
	*row = w.ws_row;
}


#ifdef CTERMTEST

int main(){

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	printf("This terminal window is %d rows by %d columns\n", w.ws_row, w.ws_col );

	int mc;
	int mr;
	ctermSize( &mc, &mr );
	printf("2 This terminal window is %d rows by %d columns\n", mc, mr  );

	return(0);
}

#endif
