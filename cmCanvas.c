
#include <stdio.h>
#include <string.h>

#include "cnn_config_data.h"
#include "cmTools.h"
#include "ccanvas.h"
#include "ctermh.h"

// CNNCANVCLEAR 9
void cm_CanvClear_byId( int ccId ){
	for( int c=0; true; c++ ){
		if( cnn_Canvass[ c ].id == -1 ) break;
		if( cnn_Canvass[ c ].id == ccId ){
			cmt_NodeName("CNCANVCLEAR 2", cnn_Canvass[ c ].id, cnn_Canvass[ c ].name );
			if( cnn_Canvass[ c ].autoSize == false ){
				//ccInit_FB_byPointer( &cnn_Canvass[ c ].ccFB, cnn_Canvass[ c ].col, cnn_Canvass[ c ].row );
				cc_clear_byPointer(  &cnn_Canvass[ c ].ccFB, cnn_Canvass[ c ].ch, cnn_Canvass[ c ].col, cnn_Canvass[ c ].row );
			} else {
				int mc;
				int mr;
				ctermSize( &mc, &mr );
				ccInit_FB_byPointer( &cnn_Canvass[ c ].ccFB, mc-3, mr-3 );
				cc_clear_byPointer(  &cnn_Canvass[ c ].ccFB, cnn_Canvass[ c ].ch, mc-3, mr-3 );
			}
			break;
		}

	}

}
void cm_CanvClear( int ccId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_CanvClears[ i ].id == -1 ) break;
		if( cnn_CanvClears[ i ].id == ccId ){
			cmt_NodeName( "CM_CANVCLEARS 1", ccId, cnn_CanvClears[ i ].name );
			cm_CanvClear_byId(  cnn_CanvClears[ i ].canvId );
			break;
		}
	}
}

int cmCanvPrintf( int ccId, int x, int y, char *msg ){
    int i,ic,iOffset = 0, yColXI;
    int ccFBc = 11;
    int cols,rows;
    char *ccFB;		  

	for( int c=0; true ;c++ ){
		if( cnn_Canvass[ c ].id == -1 ) break;
		if( cnn_Canvass[ c ].id == ccId ){

			cols = cnn_Canvass[ c ].col;
			rows = cnn_Canvass[ c ].row;
			ccFBc =  cols * rows;
			ccFB = cnn_Canvass[ c ].ccFB;


					    
			    for( i=0,ic=strlen(msg); i<ic; i++){
				yColXI = y*cols+ x + i;
				if( ccFB[ yColXI + iOffset ] == '\n' ){
				    iOffset++;
				}

				if( (  yColXI + iOffset ) > ccFBc-2 ){
				    ccFB[ ccFBc-1 ] = 0;
				    return ccFBc;
				}

				if( msg[i] == '\n' ){
				    y++;
				    iOffset = -i - 1;
				}else {
				    ccFB[ yColXI + iOffset ] = msg[ i ];
				}
			    }





			break;
		}

	}


    return 0;

}
// CNNCANVPRINTF 10
void cm_CanvPrintf( int ccpId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_CanvPrintfs[ i ].id == -1 ) break;
		if( cnn_CanvPrintfs[ i ].id == ccpId ){
			cmt_NodeName( "CM_CANVPRINTF", ccpId, cnn_CanvPrintfs[ i ].name );
			//printf( cnnPrintfs[ i ].printAs, msg.payload );
			// TODO get canvas
			cmCanvPrintf( cnn_CanvPrintfs[ i ].canvId, 
				cnn_CanvPrintfs[ i ].x, cnn_CanvPrintfs[ i ].y, 
				msgT->payload 
				);
			// cc_printf on it
			
			break;
		}
	}

}

void cmCanvasRender( int cId ){
	for( int c=0; true; c++ ){
		if( cnn_Canvass[ c ].id == -1 ) break;
		if( cnn_Canvass[ c ].id == cId ){
			printf("#* ... render FB nudle id[%i]\n", cnn_Canvass[ c ].id );
			printf("render --- (%i)\n%s\n", cnn_Canvass[ c ].pCount++, cnn_Canvass[ c ].ccFB );
			break;
		}
		
	}
}
// CNNCANVRENDER 11
void cm_CanvRender( int ccrId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_CanvRenders[ i ].id == -1 ) break;
		if( cnn_CanvRenders[ i ].id == ccrId ){
			cmt_NodeName( "CM_CANVRENDER", ccrId, cnn_CanvRenders[ i ].name );
			cmCanvasRender( cnn_CanvRenders[ i ].canvId );
			break;
		}
	}
}
