
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#ifdef CMACHINETEST

#include "config.h"

#include "cargs.h"



extern int col;
extern int row;
extern bool asBar;
extern int chFill;


int main( int argc, char *argv[] ){
	

	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;
		
	if( asBar == false )	
		printf( "cmachine ... test argc(%i)\n", argc );
	

	for( int msrc=0; true; msrc++ ){
		if( machNs[ msrc ].id == -1 ) break;

		printf("*[%i] %s\n", msrc, machNs[ msrc ].name );


	}


	printf( "cmachine ... DONE\n" );

	return 0;
}

#endif
