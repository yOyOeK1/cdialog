
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

extern int col;
extern int row;
extern bool asBar;
extern int chFill;

#ifndef CPPTEST


#else

#include "cargs.h"
#include "config.h"

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
			printf("CM_divs id:%i, \n", id);
			if( msgId != -1 ){
				struct cnn_Msg *msg = &cnMs[ cm_getMsgIndexById( msgId ) ];   
				float fin = atof( msg->payload );
				fin/= cnnDivs[ i ].divBy;
				printf("div %s by %f res [%f]\n",  msg->payload, cnnDivs[ i ].divBy, fin );
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
			printf("CM_adds id:%i, \n", id);
			if( msgId != -1 ){
				struct cnn_Msg *msg = &cnMs[ cm_getMsgIndexById( msgId ) ];   
				float fin = atof( msg->payload );
				fin+= cnnAdds[ i ].add;
				printf("add %f to %s res [%f]\n", cnnAdds[ i ].add, msg->payload, fin );
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
			printf("CM_PRINTF id:%i, \n", id);
			if( msgId != -1 ){
				struct cnn_Msg msg = cnMs[ cm_getMsgIndexById( msgId ) ];
				if( cnnPrintfs[ i ].doTopic ){
					printf("* Topic: ... %s\n", msg.topic );
				}
				printf( cnnPrintfs[ i ].printAs, msg.payload );
			}
			break;
		}
	}	
}

void cmi_dolevel( int level ){
	level*= 4;
	level+=2;
	printf("\n");
	for( int l=0; l<4; l++ ){
		printf("-");
	}
	printf("|__ ");
}


void cm_doClick( int level, int msgId, int srcType, int srcId ){
	if( level == 0 )
		printf("\n ----- \n");
	printf("\nlevel(%i) ", level );
	if( msgId != -1 ) printf("#");
	else printf("0");

	int doClick = false;
	for( int ni=0; true; ni++ ){
		if( cnnNudles[ ni ].id == -1 ) break;
		if( cnnNudles[ ni ].srcType == srcType &&
			cnnNudles[ ni ].srcId == srcId ){

			printf("GO -> ");
			cmi_dolevel( level );
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
			}

		}
	}

}
#ifdef CPPTEST
int main( int argc, char *argv[] ){
	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;

	printf("c cmachine2 CPPTEST ... START size [ %ix%i ]@%s\n", col, row, machineName );

	for( int p=0; true; p++ ){
		if( machNs[ p ].id == -1 ) break;
		printf("\n\n*[%i] id[%i] ... onStart[%i] every[%ims] \n\t - %s\n", p, 
			machNs[ p ].id, machNs[ p ].onStart, machNs[ p ].everyMs, machNs[ p ].name 
			);
		if( machNs[ p ].onStart )
			cmachine_start_byNode( machNs[ p ] );
	
	}

	printf("c cmachine2 -- 2 CPPTEST ... DONE\n");
	for( int n=0; true; n++ ){
		if( cnnAtStarts[ n ].id == -1 ) break;
		printf("\n --- nudle id[%i] ", cnnAtStarts[ n ].id );
		if( cnnAtStarts[ n ].onStart ){ 
			cm_doClick( 0, cnnAtStarts[ n ].msgId, CNNATSTART, cnnAtStarts[ n ].id );

		}
		printf("\n");
	}
	printf("c cmachine2 -- 2 CPPTEST ... END\n");

	printf("c cmachine2 CPPTEST ... DONE\n");
	return 0;
}
#endif
