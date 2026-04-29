
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mosquitto.h>


#define CMACHINEVER "2026.0425"

extern int col;
extern int row;
extern bool asBar;
extern int chFill;

#ifndef CPPMACHINE


#else

#include "cnn_config_data.h"

#include "config.h"
#include "configKeys.h"
#include "ctermh.h"
#include "ckeyh.h"
#include "mqtth.h"
#include "ccanvas.h"
#include "cargs.h"
#include "cpostprocess.h"

#endif

#include "cmdh.h"

char cmachBuff[512];

void cmachine_start_byNode( struct machNode mn ){
	printf("\t* start by id ... %i\n", mn.id );	

	if( mn.typeOf == 0 ){ // cmd
		mn.isRunning = true;
		strcpy( mn.result, cmd_to_chars( mn.cmd ) );
		printf( "\t* ... result [ %s ]\n", mn.result );

	}else{
		printf("\tEE type not implemented [%i]\n", mn.typeOf );
	}
}


void cmiNodeName( char *type, int id, char *name ){
	printf(" |\n |__  %s id[%i][ %s ]\n |\n", type, id, name );
}


int cm_getMsgIndexById( int id ){
	for( int i=0; true; i++){
		if( cnMs[ i ].id == -1 ) break;
		if( cnMs[ i ].id == id ) return i;
	}
	return -1;
}


int cm_getDivIndexById( int id ){
	for( int i=0; true; i++){
		if( cnnDivs[ i ].id == -1 ) break;
		if( cnnDivs[ i ].id == id ) return i;
	}
	return -1;
}

void cm_div( int id, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnDivs[ i ].id == -1 ) break;
		if( cnnDivs[ i ].id == id ){
			//printf("CM_divs id:%i, \n", id);
			cmiNodeName( "CM_DIVS", id, cnnDivs[ i ].name );
			if( 1 /* msgId != -1*/ ){
				float fin = atof( msgT->payload );
				fin/= cnnDivs[ i ].divBy;
				printf("[DEB] div %s by %f res [%f]\n",  msgT->payload, cnnDivs[ i ].divBy, fin );
				snprintf( msgT->payload, 512, "%f", fin );
			}
			break;
		}
	}	
}


int cm_getAddIndexById( int id ){
	for( int i=0; true; i++){
		if( cnnAdds[ i ].id == -1 ) break;
		if( cnnAdds[ i ].id == id ) return i;
	}
	return -1;
}

void cm_add( int id, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnAdds[ i ].id == -1 ) break;
		if( cnnAdds[ i ].id == id ){
			//printf("CM_adds id:%i, \n", id);
			cmiNodeName( "CM_ADDS", id, cnnAdds[ i ].name );
			if( 1 /* msgId != -1 */ ){
				float fin = atof( msgT->payload );
				fin+= cnnAdds[ i ].add;
				printf("[DEB] add %f to %s res [%f]\n", cnnAdds[ i ].add, msgT->payload, fin );
				snprintf( msgT->payload, 512, "%f", fin );


			}
			break;
		}
	}	
}
void cm_printf( int id, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnPrintfs[ i ].id == -1 ) break;
		if( cnnPrintfs[ i ].id == id ){
			//printf("CM_PRINTF id:%i, \n", id);
			cmiNodeName( "CM_PRINTF", id, cnnPrintfs[ i ].name );
			if( 1 /*msgId != -1*/ ){
				if( cnnPrintfs[ i ].doTopic ){
					printf("* Topic: ... %s\n", msgT->topic );
				}
				printf( cnnPrintfs[ i ].printAs, msgT->payload );
			}
			break;
		}
	}	
}

void cm_cmd( int cmdId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnnCmds[ i ].id == -1 ) break;
		if( cnnCmds[ i ].id == cmdId ){
			cmiNodeName( "CM_CMD", cmdId, cnnCmds[ i ].name );
			if( 1 /*msgId != -1*/ ){
				printf(" | ...... cmd START ---\\ \n");
				strcpy( msgT->payload, cmd_to_chars( cnnCmds[ i ].cmd ) );
				printf(" | ...... cmd END -----/\n");
				//printf( cnnPrintfs[ i ].printAs, msg.payload );
			}
			break;
		}
	}	
}
struct mosquitto *mqHea;
bool mqConnected = false;
void cm_mqttPub( int mqttPubId, cnn_Msg *msgT ){
	for( int i=0; true; i++ ){
		if( cnn_MqttPubs[ i ].id == -1 ) break;
		if( cnn_MqttPubs[ i ].id == mqttPubId ){
			cmiNodeName( "CM_MQTT_PUB", mqttPubId, cnn_MqttPubs[ i ].name );
			if( 1 /*msgId != -1*/ ){
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
			}
			break;
		}
	}	
}


cnn_Msg cm_msgClone( int msgId ){
	cnn_Msg msg = cnMs[ cm_getMsgIndexById( msgId ) ];
	cnn_Msg tr = {};//{ .id=-1, .topic="t", .payload="abc" };
	strcpy( tr.topic, msg.topic );
	strcpy( tr.payload, msg.payload );
	printf(" | . . .  cm message clone DONE\n");
	return tr;
}

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

	}else{
		printf("\n# EE not implemented 9898\n");
		return false;
	}
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

