

#include <stdio.h>

#include "cnn_config_data.h"
#include "cmTools.h"
#include "cmachine2.h"

void cmInit_cnnAtStart(){
	for( int n=0; true; n++ ){
		if( cnnAtStarts[ n ].id == -1 ) break;
		if( cnnAtStarts[ n ].onStart ){ 
			printf("\n ### AUTOSTART ... START\n |\n");
			cmt_NodeName("CN_ATSTART", cnnAtStarts[ n ].id, cnnAtStarts[ n ].name );
			cnn_Msg msgT;
			cm_doClick( 0, cnnAtStarts[ n ].msgId, msgT, CNNATSTART, cnnAtStarts[ n ].id );
			printf(" | \n \\ ___ ### AUTOSTART ... END\n");

		}
		printf("\n");
	}
}

