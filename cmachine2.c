
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mosquitto.h>


#define CMACHINEVER "2026.0503"

extern int col;
extern int row;
extern bool asBar;
extern int chFill;

#ifndef CPPMACHINE


#else

#include "cnn_config_data.h"


#include "config.h"
//#include "configKeys.h"
#include "cmTools.h"
#include "cmInits.h"
#include "cmTime.h"
#include "cmCanvas.h"
//#include "ctermh.h"
//#include "timeh.h"
#include "ckeyh.h"
#include "mqtth.h"
//#include "ccanvas.h"
#include "cargs.h"
#include "cpostprocess.h"

#endif

#include "cmdh.h"

char cmachBuff[512];



int cm_msg_getIndex_byId( int id ){
	for( int i=0; true; i++){
		if( cnMs[ i ].id == -1 ) break;
		if( cnMs[ i ].id == id ) return i;
	}
	return -1;
}

cnn_Msg cm_msgClone( int msgId ){
	cnn_Msg msg = cnMs[ cm_msg_getIndex_byId( msgId ) ];
	cnn_Msg tr = {};//{ .id=-1, .topic="t", .payload="abc" };
	strcpy( tr.topic, msg.topic );
	strcpy( tr.payload, msg.payload );
	printf(" | . . .  cm message clone DONE\n");
	return tr;
}

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

void cm_printf( int id, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnPrintfs[ i ].id == -1 ) break;
		if( cnnPrintfs[ i ].id == id ){
			cmt_NodeName( "CM_PRINTF", id, cnnPrintfs[ i ].name );
			if( cnnPrintfs[ i ].doTopic ){
				printf("* Topic: ... %s\n", msgT->topic );
			}
			printf( cnnPrintfs[ i ].printAs, msgT->payload );
			break;
		}
	}	
}
// CNNCMD 6 
void cm_cmd( int cmdId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnCmds[ i ].id == -1 ) break;
		if( cnnCmds[ i ].id == cmdId ){
			cmt_NodeName( "CM_CMD", cmdId, cnnCmds[ i ].name );
			printf(" | ...... cmd START ---\\ \n");
			strcpy( msgT->payload, cmd_to_chars( cnnCmds[ i ].cmd ) );
			printf(" | ...... cmd END -----/\n");
			//printf( cnnPrintfs[ i ].printAs, msg.payload );
			break;
		}
	}	
}

// CNNMQTTPUB 8
struct mosquitto *mqHea;
bool mqConnected = false;
void cm_mqttPub( int mqttPubId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_MqttPubs[ i ].id == -1 ) break;
		if( cnn_MqttPubs[ i ].id == mqttPubId ){
			cmt_NodeName( "CM_MQTT_PUB", mqttPubId, cnn_MqttPubs[ i ].name );
			printf(" | ...... mqtt pub START ---\\ \n"
				" | ...		mqtt host id	[%i]\n"
				" | ... 	topic 	[%s]\n"
				" | ... 	payload	[%s]\n"
				" |\n",
				cnn_MqttPubs[ i ].mqHostId, msgT->topic, msgT->payload );

			if( mqConnected ){
				//mqtth_publish_byHea( mqHea, "and/ping", "abc" );
				mqtth_publish_byHea( mqHea, msgT->topic, msgT->payload );
			} else {
				printf("[DEB EE] mqtt not connected yet\n");
			}

			printf(" | ...... mqtt pub  END -----/\n");
			//printf( cnnPrintfs[ i ].printAs, msg.payload );
			break;
		}
	}	
}

