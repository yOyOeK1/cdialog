
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

extern int col;
extern int row;
extern bool asBar;
extern int chFill;

#ifndef CPPTEST


#else

#include "cargs.h"
#include "config.h"

#endif

#include "cmdh.h"

char cmachBuff[512];

void cmachine_start_byNode( struct machNode mn ){
	printf("\t* start by id ... %i\n", mn.id );	

	if( mn.typeOf == 0 ){ // cmd
		mn.isRunning = true;
		strcpy( mn.result, cmd_to_chars( mn.cmd ) );
		printf( "\t* ... result [ %s ]\n", mn.result );

	}else{
		printf("\tEE type not implemented [%i]\n", mn.typeOf );
	}
}


#ifdef CPPTEST
int main( int argc, char *argv[] ){

	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;


	printf("c cmachine2 CPPTEST ... START size [ %ix%i ]@%s\n", col, row, machineName );

	for( int p=0; true; p++ ){
		if( machNs[ p ].id == -1 ) break;

		printf("\n\n*[%i] id[%i] ... onStart[%i] every[%ims] \n\t - %s\n", p, 
			machNs[ p ].id, machNs[ p ].onStart, machNs[ p ].everyMs, machNs[ p ].name 
			);
		if( machNs[ p ].onStart )
			cmachine_start_byNode( machNs[ p ] );
	
	}


	printf("c cmachine2 CPPTEST ... DONE\n");
	return 0;
}
#endif
