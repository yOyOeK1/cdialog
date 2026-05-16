
#include <stdio.h>

#include "cnn_config_data.h"
#include "cmachine2.h"
#include "cmTools.h"

#include "cmdh.h"


void cm_printf( int id, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnPrintfs[ i ].id == -1 ) break;
		if( cnnPrintfs[ i ].id == id ){
			cmt_NodeName( "CM_PRINTF", id, cnnPrintfs[ i ].name );
			if( cnnPrintfs[ i ].doTopic ){
				printf("* Topic: ... %s\n", msgT->topic );
			}
			printf( cnnPrintfs[ i ].printAs, msgT->payload );
			
			cm_doWorkAt_byNId( id, CNNPRINTF, 0, msgT );

			break;
		}
	}	
}
// CNNCMD 6 
void cm_cmd( int nId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnCmds[ i ].id == -1 ) break;
		if( cnnCmds[ i ].id == nId ){
			cmt_NodeName( "CM_CMD", nId, cnnCmds[ i ].name );
			cmtDeb( "cmCmd", " | ...... cmd START ---\\ \n");
			strcpy( msgT->payload, cmd_to_chars( cnnCmds[ i ].cmd ) );
			//msgT->payload[511] = 0;
			cmtDeb( "cmCmd", " | ...... cmd END -----/ (%i)\n", strlen(msgT->payload) );
			//printf( cnnPrintfs[ i ].printAs, msg.payload );
			
			cm_doWorkAt_byNId( nId, CNNCMD, 0, msgT );

			break;
		}
	}	
}
