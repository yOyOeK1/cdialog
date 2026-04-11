
#include <stdlib.h>
#include <stdio.h>


extern int col;
extern int row;
extern bool asBar;
extern int chFill;


//int colTmp = 40; // should be replace / update with resize of window 

/* to convert float to progress where input need to be 100.00 - 0.00 */
char *cPP_asProgress( float perc ){
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


