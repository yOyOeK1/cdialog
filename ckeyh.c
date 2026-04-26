


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>


#include "cnn_config_data.h"


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

int keyBindDoIt(){
	keyNo = 0;
	keyCmdOk = false;
	while( true ){
		printf("[q] key to exit ...\n");
		keyCh = getchar();

		if ( keyCh == '\n' ){
			keyCmdOk = true;
			keyIn[ keyNo ] = 0;
		} else {
			keyIn[ keyNo++ ] = keyCh;
		}

		if( keyCmdOk ){
			printf("CMD@[%i:%s] [%s] (%i)\n", cnn_KeyModeNow, key_getCurrentMode_name(), keyIn, keyNo );
			
			if( keyNo == 1 && keyIn[0] == 'q' ){
				printf("Exit by q\n");
				break;
			}else if( keyNo == 2 && keyIn[0] == 'm' ){
				sscanf( keyIn, "m%li",  &cnn_KeyModeNow );
				printf("Mode switch ...[%i:%s]\n", cnn_KeyModeNow, key_getCurrentMode_name() );
			}  	

			keyCmdOk = false;
			keyNo = 0;

		}
	}

return 1;
}

