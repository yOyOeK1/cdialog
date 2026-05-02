

#include <stdio.h>

//#include "config.h"
#include "cnn_config_data.h"
#include "cmTools.h"
#include "cmachine2.h"

#include "ctermh.h"
#include "ccanvas.h"

void cmInit_machNs(){
	for( int p=0; true; p++ ){
		if( machNs[ p ].id == -1 ) break;
		printf("\n\n*[%i] id[%i] ... onStart[%i] every[%ims] \n\t - %s\n", p, 
			machNs[ p ].id, machNs[ p ].onStart, machNs[ p ].everyMs, machNs[ p ].name 
			);
		if( machNs[ p ].onStart )
			cmt_start_byNode( machNs[ p ] );
	
	}
}

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

void cmInit_cnCanvass(){
	for( int c=0; true; c++ ){
		if( cnn_Canvass[ c ].id == -1 ) break;
		printf("#* ... init FB nudle id[%i]\n", cnn_Canvass[ c ].id);
		cmt_NodeName("CNCANVAS", cnn_Canvass[ c ].id, cnn_Canvass[ c ].name );
		cnn_Canvass[ c ].pCount = 0;
		if( cnn_Canvass[ c ].autoSize == false ){
			ccInit_FB_byPointer( &cnn_Canvass[ c ].ccFB, cnn_Canvass[ c ].col, cnn_Canvass[ c ].row );
			cc_clear_byPointer(  &cnn_Canvass[ c ].ccFB, cnn_Canvass[ c ].ch, cnn_Canvass[ c ].col, cnn_Canvass[ c ].row );
		} else {
			int mc;
			int mr;
			ctermSize( &mc, &mr );
			cnn_Canvass[ c ].col = mc-3;
			cnn_Canvass[ c ].row = mr-3;
			ccInit_FB_byPointer( &cnn_Canvass[ c ].ccFB, mc-3, mr-3 );
			cc_clear_byPointer(  &cnn_Canvass[ c ].ccFB, cnn_Canvass[ c ].ch, mc-3, mr-3 );
		}
	}
}

