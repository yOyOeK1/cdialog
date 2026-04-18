
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#ifndef CPPTEST

extern int col;
extern int row;
extern bool asBar;
extern int chFill;

#else

#include "cargs.h"
extern int col;
extern int row;
extern bool asBar;
extern int chFill;

#endif


#ifdef CPPTEST
int main( int argc, char *argv[] ){

	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;


	printf("c cmachine2 CPPTEST ... START size [ %ix%i ]\n", col, row);

	printf("c cmachine2 CPPTEST ... DONE\n");
	return 0;
}
#endif
