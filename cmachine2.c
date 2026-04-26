
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

void cm_div( int id, int msgId ){
	for( int i=0; true; i++ ){
		if( cnnDivs[ i ].id == -1 ) break;
		if( cnnDivs[ i ].id == id ){
			//printf("CM_divs id:%i, \n", id);
			cmiNodeName( "CM_DIVS", id, cnnDivs[ i ].name );
			if( msgId != -1 ){
				cnn_Msg *msg = &cnMs[ cm_getMsgIndexById( msgId ) ];   
				float fin = atof( msg->payload );
				fin/= cnnDivs[ i ].divBy;
				printf("[DEB] div %s by %f res [%f]\n",  msg->payload, cnnDivs[ i ].divBy, fin );
				snprintf( msg->payload, 512, "%f", fin );


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

void cm_add( int id, int msgId ){
	for( int i=0; true; i++ ){
		if( cnnAdds[ i ].id == -1 ) break;
		if( cnnAdds[ i ].id == id ){
			//printf("CM_adds id:%i, \n", id);
			cmiNodeName( "CM_ADDS", id, cnnAdds[ i ].name );
			if( msgId != -1 ){
				cnn_Msg *msg = &cnMs[ cm_getMsgIndexById( msgId ) ];   
				float fin = atof( msg->payload );
				fin+= cnnAdds[ i ].add;
				printf("[DEB] add %f to %s res [%f]\n", cnnAdds[ i ].add, msg->payload, fin );
				snprintf( msg->payload, 512, "%f", fin );


			}
			break;
		}
	}	
}
void cm_printf( int id, int msgId ){
	for( int i=0; true; i++ ){
		if( cnnPrintfs[ i ].id == -1 ) break;
		if( cnnPrintfs[ i ].id == id ){
			//printf("CM_PRINTF id:%i, \n", id);
			cmiNodeName( "CM_PRINTF", id, cnnPrintfs[ i ].name );
			if( msgId != -1 ){
				cnn_Msg msg = cnMs[ cm_getMsgIndexById( msgId ) ];
				if( cnnPrintfs[ i ].doTopic ){
					printf("* Topic: ... %s\n", msg.topic );
				}
				printf( cnnPrintfs[ i ].printAs, msg.payload );
			}
			break;
		}
	}	
}

void cm_cmd( int cmdId, int msgId ){
	for( int i=0; true; i++ ){
		if( cnnCmds[ i ].id == -1 ) break;
		if( cnnCmds[ i ].id == cmdId ){
			cmiNodeName( "CM_CMD", cmdId, cnnCmds[ i ].name );
			if( msgId != -1 ){
				cnn_Msg *msg = &cnMs[ cm_getMsgIndexById( msgId ) ];
				printf(" | ...... cmd START ---\\ \n");
				strcpy( msg->payload, cmd_to_chars( cnnCmds[ i ].cmd ) );
				printf(" | ...... cmd END -----/\n");
				//printf( cnnPrintfs[ i ].printAs, msg.payload );
			}
			break;
		}
	}	
}

void cm_doClick( int level, int msgId, int srcType, int srcId ){
	if( level == 0 ){
		printf(" | . . . ");
		printf(" level(%i) ", level );
		if( msgId != -1 ) 
			printf("# With msg id[%i] ", msgId );
		else 
			printf("0");
		printf("\n |\n");
	}

	int doClick = false;
	for( int ni=0; true; ni++ ){
		if( cnnNudles[ ni ].id == -1 ) break;
		if( cnnNudles[ ni ].srcType == srcType &&
			cnnNudles[ ni ].srcId == srcId ){

			printf(" |\n |--- nudle id[%i]\n |\n", cnnNudles[ ni ].id );
			if( cnnNudles[ ni ].targetType == CNNPRINTF ){
				cm_printf( cnnNudles[ ni ].targetId, msgId );
				doClick = true;

			}else if( cnnNudles[ ni ].targetType == CNNDIV ){
				cm_div( cnnNudles[ ni ].targetId, msgId );
				doClick = true;

			}else if( cnnNudles[ ni ].targetType == CNNADD ){
				cm_add( cnnNudles[ ni ].targetId, msgId );
				doClick = true;

			}else if( cnnNudles[ ni ].targetType == CNNCMD ){
				cm_cmd( cnnNudles[ ni ].targetId, msgId );
				doClick = true;

			}else{
				printf("\n# EE not implemented 9898\n");
				doClick = false;
			}

			if( doClick ){
				cm_doClick( level+1, msgId, cnnNudles[ ni ].targetType, cnnNudles[ ni ].targetId );
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
			cm_doClick( 0, cnnAtStarts[ n ].msgId, CNNATSTART, cnnAtStarts[ n ].id );
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
			//cc_clear_byPointer(  &cnCanvass[ c ].ccFB, cnCanvass[ c ].ch, mc-3, mr-3 );
				

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
					cm_doClick( 0, cnn_MqttSubs[ s ].msgId, cnnNudles[ n ].srcType, cnnNudles[ n ].srcId );

				}


			}
			printf(" | \n \\ ___ ### CNNMQTTSUB ... END\n");
		} 
	}
	if( sIndex == -1 ){
		printf(" * cm2 mqtt msg ... topic: [%s]\n *\t[ %s ]\n", message->topic, message->payload ); 
	}


}	

#ifdef CPPMACHINE
int main( int argc, char *argv[] ){
	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;

	printf("cmachine2 ver[%s]\n", CMACHINEVER );
	printf("c cmachine2 CPPMACHINE2 ... START size [ %ix%i ]@%s\n", col, row, machineName );
	for( int p=0; true; p++ ){
		if( machNs[ p ].id == -1 ) break;
		printf("\n\n*[%i] id[%i] ... onStart[%i] every[%ims] \n\t - %s\n", p, 
			machNs[ p ].id, machNs[ p ].onStart, machNs[ p ].everyMs, machNs[ p ].name 
			);
		if( machNs[ p ].onStart )
			cmachine_start_byNode( machNs[ p ] );
	
	}
	printf("c cmachine2 CPPMACHINE2 ... END size [ %ix%i ]@%s\n", col, row, machineName );


	printf("c cmachine2 -- 2 CPPMACHINE2 ... DONE .. NUDLE SECTION\n");
	cmInit();
	printf("c cmachine2 -- 2 CPPMACHINE2 ... END  .. NUDLE SECTION\n");


	printf("c cmachine2 -- 3 CPPMACHINE2 ... START mqtt init \n"
		"\t- mqtt hosts:	[ %i ]\n", MqHostsCount );
	mqttInit2( &cnn_mqtt_on_message );
	mqttDoIt2();

	keyBindDoIt();
	
	//mqttInit();
	//mqttDoIt();
	printf("c cmachine2 -- 3 CPPMACHINE2 ... END\n");


	printf("c cmachine2 CPPMACHINE2 ... DONE\n");
	printf("cnn_Version	[%s]\n", cnn_Version );
	printf("cmachine2 ver	[%s]\n", CMACHINEVER );
	return 0;
}
#endif
