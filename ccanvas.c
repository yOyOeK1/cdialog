//
//	as i3bar
//     status_command /home/yoyo/Apps/cdialog/ccanvash.bin -row=1 -col=150
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timeh.h"

#include "ccanvas.h"
#include "ccNode.h"

#include <unistd.h>
#include <pthread.h>
#include <time.h>


struct ccNode ccNs[10];
int ccNsCount = 0;

int col = 50;
int row = 4;
int CC_NODE_MARGIN = 2;
int ch = '\n';
int chFill = '.';
int chNo = 0;
char line[512] = "-";
bool asBar = false;

char *ccFB;
int ccFBc = 0;

int SMWork = 1;
int SMLoop = 0;




//
// widTic	for node 
//
int widgetTickC=0;
int *widgetTick(  struct ccNode *cN, int frameNo ){
	widgetTickC++;
	printf(" widget tick ! %i\n", widgetTickC );
	snprintf( cN->text, 50, "ok!(%i)", widgetTickC);
}

//
// for node if not defined 
//
int *fUpdateDef( struct ccNode *cN, int frameNo ){
	
	printf("fUpdateDef ... fNo[%i] of [ %s ]\n", frameNo, cN->name );
	return 0;
}

// 
// dogTimeCounter dog() loop() ....
//
int dogTimeCounter=0;
void *dogTimeLooper( void *vargp ){
	sleep( 1 );
	while( SMWork == 1 ){
		char isDog[50];
		snprintf( isDog, 50, " | 󱑌 [%s] ", time_now_tt() );
		cc_printf( col-23, 0, isDog );
		ccRender();
		sleep( 10 );
	}
	printf("@* ... dogTimeLooper DONE\n" );
}



// 
// dogCounter dog() loop() ....
//
int dogCounter=0;
void *dogLooper( void *vargp ){
	sleep( 1 );
	while( SMWork == 1 ){
		//printf("@* loop\n")
		//widgetTickC
		char isDog[50];
		snprintf( isDog, 50, " dog(%i) loop(%i)", dogCounter++, SMLoop );
		//printf("%s ---\n", isDog);
		cc_printf( col-40, row-1, isDog );
		ccRender();
		sleep( 2 );
	}
	printf("@* ... dogLooper DONE\n" );
}



int ccInit_FB(){
	ccFBc = col*row + 1;
	ccFB = malloc( ccFBc * sizeof( char ) );
	printf("#* .. ccFB size [ %i ] for [ %i x %i ] terminal size\n", ccFBc, col, row );
}

int ccFree_FB(){
	free( ccFB );
}

int ccInit(){

	ccInit_FB();

	struct ccNode cPwd = { 1, {0, 0 }, {0, 0 },  { 255,0,0,255 }, { 255,0,200,255 }, "Entry0","Full text of entry 0", "widgetTick", 0 };
	//printf("* at adding cPwd and name [ %s ] \n",cPwd.name);
	ccNs[ ccNsCount++ ] = cPwd;
	
	struct ccNode cRenderC = { 2, {0, 0 }, {0, 0 }, { 255,255,255,255 },  { 255,0,200,255 }, "ERenderC","123456790",  "fUpdateD", 1 };
	ccNs[ ccNsCount++ ] = cRenderC;

	struct ccNode cLastCmd = { 2, {0, -1 }, {0, 0 }, { 255,255,255,255 },  { 255,20,100,255 }, "lastCmd","123456790",  "fUpdateLastCmd", 1 };
	ccNs[ ccNsCount++ ] = cLastCmd;

	return ccNsCount;
}

int ccUpdate(){
	printf("#* ... ccUpdate \n");
	for(int w=0; w<ccNsCount; w++ ){
		if( strcmp( ccNs[w].fUpdate, "fUpdateLastCmd" ) == 0 ){
			snprintf( ccNs[w].text, 50, "Last cmd[%s]", line );
		}else if( strcmp( ccNs[w].fUpdate, "widgetTick" ) == 0 ){
			widgetTick( &ccNs[w], 0 );
		}else{
			fUpdateDef( &ccNs[ w ], 0 );
		}
	}

}

int cc_printf( int x, int y, char *msg ){
	for( int i=0,ic=strlen(msg); i<ic; i++){
		ccFB[ y*col + x + i ] = msg[ i ];

	}
	return 0;
}