void cmInit_atStart(){
	for( int n=0; true; n++ ){
		if( cnnAtStarts[ n ].id == -1 ) break;
		if( cnnAtStarts[ n ].onStart ){ 
			printf("\n ### AUTOSTART ... START\n |\n");
			cmiNodeName("CN_ATSTART", cnnAtStarts[ n ].id, cnnAtStarts[ n ].name );
			cnn_Msg msgT;
			cm_doClick( 0, cnnAtStarts[ n ].msgId, msgT, CNNATSTART, cnnAtStarts[ n ].id );
			printf(" | \n \\ ___ ### AUTOSTART ... END\n");

		}
		printf("\n");
	}
}

void cmInit_cnCanvass(){
	for( int c=0; true; c++ ){
		if( cnCanvass[ c ].id == -1 ) break;
		printf("#* ... init FB nudle id[%i]\n", cnCanvass[ c ].id);
		cmiNodeName("CNCANVAS", cnCanvass[ c ].id, cnCanvass[ c ].name );
		cnCanvass[ c ].pCount = 0;
		if( cnCanvass[ c ].autoSize == false ){
			ccInit_FB_byPointer( &cnCanvass[ c ].ccFB, cnCanvass[ c ].col, cnCanvass[ c ].row );
			cc_clear_byPointer(  &cnCanvass[ c ].ccFB, cnCanvass[ c ].ch, cnCanvass[ c ].col, cnCanvass[ c ].row );
		} else {
			int mc;
			int mr;
			ctermSize( &mc, &mr );
			ccInit_FB_byPointer( &cnCanvass[ c ].ccFB, mc-3, mr-3 );
			cc_clear_byPointer(  &cnCanvass[ c ].ccFB, cnCanvass[ c ].ch, mc-3, mr-3 );
				

		}

	}
}
void cmCanvasRender( int cId ){
	for( int c=0; true; c++ ){
		if( cnCanvass[ c ].id == -1 ) break;
		if( cnCanvass[ c ].id == cId ){
			printf("#* ... render FB nudle id[%i]\n", cnCanvass[ c ].id );
			printf("render ---\n%s\n", cnCanvass[ c ].ccFB );
			break;
		}
		
	}
}

void cmInit(){

	//ccInit_FB_nudle( &cnCanvass );
	//cc_clear( chFill );
	//cmInit_cnCanvass();

	cmInit_atStart();

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
					int msgIndex = cm_getMsgIndexById( cnn_MqttSubs[ s ].msgId  );
					strcpy( cnMs[ msgIndex  ].topic, message->topic );
					strcpy( cnMs[ msgIndex  ].payload, message->payload );
					//cm_doClick( 0, 1, cnnNudles[ n ].targetType, cnnNudles[ n ].targetId );
					cmiNodeName("CNNMQTTSUB", cnn_MqttSubs[ s ].id, cnn_MqttSubs[ s ].name );
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

void cmInit_machNs(){
	for( int p=0; true; p++ ){
		if( machNs[ p ].id == -1 ) break;
		printf("\n\n*[%i] id[%i] ... onStart[%i] every[%ims] \n\t - %s\n", p, 
			machNs[ p ].id, machNs[ p ].onStart, machNs[ p ].everyMs, machNs[ p ].name 
			);
		if( machNs[ p ].onStart )
			cmachine_start_byNode( machNs[ p ] );
	
	}
}

#ifdef CPPMACHINE
int main( int argc, char *argv[] ){
	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;

	printf("cmachine2 ver[%s]\n", CMACHINEVER );

	if(0){
		printf("c cmachine2 CPPMACHINE2 ... START size [ %ix%i ]@%s\n", col, row, machineName );
		cmInit_machNs();
		printf("c cmachine2 CPPMACHINE2 ... END size [ %ix%i ]@%s\n", col, row, machineName );


		printf("c cmachine2 -- 2 CPPMACHINE2 ... DONE .. NUDLE SECTION\n");
		cmInit_atStart();
		printf("c cmachine2 -- 2 CPPMACHINE2 ... END  .. NUDLE SECTION\n");


		printf("c cmachine2 -- 3 CPPMACHINE2 ... START mqtt init \n"
			"\t- mqtt hosts:	[ %i ]\n", MqHostsCount );
		mqttInit2( &cnn_mqtt_on_message );
		mqttDoIt2();
		printf("c cmachine2 -- 3 CPPMACHINE2 ... END\n");
		


		printf("c cmachine2 -- 4 CPPKEYBIND... START\n");
		keyBindDoIt();
		printf("c cmachine2 -- 4 CPPKEYBIND... END\n");

	//mqttInit();
	//mqttDoIt();
	}

	cmInit_cnCanvass();
	cmCanvasRender( 2 );

	printf("c cmachine2 CPPMACHINE2 ... DONE\n");
	printf("cnn_Version	[%s]\n", cnn_Version );
	printf("cmachine2 ver	[%s]\n", CMACHINEVER );
	return 0;
}
#endif
