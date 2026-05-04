
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cnn_config_data.h"
#include "cmTools.h"
#include "cmachine2.h"

void cm_div( int id, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnDivs[ i ].id == -1 ) break;
		if( cnnDivs[ i ].id == id ){
			cmt_NodeName( "CM_DIVS", id, cnnDivs[ i ].name );
			float fin = atof( msgT->payload );
			fin/= cnnDivs[ i ].divBy;
			printf("[DEB] div %s by %f res [%f]\n",  msgT->payload, cnnDivs[ i ].divBy, fin );
			snprintf( msgT->payload, 512, "%f", fin );
			
			cm_doWorkAt_byNId( id, CNNDIV, 0, msgT );

			break;
		}
	}	
}

void cm_add( int id, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnAdds[ i ].id == -1 ) break;
		if( cnnAdds[ i ].id == id ){
			cmt_NodeName( "CM_ADDS", id, cnnAdds[ i ].name );
			float fin = atof( msgT->payload );
			fin+= cnnAdds[ i ].add;
			printf("[DEB] add %f to %s res [%f]\n", cnnAdds[ i ].add, msgT->payload, fin );
			snprintf( msgT->payload, 512, "%f", fin );
			
			cm_doWorkAt_byNId( id, CNNADD, 0, msgT );

			break;
		}
	}	
}

