


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>


#include "cnn_config_data.h"

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

bool key_chk_KeyBinds(  ){
	if( asBar == false ) 
		printf( " k ... keyBin " );

	for( int kBin=0; true; kBin++ ){
		if( cnn_KeyBinds[kBin].id == -1 ) break;

		if( asBar == false ) 
			printf( " [%s] ", cnn_KeyBinds[kBin].ch );

		if( cnn_KeyBinds[kBin].parentId == cnn_KeyModeNow && 
			strcmp( keyIn, cnn_KeyBinds[kBin].ch ) == 0 ){
			printf("\n k OK keyBind id[%i]\n k ... [%s]\n", cnn_KeyBinds[kBin].id, cnn_KeyBinds[kBin].parser );

			/*if( cnn_KeyBinds[kBin].doWhat == 0 ){ // cmd
				snprintf( tmsg, 512, cnn_KeyBinds[kBin].parser, cmd_to_chars( cnn_KeyBinds[kBin].args  ) );
				cc_printf( 2, 3 , tmsg );


			} else */if( cnn_KeyBinds[kBin].doWhat == 1 ){ // mqtt push / publish
				// TODO mqtt publish

			} else {
				printf("EE NOT IMPlemented yet doWhat [%i]\n", cnn_KeyBinds[kBin].doWhat);	
			}
			break;
		}
	}
	printf("\n");
	return false;
}




int keyBindDoIt(){
	keyNo = 0;
	keyCmdOk = false;
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
			
			if( keyNo == 1 && keyIn[0] == 'q' ){
				printf("Exit by q\n");
				break;

			} else if( key_chk_KeyBinds() == true ) {
				printf("---- KEYBINDS .... END\n");
			
			} else if( keyNo == 2 && keyIn[0] == 'm' ){
				sscanf( keyIn, "m%li",  &cnn_KeyModeNow );
				printf("Mode switch ...[%i:%s]\n", cnn_KeyModeNow, key_getCurrentMode_name() );
			}  	

			keyCmdOk = false;
			keyNo = 0;

		}
	}

return 1;
}