// ------------------------------
bool cm_doWorkAt( cnn_Msg *msgT, int nType, int nId ){
	if( nType == CNNPRINTF ){
		cm_printf( nId, msgT);
		return true;

	}else if( nType == CNNDIV ){
		cm_div( nId, msgT );
		return true;

	}else if( nType == CNNADD ){
		cm_add( nId, msgT );
		return true;

	}else if( nType == CNNCMD ){
		cm_cmd( nId, msgT );
		return true;

	}else if( nType == CNNMQTTPUB ){
		cm_mqttPub( nId, msgT );
		return true;

	}else if( nType == CNNCANVCLEAR ){
		cm_CanvClear( nId, msgT );
		return true;
		
	}else if( nType == CNNCANVPRINTF ){
		cm_CanvPrintf( nId, msgT );
		return true;

	}else if( nType == CNNCANVRENDER ){
		cm_CanvRender( nId, msgT );
		return true;

	}else if( nType == CNNTIMESINCE ){
		cm_TimeSince( nId, msgT );
		return true;

	}else if( nType == CNNPROGRESSBAR ){
		cm_ProgressBar( nId, msgT );
		return true;

	}else if( nType == CNNCOMPAS ){
		cm_Compas( nId, msgT );
		return true;

	}

	// skip to 14 ifs above are doing it
	for( int h=14; true; h++ ){
		if( cnn_Hashs[ h ].id == -1 ) break;

		printf(" | ## looking in hashs ...\n"
				" | ##% 3i|% 3i| %c | % 3i|% 16p| %s\n",
			h, cnn_Hashs[ h ].id,
			( cnn_Hashs[ h ].isNode ? 'X' : ' ' ),
			cnn_Hashs[ h ].nType,
			cnn_Hashs[ h ].fPts, cnn_Hashs[ h ].name
			);

		if( nType == cnn_Hashs[ h ].nType ){
			printf(" | ## cnn Hashs OK [ %s ]!\n", cnn_Hashs[ h ].name );
			cmt_NodeName( "CM_HASHS", cnn_Hashs[ h ].id, cnn_Hashs[ h ].name );
			cnn_Hashs[ h ].fPts( nId, msgT );
			return true;
		}


	}

	return false;
	
}

void cm_doClick( int level, int msgId, cnn_Msg msgTp, int srcType, int srcId ){
	bool msgClone = false;
	cnn_Msg msgT;
	if( level == 0 ){
		printf(" | . . . "
			" level(%i) srcType[%i] srcId[%i] \n", level, srcType, srcId );
		if( msgId != -1 ){
			printf(" | . . .  With msg id[%i]\n", msgId );
			msgT = cm_msgClone( msgId );
			msgClone = true;
		} else { 
			printf("# msgT blank topic [%s] payload [%s]\n", msgT.topic, msgT.payload );
		}
	} else {
		printf(" | . . . msgT reuse\n");
		msgT = msgTp;
	}

	int doClick = false;
	for( int ni=0; true; ni++ ){
		if( cnnNudles[ ni ].id == -1 ) break;
		if( cnnNudles[ ni ].srcType == srcType &&
			cnnNudles[ ni ].srcId == srcId ){

			printf(" |\n |\n *--- nudle id[%i]\n |\n", cnnNudles[ ni ].id );
			doClick = cm_doWorkAt( &msgT, cnnNudles[ ni ].targetType, cnnNudles[ ni ].targetId );

			if( doClick ){
				cm_doClick( level+1, msgId, msgT, cnnNudles[ ni ].targetType, cnnNudles[ ni ].targetId );
			}else{
				printf(" \\ __ ... nudle id[%i] END\n", cnnNudles[ ni ].id );
			}

		}
	}

}

void cmInit(){

	//ccInit_FB_nudle( &cnn_Canvass );
	//cc_clear( chFill );
	//cmInit_cnCanvass();

	cmInit_cnnAtStart();

	//ccRender();

}

