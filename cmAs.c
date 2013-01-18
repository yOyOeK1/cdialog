

#include <stdio.h>
#include <stdlib.h>

#include "cnn_config_data.h"
#include "cmTools.h"
#include "cpostprocess.h"

extern int col;
extern int row;
extern bool asBar;
extern int chFill;


// CNNPROGRESSBAR 13
void cm_ProgressBar( int pId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_ProgressBars[ i ].id == -1 ) break;
		if( cnn_ProgressBars[ i ].id == pId ){
			cmt_NodeName( "CM_PROGRESSBAR", pId, cnn_ProgressBars[ i ].name );
			long int mesLong = strtol( msgT->payload, NULL, 10 );
			col = cnn_ProgressBars[ i ].width;
			snprintf( msgT->payload, 512, 
				cnn_ProgressBars[ i ].printAs, cPP_asProgress( mesLong ) 
				);
			break;
		}
	}
}
// CNNASCOMPAS 14
void cm_Compas( int nId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_Compass[ i ].id == -1 ) break;
		if( cnn_Compass[ i ].id == nId ){
			cmt_NodeName( "CM_COMPASS", nId, cnn_Compass[ i ].name );
			long int mesLong = strtol( msgT->payload, NULL, 10 );
			col = cnn_Compass[ i ].width;
			snprintf( msgT->payload, 512, 
				cnn_Compass[ i ].printAs, cPP_asCompass( mesLong ) 
				);
			break;
		}
	}
}

