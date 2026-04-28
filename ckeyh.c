


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>


#include "cnn_config_data.h"

#include "cmachine2.h"

extern int col;
extern int row;
extern bool asBar;
extern int chFill;

char keyIn[512];
char keyCh;
int keyNo;
bool keyCmdOk;
//char keyLine[512] = "-";

char *key_getCurrentMode_name(){

	for( int p=0; true; p++ ){
		if( cnn_KeyModes[ p ].id == -1 ) break;
		if( cnn_KeyModes[ p ].id == cnn_KeyModeNow )
			return cnn_KeyModes[ p ].name;
	}
	return "NaN";
}

int key_chk_KeyBinds(  ){
	if( asBar == false ) 
		printf( " * keyBin parentId[%i] ", cnn_KeyModeNow );

	for( int kBin=0; true; kBin++ ){
		if( cnn_KeyBinds[kBin].id == -1 ) break;
		if( cnn_KeyBinds[kBin].parentId == cnn_KeyModeNow ){
			if( asBar == false ) 
				printf( "[%s] ", cnn_KeyBinds[kBin].keys );
			if( strcmp( keyIn, cnn_KeyBinds[kBin].keys ) == 0 ){
				cmiNodeName("CNNKEYBIND", cnn_KeyBinds[kBin].id, cnn_KeyBinds[kBin].keys );
				printf(" | OK keyBind id[%i]\n | ... [%s]\n", cnn_KeyBinds[kBin].id, cnn_KeyBinds[kBin].parser );

				//cm_doClick( 0, 0/*cnn_KeyBinds[kBin].msgId*/, CNNKEYBIND, cnn_KeyBinds[kBin].id );
				cnn_Msg msgT;
				cm_doClick( 0, cnn_KeyBinds[kBin].msgId, msgT, CNNKEYBIND, cnn_KeyBinds[kBin].id );


				/*if( cnn_KeyBinds[kBin].doWhat == 0 ){ // cmd
					snprintf( tmsg, 512, cnn_KeyBinds[kBin].parser, cmd_to_chars( cnn_KeyBinds[kBin].args  ) );
					cc_printf( 2, 3 , tmsg );


				} else */if( cnn_KeyBinds[kBin].workType == CNKEY_MQTTPUSH ){ // mqtt push / publish
					// TODO mqtt publish

				} else {
					printf("EE NOT IMPlemented yet workType [%i]\n", cnn_KeyBinds[kBin].workType );	
				}
				break;
			}
		}
	}
	printf("\n");
	return -1;
}

void cnn_keyBind_on_OK( int kbId ){
	//
	//for( int n=0; true; n++ ){
	//	if( cnnNudles[ n ].id == -1 ) break;
        //
	//	if( cnnNudles[ n ].srcType == CNNKEYBIND &&
	//		cnnNudles[ n ].srcId == cnn_KeyBinds[ s ].id ){
	//		printf(" */ cmd got nudle .... n[%i] type[%i] id[%i] msgId[%i]\n", n, cnnNudles[ n ].targetType, cnnNudles[ n ].targetId, cnnCmds[ s ].msgId );
	//		int msgIndex = cm_getMsgIndexById( cnnCmds[ s ].msgId  );
	//		strcpy( cnMs[ msgIndex  ].topic, message->topic );
	//		strcpy( cnMs[ msgIndex  ].payload, message->payload );
	//		//cm_doClick( 0, 1, cnnNudles[ n ].targetType, cnnNudles[ n ].targetId );
	//		cmiNodeName("CNNCMD", cnnCmds[ s ].id, cnnCmds[ s ].name ); 
	//		cm_doClick( 0, cnnCmds[ s ].msgId, cnnNudles[ n ].srcType, cnnNudles[ n ].srcId );
        //
	//	}
        //
        //
	//}
	printf(" | \n \\ ___ ### CNNCMD ... END\n");
}

int keyBindIdLast;

int keyBindDoIt(){
	keyNo = 0;
	keyCmdOk = false;
	keyBindIdLast = -1;
	printf("[q] key to exit ...\n");
	while( true ){
		keyCh = getchar();

		if ( keyCh == '\n' ){
			keyCmdOk = true;
			keyIn[ keyNo ] = 0;
			printf("[q] key to exit ...\n");
		} else {
			keyIn[ keyNo++ ] = keyCh;
		}

		if( keyCmdOk ){
			printf("CMD@[%i:%s] [%s] (%i)\n", cnn_KeyModeNow, key_getCurrentMode_name(), keyIn, keyNo );
			
			keyBindIdLast = key_chk_KeyBinds();
			if( keyNo == 1 && keyIn[0] == 'q' ){
				printf("Exit by q\n");
				break;

			} else if( keyBindIdLast != -1 ) {
				printf("---- KEYBINDS .... END\n");
			
			} else if( keyNo == 2 && keyIn[0] == 'm' ){
				sscanf( keyIn, "m%li",  &cnn_KeyModeNow );
				printf("Mode switch ...[%i:%s]\n", cnn_KeyModeNow, key_getCurrentMode_name() );
			}  	

			keyCmdOk = false;
			keyNo = 0;
			keyBindIdLast = -1;

		}
	}

	return -1;
}

