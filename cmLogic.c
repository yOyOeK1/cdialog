

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cnn_config_data.h"
#include "cmTools.h"
#include "timeh.h"
#include "cpostprocess.h"


// CNLIF 17
void cml_if( int nId, cnn_Msg *msgT ){
	bool isOk = false;
	for( int i=0; true; i++ ){
		if( cnn_ifs[ i ].id == -1 ) break;
		if( cnn_ifs[ i ].id == nId ){
			cmt_NodeName( "CM_IF", nId, cnn_ifs[ i ].name );
			if( cnn_ifs[ i ].ifType == CNLIF_EQUAL ){ // == 
				if( strcmp( msgT->payload, cnn_ifs[ i ].vThen ) == 0 ){
					isOk = true;
				}else{
					isOk = false;
				}

			} else if( cnn_ifs[ i ].ifType == CNLIF_DIFRENT ){ // != 
				if( strcmp( msgT->payload, cnn_ifs[ i ].vThen ) != 0 ){
					isOk = true;
				}else{
					isOk = false;
				}
			}

			printf(" | compare [%s] to [%s] \n", msgT->payload, cnn_ifs[ i ].vThen );
			if( isOk ){
				printf(" | IF OK\n");
			}else{
				printf(" | IF !OK\n");
			}
			break;
		}
	}
}

//// CNITIMESTAMP 15
//void cmi_timeStamp( int id, cnn_Msg *msgT ){
//	snprintf( msgT->payload, 512, "%i", time_now_stamp() );
//	//printf("\n\n..........\n"
//	//	"id[%i]"
//	//	"\n.........\n\n\n", id);
//
//}
//// CNITIMENOWTT 16
//void cmi_timeNowTT( int id, cnn_Msg *msgT ){
//	snprintf( msgT->payload, 512, "%s", time_now_tt() );
//}
//
