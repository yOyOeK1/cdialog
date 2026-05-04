

#include <stdio.h>
#include <stdlib.h>

#include "cnn_config_data.h"
#include "cmTools.h"
#include "cmachine2.h"
#include "timeh.h"
#include "cpostprocess.h"


// CNNTIMESINCE 12
void cm_TimeSince( int nId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_TimeSinces[ i ].id == -1 ) break;
		if( cnn_TimeSinces[ i ].id == nId ){
			cmt_NodeName( "CM_TIMESINCE", nId, cnn_TimeSinces[ i ].name );
			long int mesLong = strtol( msgT->payload, NULL, 10 );
			snprintf( msgT->payload, 512, 
				cnn_TimeSinces[ i ].printAs, cPP_secLeft( mesLong ) 
				);
			cm_doWorkAt_byNId( nId, CNNTIMESINCE, 0, msgT );
			break;
		}
	}
}

// CNITIMESTAMP 15
void cmi_timeStamp( int id, cnn_Msg *msgT ){
	snprintf( msgT->payload, 512, "%i", time_now_stamp() );
	//printf("\n\n..........\n"
	//	"id[%i]"
	//	"\n.........\n\n\n", id);
	
	cm_doWorkAt_byNId( id, CNITIMESTAMP, 0, msgT );

}
// CNITIMENOWTT 16
void cmi_timeNowTT( int id, cnn_Msg *msgT ){
	snprintf( msgT->payload, 512, "%s", time_now_tt() );
	cm_doWorkAt_byNId( id, CNITIMENOWTT, 0, msgT );
}