void cnn_mqtt_on_message( struct mosquitto *mosq, void *obj, const struct mosquitto_message *message ){
	mqHea = mosq;
	mqConnected = true;
	int sIndex = -1;
	for( int s=0; s<cnn_MqttSubsCount; s++ ){
		if( strcmp( cnn_MqttSubs[ s ].topic, message->topic ) == 0 ){
			sIndex = s;
		
			printf(" * OK cm2 mqtt msg ... index[%i] obj [%i]\n * _ topic: [%s] %s\n", sIndex, message->mid, message->topic, message->payload ); 

			for( int n=0; true; n++ ){
				if( cnnNudles[ n ].id == -1 ) break;

				if( cnnNudles[ n ].srcType == CNNMQTTSUB &&
					cnnNudles[ n ].srcId == cnn_MqttSubs[ s ].id ){
					printf(" */ mqtt got nudle .... n[%i] type[%i] id[%i] msgId[%i]\n", n, cnnNudles[ n ].targetType, cnnNudles[ n ].targetId, cnn_MqttSubs[ s ].msgId );
					if( cnn_MqttSubs[ s ].msgId == 0 ){
					} else {
						int msgIndex = cm_msg_getIndex_byId( cnn_MqttSubs[ s ].msgId  );
						strcpy( cnMs[ msgIndex  ].topic, message->topic );
						strcpy( cnMs[ msgIndex  ].payload, message->payload );
					}
					//cm_doClick( 0, 1, cnnNudles[ n ].targetType, cnnNudles[ n ].targetId );
					cmt_NodeName("CNNMQTTSUB", cnn_MqttSubs[ s ].id, cnn_MqttSubs[ s ].name );
					cnn_Msg msgT;
					cm_doClick( 0, cnn_MqttSubs[ s ].msgId, msgT, cnnNudles[ n ].srcType, cnnNudles[ n ].srcId );

				}


			}
			printf(" | \n \\ ___ ### CNNMQTTSUB ... END\n");
		} 
	}
	if( sIndex == -1 ){
		printf(" * cm2 mqtt msg ... topic: [%s]\n *\t[ %s ]\n", message->topic, message->payload ); 
	}


}	

void cmInit_mqtt(){
	mqttInit2( &cnn_mqtt_on_message );
	mqttDoIt2();
}

#ifdef CPPMACHINE
int main( int argc, char *argv[] ){
	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;

	printf("cmachine2 [%s]\n * target [%s]\n * ver[%s]\n", cnn_name, cnn_target, CMACHINEVER );

	if( 0 ){
		cmt_hashsDump();
		return 1;
	}
	if( 0 ){
		// pointer function ? START
		printf("pts to cm_Printf [%p] as int[%i]\n", cm_printf,(int)cm_printf );
		void (*cmf)(int, cnn_Msg * );
		cnn_Msg msgt = { -1, "and/testHot123", "989898" };
		cmf = &cm_printf;
		cmf( 1, &msgt );
		cmf = &cm_div;
		cmf( 1, &msgt );
		cm_add( 1, &msgt );
		cm_TimeSince( 1, &msgt );
		cm_printf( 1, &msgt );
		strcpy( msgt.payload, "90 % :)" );
		cm_ProgressBar( 1, &msgt );
		cm_printf( 1, &msgt );
		return 0;
		// pointer function ? END 
	}

	if(1){
	//	printf("c cmachine2 CPPMACHINE2 ... START size [ %ix%i ]@%s\n", col, row, machineName );
	//	cmInit_machNs();
	//	printf("c cmachine2 CPPMACHINE2 ... END size [ %ix%i ]@%s\n", col, row, machineName );


		printf("c cmachine2 -- 2 CPPMACHINE2 ... DONE .. NUDLE SECTION\n");
		cmInit_cnnAtStart();
		printf("c cmachine2 -- 2 CPPMACHINE2 ... END  .. NUDLE SECTION\n");

//	return 1;
		printf("c cmachine2 -- 3 CPPMACHINE2 ... START mqtt init \n"
			"\t- mqtt hosts:	[ %i ]\n", MqHostsCount );
		cmInit_mqtt();
		printf("c cmachine2 -- 3 CPPMACHINE2 ... END\n");
		

		cmInit_cnCanvass();
		//cmCanvasRender( 2 );

		printf("c cmachine2 -- 4 CPPKEYBIND... START\n");
		keyBindDoIt();
		printf("c cmachine2 -- 4 CPPKEYBIND... END\n");

	}


	printf("c cmachine2 CPPMACHINE2 ... DONE\n");
	printf("cnn_Version	[%s]\n", cnn_Version );
	printf("cmachine2 ver	[%s]\n", CMACHINEVER );
	return 0;
}
#endif
