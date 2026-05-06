


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>


#include "cnn_config_data.h"

#include "cmTools.h"
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





#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios original_termios;

void key_mouseKey_disable(){
    // Disable mouse tracking and restore original termios
    printf("\x1b[?1006l\x1b[?1003l"); 
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

void key_mouseKey_modeMouse( int modeNo ){
	if( modeNo == 0  ){ // mouse pc
		printf("\x1b[?1003h\x1b[?1006h");
	} else if ( modeNo == 1 ){ // termux
		printf("\033[?1003h\033[?1006h");   
	}
	fflush(stdout);
}

int key_mouseKey_enable(){
    // 1. Save original settings and register reset on exit
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit( key_mouseKey_disable );

    // 2. Enter raw mode
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);


    key_mouseKey_modeMouse( 1 );

    char buf[32];
    printf("Capturing... Press 'q' to quit.\n");

    while (1) {
        int n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            if (buf[0] == 'q') break;
	
            // Mouse events start with \x1b[<
            if (n > 3 && buf[0] == '\x1b' && buf[1] == '[' && buf[2] == '<') {
                printf("Mouse event: %s\r\n", buf + 3);
	    }else if ( n>1 ){
		    printf("Special key n(%i)	",n);
		    for( int c=0; c<n; c++ )
			    printf(" [%i] ", buf[c]);
		    printf("\n");
            } else {
                printf("Key pressed n(%i)[%c]	int[%i]: %d\r\n", n, buf[0], buf[0], buf[0]);
            }
        }
    }

    return 0;
}












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
		cmtDeb( "keyBind", " * keyBin parentId[%i] ", cnn_KeyModeNow );

	for( int kBin=0; true; kBin++ ){
		if( cnn_KeyBinds[kBin].id == -1 ) break;
		if( cnn_KeyBinds[kBin].parentId == cnn_KeyModeNow ){
			if( asBar == false ) 
				printf( "[%s] ", cnn_KeyBinds[kBin].keys );
			if( strcmp( keyIn, cnn_KeyBinds[kBin].keys ) == 0 ){
				cmt_NodeName("CNNKEYBIND", cnn_KeyBinds[kBin].id, cnn_KeyBinds[kBin].keys );
				cmtDeb( "keyBind"," | OK keyBind id[%i]\n | ... [%s]\n", cnn_KeyBinds[kBin].id, cnn_KeyBinds[kBin].parser );

				//cm_doClick( 0, 0/*cnn_KeyBinds[kBin].msgId*/, CNNKEYBIND, cnn_KeyBinds[kBin].id );
				cnn_Msg msgT;
				cm_doClick( 0, cnn_KeyBinds[kBin].msgId, msgT, CNNKEYBIND, cnn_KeyBinds[kBin].id );

				cmtDeb( "keyBind"," | \n \\ ___ ### CNNKEYBIND... END\n");

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
	//cmtDeb( "keyBind","\n");
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
	//		cmt_NodeName("CNNCMD", cnnCmds[ s ].id, cnnCmds[ s ].name ); 
	//		cm_doClick( 0, cnnCmds[ s ].msgId, cnnNudles[ n ].srcType, cnnNudles[ n ].srcId );
        //
	//	}
        //
        //
	//}
	printf(" | \n \\ ___ ### CNNCMD ... END\n");
}

void keyPrintf_helpForCurrentMode(){
	printf("--------------------------------\n"
		"# help / legend \n\n"
		);
	int p,pNo;
	
	printf("## master keys\n"
		"	[mN]	- switch modes N is mode No\n"
		"	[q]	- quit / exit\n"
		);
	printf("## key modes \n"
		" [@]	- is current\n");
	pNo = 1;
	for( p=0; true; p++ ){
		if( cnn_KeyModes[ p ].id == -1 ) break;
		printf(" %i.	%c[m%i] [%s]\n", pNo++,
			(cnn_KeyModes[ p ].id == cnn_KeyModeNow ? '@' : ' '),
			cnn_KeyModes[ p ].id, cnn_KeyModes[ p ].name );
	}
	printf("## key at this mode \n");

	pNo = 1;
	for( p=0; true; p++ ){
		if( cnn_KeyBinds[ p ].id == -1 ) break;

		if( cnn_KeyBinds[ p ].parentId == cnn_KeyModeNow ){
			printf(" %i.	 [%s]	- %s\n", pNo++, cnn_KeyBinds[ p ].keys, cnn_KeyBinds[ p ].parser );
		}
	}

	printf("\n----------------------------\n");
}

int keyBindIdLast;

int keyBindDoIt(){
	keyNo = 0;
	keyCmdOk = false;
	keyBindIdLast = -1;
	printf("[q] key to exit ... or [?] for help ...\n");
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

			} else if( keyNo == 1 && keyIn[0] == '?' ){
				keyPrintf_helpForCurrentMode();

			} else if( keyBindIdLast != -1 ) {
				printf("---- KEYBINDS .... END\n");
			
			} else if( keyNo == 2 && keyIn[0] == 'm' ){
				sscanf( keyIn, "m%i",  &cnn_KeyModeNow );
				printf("Mode switch ...[%i:%s]\n", cnn_KeyModeNow, key_getCurrentMode_name() );
			}  	

			keyCmdOk = false;
			keyNo = 0;
			keyBindIdLast = -1;

		}
	}

	return -1;
}

