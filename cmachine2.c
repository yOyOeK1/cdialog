
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mosquitto.h>


#define CMACHINEVER "2026.0421"

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

			printf("\n |\n |--- nudle id[%i]\n |\n", cnnNudles[ ni ].id );
			if( cnnNudles[ ni ].targetType == CNNPRINTF ){
				cm_printf( cnnNudles[ ni ].targetId, msgId );
				doClick = true;

			}else if( cnnNudles[ ni ].targetType == CNNDIV ){
				cm_div( cnnNudles[ ni ].targetId, msgId );
				doClick = true;

			}else if( cnnNudles[ ni ].targetType == CNNADD ){
				cm_add( cnnNudles[ ni ].targetId, msgId );
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
		
			printf("cmachine2 mqtt msg ... index[%i] obj [%i] topic: [%s]\n", sIndex, message->mid, message->topic ); 

			for( int n=0; true; n++ ){
				if( cnnNudles[ n ].id == -1 ) break;

				if( cnnNudles[ n ].srcType == CNNMQTTSUB &&
					cnnNudles[ n ].srcId == cnn_MqttSubs[ s ].id ){
					printf("mqtt got nudle .... n[%i] type[%i] id[%i]\n", n, cnnNudles[ n ].targetType, cnnNudles[ n ].targetId );
					strcpy( cnMs[0].payload, message->payload );
					//cm_doClick( 0, 1, cnnNudles[ n ].targetType, cnnNudles[ n ].targetId );
					cm_doClick( 0, 1, cnnNudles[ n ].srcType, cnnNudles[ n ].srcId );

				}


			}
		} 
	}
	if( sIndex == -1 ){
		printf("cmachine2 mqtt msg ... topic: [%s]\n", message->topic ); 
	}


}	

#ifdef CPPMACHINE

char keyIn[512];
char keyCh;
int keyNo;
bool keyCmdOk;
char *key_getCurrentMode_name(){

	for( int p=0; true; p++ ){
		if( cnn_KeyModes[ p ].id == -1 ) break;
		if( cnn_KeyModes[ p ].id == cnn_KeyModeNow )
			return cnn_KeyModes[ p ].name;
	}
	return "NaN";
}


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

	keyNo = 0;
	keyCmdOk = false;
	while( true ){
		printf("Any key to exit ...\n");
		keyCh = getchar();
	

		if ( keyCh == '\n' ){
			keyCmdOk = true;
			keyIn[ keyNo ] = 0;
		} else {
			keyIn[ keyNo++ ] = keyCh;
		}


		printf("keys [%s]\n", keyIn );


		if( keyCmdOk ){
			printf("CMD@[%i:%s] [%s] (%i)\n", cnn_KeyModeNow, key_getCurrentMode_name(), keyIn, keyNo );
			
			if( keyNo == 1 && keyIn[0] == 'q' ){
				printf("Exit by q\n");
				break;
			}else if( keyNo == 2 && keyIn[0] == 'm' ){
				sscanf( keyIn, "m%li",  &cnn_KeyModeNow );
				printf("Mode switch ...\n");
			}  	

			keyCmdOk = false;
			keyNo = 0;

		}
	}
	
	//mqttInit();
	//mqttDoIt();
	printf("c cmachine2 -- 3 CPPMACHINE2 ... END\n");


	printf("c cmachine2 CPPMACHINE2 ... DONE\n");
	printf("cmachine2 ver[%s]\n", CMACHINEVER );
	return 0;
}
#endif