int ccDraw(){
	int cur = 0;
	int wLen = 0;
	int c;
	for(int w=0; w<ccNsCount; w++ ){
		wLen = strlen( ccNs[w].text );
		printf( "w* cur[%i] [ %s ] len(%i)\n", cur, ccNs[w].name, wLen  );

		for( c=0; c<wLen ;c++ ){

			ccFB[ cur++ ] = ccNs[w].text[ c ];
			if( ((cur+1)%col) == 0 ){
				ccFB[ cur ] = '\n';
			} 
			if( cur >= ccFBc ) return 0;
		}
		//cur+= CC_NODE_MARGIN;
	}
	return 0;
}

char *ccGetPX( int x, int y ){
	return &ccFB[ y*col + x ];
}

// to clear FB
void ccClear( char cBlank ){
	char *tmpc;
	for( int y=0; y<row; y++ ){
		for(int x=0; x<col; x++){
			tmpc = ccGetPX( x, y );			
			if( x == (col-1) && row > 1)
				*tmpc='\n';
			else
				*tmpc = cBlank;

		}
	}

}

void ccRender(){
	/*
	printf( "\n\nccRender  %i x %i ................\n\e[38;2;255;0;0m%s\e[0m................ccRender DONE\n", 
		col,row,
		ccFB 
		);
	*/
	if( asBar == true ){
		ccFB[ strcspn( ccFB, "\n") ] = '\0';
		printf(",[{ \"full_text\": \"%i\", \"full_text\":\"%s\"}]\n", 1,ccFB );
	}else{
		printf("%s\n", ccFB );
	}
}




int main( int argc, char *argv[] ){
	

	if( argc > 1 ){
		for( int a=0; a<argc ; a++ ){
			if( strncmp( argv[ a ], "-row=", 5 ) == 0 ){
				printf("#* ... --row=\n");
				sscanf( argv[ a ], "-row=%d", &row );
			} else if( strncmp( argv[ a ], "-asBar", 6 ) == 0 ){
				printf("{\"version\": 1, \"click_events\":true }[[]\n");
				asBar = true;

			} else if( strncmp( argv[ a ], "-col=", 5 ) == 0 ){
				printf("#* ... --col=\n");
				sscanf( argv[ a ], "-col=%d", &col );
			} else if( strncmp( argv[ a ], "-chFill=", 8) == 0 ){
				chFill = argv[ a ][8];
				printf("#* ... --chFill= (%c)\n",chFill );
				//sscanf( argv[ a ], "-chFill=%c", chFill );
			} 

		}
	}
	

	printf( "ccanvas ... test argc(%i)\n", argc );

	ccInit();
	//ccRender();
	ccClear( chFill );
	//ccDraw();
	//ccRender();
		
	//strcpy( ccNs[0].text, "123Full Text Of Entry 0 " );
	//ccDraw();
	//ccRender();


	pthread_t tdogTimeLoop;
	pthread_create( &tdogTimeLoop, NULL, dogTimeLooper, NULL );

	pthread_t tdogLoop;
	pthread_create( &tdogLoop, NULL, dogLooper, NULL );



	// main loop START
	while( SMWork == 1 ){
		SMLoop++;
		if( ch == '\n' ){

		if( line[0] == 'q' ){
			SMWork = 0;
			break;
		} else if( line[0] == 'c' && strlen( line ) == 2 ){
			chFill = (char)line[1];
			ccClear( chFill );

		} else if( line[0] == 'p' ){
			cc_printf( 5, 2, "5x2 land" );
		} else if( line[0] == 'c' ){
			ccClear( chFill );

		} else if( line[0] == 's' && line[1] == 'r' ){
			sscanf( line, "sr%d", &row );
			printf("#* ... [%s] set new row(%i)\n", line, row );
			ccFree_FB();
			ccInit_FB();
			

		} else if( line[0] == 's' && line[1] == 'c' ){
			sscanf( line, "sc%d", &col );
			printf("#* ... [%s] set new col(%i)\n", line, col);
			ccFree_FB();
			ccInit_FB();
		}
	

			line[ chNo ] = 0;
			chNo = 0;
		
			//ccClear( chFill );
			ccUpdate();
			ccDraw();
			ccRender();

			//printf( "To quit press [q] fill[%c]\n", chFill );
			char tmsg[51200];
			snprintf( tmsg, 512, "To quit press [q] fill[%c] size[ %ix%i ]",
				chFill, col, row );
			cc_printf( 0, row-1, tmsg);
			//scanf( "%c", &ch );
			//scanf("%s", line );
			

		}else{
			line[ chNo++ ] = ch;
		}

		ch = getchar();
		
		printf("#* ... pressd [%c]\n", ch);

	}	
	// main loop END


	printf( "ccanvas ... test ccCount(%i) DONE\n"
		" .. ccNs[0].name [ %s ]\n",
		ccNsCount,
		ccNs[0].name
		);

	return 0;
}
