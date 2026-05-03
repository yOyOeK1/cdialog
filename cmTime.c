

#include <stdio.h>
#include <stdlib.h>

#include "cnn_config_data.h"
#include "cmTools.h"
#include "timeh.h"
#include "cpostprocess.h"


// CNNTIMESINCE 12
void cm_TimeSince( int tsId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_TimeSinces[ i ].id == -1 ) break;
		if( cnn_TimeSinces[ i ].id == tsId ){
			cmt_NodeName( "CM_TIMESINCE", tsId, cnn_TimeSinces[ i ].name );
			long int mesLong = strtol( msgT->payload, NULL, 10 );
			snprintf( msgT->payload, 512, 
				cnn_TimeSinces[ i ].printAs, cPP_secLeft( mesLong ) 
				);
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

}
// CNITIMENOWTT 16
void cmi_timeNowTT( int id, cnn_Msg *msgT ){
	snprintf( msgT->payload, 512, "%s", time_now_tt() );
}

