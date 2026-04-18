
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#ifdef CMACHINETEST

#include "cargs.h"

extern int col;
extern int row;
extern bool asBar;
extern int chFill;


int main( int argc, char *argv[] ){
	

	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;
		
	if( asBar == false )	
		printf( "cmachine ... test argc(%i)\n", argc );
	

	return 0;
}

#endif
