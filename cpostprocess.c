
#include <stdlib.h>
#include <stdio.h>

int colTmp = 40; // should be replace / update with resize of window 

/* to convert float to progress where input need to be 100.00 - 0.00 */
char *cPP_asProgress( float perc ){
	char *tr;
	tr = malloc( sizeof( char ) * ( colTmp + 1 ) );
	snprintf( tr, colTmp, "%03.0f%% %s", perc, "   " );  
	float nPerc = perc / 100.00L * ( colTmp - 7 );
	for( int c=6; c<colTmp; c++ ){
		if( (c-6) <= nPerc && nPerc != 0)
			tr[c] = 'x';
		else 
			tr[c] = '_';
	}
	//printf("col[%i] from cPP_ nPerc [%f] \n", colTmp, nPerc );
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


