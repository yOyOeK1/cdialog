
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

//int col = 50;
//int row = 10;
//bool asBar = false;
//int chFill = '.';
//
#endif

//int colTmp = 40; // should be replace / update with resize of window 
//A small plot' ) let map = " ▁▂▃▄▅▆▇"




/* to convert float to progress where input need to be 100.00 - 0.00 */
char *cPP_asProgress( float perc ){
	/*
	bTheme = [ ' ⠽','⠿','⠂','⠯ ' ];
        bTheme = [ '[_','▇','_','_]' ]; };
        */


	char *tr;
	tr = malloc( sizeof( char ) * ( col + 1 ) );
	snprintf( tr, col, "%03.0f%% %s", perc, "   " );  
	float nPerc = perc / 100.00L * ( col - 7 );
	for( int c=6; c<col; c++ ){
		if( (c-6) <= nPerc && nPerc != 0)
			tr[c] = '#';
		else 
			tr[c] = '_';
	}
	//printf("col[%i] from cPP_ nPerc [%f] \n", col, nPerc );
	return tr;
}

/* to convert long to time selft hh:mm:sec. */
char *cPP_secLeft( long secL ){
	//double secD = (double)secL;
	//printf("PP secDeft lf:[%lf] f:[%f] d:[%d] i:[%i]\n", secD, secD, secD, secD, secD );
	//printf("PP secLeft lf:[%lf] f:[%f] d:[%d] i:[%i]\n", secL, secL, secL, secL, secL );
	char *tr;
	tr = malloc(sizeof(char)*128);
	if( secL < 60 ){
		snprintf( tr, 128, "%i sec.", (int)secL );
	
	} else if( secL < 3600 ){
		int m = (int)(secL/60);
		secL = ((int)secL)%60;
		snprintf( tr, 128, "%i:%02i mm:s.", m, secL );
	
	} else {
		int h = (int)(secL/3600);
		int m = (int)(secL/60)%60;
		secL = ((int)secL)%60;
		
		snprintf( tr, 128, "%i:%02i:%02i hh:mm:s.", h, m, secL );

	}

	return tr;
}

char *cPP_asCompass( long mag ){
	char *tr = (char *)malloc( 361*sizeof( char) );
	int c;
	for( c=0; c<360; c++ ){
		if( (c%10) == 0 )
			tr[ c ] = '|';
		else if( (c%5) == 0 )
			tr[ c ] = ',';
		else 
			tr[ c ] = '.';
	}
	tr[360] = 0;
	int ang = 0;
	tr[ ang ] = 'N';
	ang+=44;
	tr[ ang++] = 'N'; tr[ang] = 'E';
	ang=90;
	tr[ang] = 'E';
	ang+=44;
	tr[ang++] = 'E'; tr[ang] = 'S';
	ang = 180;
	tr[ang] = 'S';
	ang+=44;
	tr[ang++] = 'S';	tr[ang] = 'W';
	ang = 270;
	tr[ang] = 'W';
	ang+=44;
	tr[ang++] = 'W';	tr[ang] = 'N';

	int ci = (int)mag;
	//printf("asCompass [%i] \n%s\n", ci, tr );

	char *trt = (char *)malloc( (col+1)*sizeof(char) );
	trt[col+1] = 0;
	int cNo = 0;
	int colH = col / 2;
	for( c=ci-colH; c<ci+colH; c++ ){
		//printf("c[%i]\n", c);
		trt[cNo++] = tr[ ((c+360)%360) ];	
	}
	//printf("asCompass [%i] \n%s\n", ci, trt );
	char *magStr = malloc( 4*sizeof(char) );
	snprintf( magStr, 4, "%03i", ci );
	
	trt[ colH-1 ] = magStr[0];
	trt[ colH ] = magStr[1];
	trt[ colH+1 ] = magStr[2];

	return trt;
}


#ifdef CPPTEST
int main( int argc, char *argv[] ){

	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;


	printf("c postprocess CPPTEST ... START size [ %ix%i ]\n", col, row);
	
	printf("SecLeft ... 10 is [%s]\n", cPP_secLeft(10) );
	printf("SecLeft ... 100 is [%s]\n", cPP_secLeft(100) );
	printf("SecLeft ... 1000 is [%s]\n", cPP_secLeft(1000) );
	printf("SecLeft ... 10000 is [%s]\n", cPP_secLeft(10000) );
	printf("SecLeft ... 100000 is [%s]\n", cPP_secLeft(100000) );


	printf("progress ... 0.00 is \n\t%s\n", cPP_asProgress( 0.00 ) );
	printf("progress ... 0.01 is \n\t%s\n", cPP_asProgress( 0.01 ) );
	printf("progress ... 30.00 is \n\t%s\n", cPP_asProgress( 30.00 ) );
	printf("progress ... 90.00 is \n\t%s\n", cPP_asProgress( 90.00 ) );
	printf("progress ... 99.99 is \n\t%s\n", cPP_asProgress( 99.99 ) );
	printf("progress ... 100.00 is \n\t%s\n", cPP_asProgress( 100.00 ) );


	printf("compass ... 10.00 is \n\t%s\n", cPP_asCompass( 10.00 ) );
	printf("compass ... 100.00 is \n\t%s\n", cPP_asCompass( 100.00 ) );
	long angg = 0.00;
	for( int a=0; a<360; a+=12){
		printf("compass ... %i is \n\t%s\n", angg, cPP_asCompass( angg ) );
		angg+= 12.31;
	}

	printf("c postprocess CPPTEST ... DONE\n");
	return 0;
}
#endif
