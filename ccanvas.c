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
#include <stdbool.h>


#ifdef CCANVASTEST
#include "configKeys.h"
//#include "config.h"
#include "cargs.h"
#include "cmdh.h"
#include "timeh.h"
#include "fileh.h"

#include "ccNode.h"
#include "ccanvas.h"
struct ccNode ccNs[10];

#else

//#include "config.h"

#endif



#include <unistd.h>
#include <pthread.h>
#include <time.h>


int ccNsCount = 0;

//int col = 70;
//int row = 10;
//bool asBar = false;
//int chFill = '.';
extern int col;
extern int row;
extern bool asBar;
extern int chFill;

//extern struct keyBinds[];


int CC_NODE_MARGIN = 2;
int ch = '\n';
int chNo = 0;
char line[512] = "-";

char *ccFB;
int ccFBc = 0;

int SMWork = 1;
int SMLoop = 0;


#ifdef CCANVASTEST
//
// for node if not defined 
//
int *fUpdateDef( struct ccNode *cN, int frameNo ){
	
	if( asBar == false )
		printf("fUpdateDef ... fNo[%i] of [ %s ]\n", frameNo, cN->name );
	return 0;
}



// Keys Root
//
//struct keyBind {
//	int parentId;
//	char ch[51];
//	int doWhat;
//	char parser[512];
//	char args[512];
//};
//struct keyBind keyBinds[] = {
//	{ 0, "W",	0,/*"cmdh"*/	"ip's:\n%s",		"ip a | grep 'inet ' | awk '{print $2}'" },
//	{ 0, "w",	0,/*"cmdh"*/	"whoami:[ %s ]",	"whoami" },
//	{ 0, "f",	0,/*"cmdh"*/ 	"%s",	"free -h" },
//	{-1}
//};



//
// widTic	for node 
//
int widgetTickC=0;
int *widgetTick(  struct ccNode *cN, int frameNo ){
	widgetTickC++;
	//printf(" widget tick ! %i\n", widgetTickC );
	snprintf( cN->text, 50, "widTok!(%i)", widgetTickC);
}


// 
// dogBatteryCounter dog() loop() ....
//
int dogBatteryCounter=0;
void *dogBatteryLooper( void *vargp ){
	sleep( 1 );
	char isDog[50];
	while( SMWork == 1 ){
		snprintf( isDog, 50, " | [B %s%%]", file_read_to_chars("/sys/class/power_supply/BAT0/capacity") );

		cc_printf( col-10 - 21, 0, isDog );
		ccRender();
		sleep( 11 );
	}
	printf("@* ... dogBatteryLooper DONE\n" );
}


// 
// dogTimeCounter dog() loop() ....
//
int dogTimeCounter=0;
void *dogTimeLooper( void *vargp ){
	sleep( 1 );
	char isDog[50];
	while( SMWork == 1 ){
		snprintf( isDog, 50, " | [%s]", time_now_tt() );
		cc_printf( col-21, 0, isDog );
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
	char isDog[50];
	while( SMWork == 1 ){
		//printf("@* loop\n")
		//widgetTickC
		snprintf( isDog, 50, " dog(%i) loop(%i) ", dogCounter++, SMLoop );
		//printf("%s ---\n", isDog);
		cc_printf( 1, row-3, isDog );
		ccRender();
		sleep( 5 );
	}
	printf("@* ... dogLooper DONE\n" );
}

// 
// dogs a.k.a. children processis / timers
//
pthread_t tdogBatteryLoop;
pthread_t tdogTimeLoop;
pthread_t tdogLoop;
void dogsStart(){
//	pthread_create( &tdogBatteryLoop, NULL, dogBatteryLooper, NULL );
	pthread_create( &tdogTimeLoop, NULL, dogTimeLooper, NULL );
	pthread_create( &tdogLoop, NULL, dogLooper, NULL );
}
void dogsStop(){

}
#endif


// ----------------------------------------------
char *cc_getPx( int x, int y ){
	return &ccFB[ y*col + x ];
}
char *cc_getPx_byPointer( char *pts, int x, int y, int icol){
	return &pts[ y*icol + x ];

	//char tr = pts[ y*icol + x ];
	//printf("by pointer got [%c]\n", tr);
	//return tr;
}

int ccInit_FB_byPointer( char **pts, int dcol, int drow ){
	ccFBc = dcol*drow;
	*pts = (char *)malloc( (ccFBc+1) * sizeof( char ) );
	if( *pts == NULL ) 
		printf("EE ccInit error size %i x %i\n", dcol, drow);

#ifdef CMTDEB 
	if( asBar == false )
		printf("#* .. ccFB size [ %i ] for [ %i x %i ] terminal \n", ccFBc, dcol, drow );
#endif

	memset( *pts, 'x', ccFBc );
	(*pts)[ ccFBc ] = 0;
#ifdef CMTDEB 
	printf("[DEB ccInit FB byP] after init len(%zu)\n", strlen( *pts ) );
#endif
}
int ccInit_FB(){
	ccInit_FB_byPointer( &ccFB, col, row );
}



int ccFree_FB(){
	free( ccFB );
}


#ifdef CCANVASTEST
int ccInit(){

	ccInit_FB();

	struct ccNode cPwd = { 1, {0, row-2 }, {0, 0 },  
		{ 255,0,0,255 }, { 255,0,200,255 }, 
		"Entry0","Full text of entry 0", "widgetTick", false, " ", 0 };
	//printf("* at adding cPwd and name [ %s ] \n",cPwd.name);
	ccNs[ ccNsCount++ ] = cPwd;
	
	struct ccNode cRenderC = { 2, {0, 0 }, {0, 0 }, 
		{ 255,25,255,255 },  { 255,0,200,255 }, 
		"ERenderC","1234567890abcdefgh123456790",  "fUpdateD", false, " ", 1 };
	ccNs[ ccNsCount++ ] = cRenderC;

	struct ccNode cLastCmd = { 2, {0, 1 }, {0, 0 },
		{ 255,255,55,255 },  { 255,20,100,255 }, 
		"lastCmd","12345678901234567890aoeuidhtn123456790",  "fUpdateLastCmd", false, " ", 1 };
	ccNs[ ccNsCount++ ] = cLastCmd;

	return ccNsCount;
}


int ccUpdate(){
	if( asBar == false )
		printf("#* ... ccUpdate \n");
	
	for(int w=0; w<ccNsCount; w++ ){

	if( strcmp( ccNs[w].fUpdate, "fUpdateLastCmd" ) == 0 ){
		snprintf( ccNs[w].text, 50, "Last cmd[%s]", line );

	//	}else if( strcmp( ccNs[w].fUpdate, "widgetTick" ) == 0 ){
	//		widgetTick( &ccNs[w], 0 );
	//	
	//	}else if( strcmp( ccNs[w].fUpdate, "fUpdateD" ) == 0 ){
	//		fUpdateDef( &ccNs[ w ], 0 );
	//	
		}
	}
}
#endif

// to clear FB
int cc_clear_byPointer( char **pts, char chf, int dcol, int drow ){
	char *tmpc;
	int cSize = drow*dcol;
	if( asBar == false )
		printf( "[DEB cc_clear by pointer] cSize:[%d] as strlen(%d)\n", cSize, strlen( *pts ) );
	for( int y=0; y<drow; y++ ){
		for(int x=0; x<=dcol; x++){
			//resBuf = cc_getPx_byPointer( pts, x, y );					     //tmpc = resBuf[0]; 
			tmpc = cc_getPx_byPointer( (char *)(*pts), x, y, dcol  );
			if( x == (dcol-1) && drow > 0)
				*tmpc='\n';
			else
				*tmpc=chf;
				//snprintf( tmpc, 1, "%s", chf );

		}
	}
	(*pts)[ cSize - 1 ] = 0;
	return 0;
}
int cc_clear( char cBlank ){
	return cc_clear_byPointer( &ccFB, cBlank, col, row );
}
// 
int cc_printf( int x, int y, char *msg ){
	int i,ic,iOffset = 0, yColXI;
	for( i=0,ic=strlen(msg); i<ic; i++){
		yColXI = y*col + x + i;
		if( ccFB[ yColXI + iOffset ] == '\n' ){
			iOffset++;
		}
		
		if( (  yColXI + iOffset ) > ccFBc-2 ){
			ccFB[ ccFBc-1 ] = 0;
			return ccFBc;
		}
		
		if( msg[i] == '\n' ){
			y++;
			iOffset = -i - 1;
		}else {
			ccFB[ yColXI + iOffset ] = msg[ i ];
		}
	}
	return i+iOffset-1;
}

int ccDraw(){
	int cur = 0;
	int wLen = 0;
	int c;
	for(int w=0; w<ccNsCount; w++ ){
#ifdef CCANVASTEST
		wLen = strlen( ccNs[w].text );
		if( asBar == false )
			printf( "ccDraw cur[%i] node[ %s ](%i)\n"
				"\t-> %s() pos:[%ix%i] ", 
				cur, ccNs[w].name, wLen, ccNs[w].fUpdate, ccNs[w].pos[0], ccNs[w].pos[1]			
				);


		// have colors ? // font only 
		if( asBar == false && ccNs[w].fbColor[0] != 0 && ccNs[w].tRenderDone == false ){
			//\e[41m"$battPerc'%'"\e[0m
			//48 is backgroung 38 font foreground
			snprintf( ccNs[w].tRender, 1024, "\e[38;2;%i;%i;%im%s\e[0m", 
				ccNs[w].fbColor[0], ccNs[w].fbColor[1], ccNs[w].fbColor[2],
				ccNs[w].text
				);
			printf("tRander .... \n\t(%s)\n", ccNs[w].tRender);
			ccNs[w].tRenderDone = true;

		}

		// by pos in ccNode
		if(  ccNs[w].pos[0] != 0 ||  ccNs[w].pos[1] != 0 ){
			cc_printf( ccNs[w].pos[0], ccNs[w].pos[1], ccNs[w].text );
			
			//printf("\e[%i;%iH%s\n", ccNs[w].pos[1], ccNs[w].pos[0], ccNs[w].tRender);
			//printf(" ... position()\n");

		// by currsor current	
		} else {
			cur+= cc_printf( cur, 0, ccNs[w].text );
			//printf(" ... cursor (%i)\n", cur);
		}

#endif
//		for( c=0; c<wLen ;c++ ){
//
//			ccFB[ cur++ ] = ccNs[w].text[ c ];
//			if( ((cur)%col) == 0 ){
//				ccFB[ cur++ ] = '\n';
//			} 
//			if( cur >= ccFBc ) return 0;
//		}
		//cur+= CC_NODE_MARGIN;
	}
	return 0;
}

int ccRenderCount=0;
void ccRender(){
	/*
	printf( "\n\nccRender  %i x %i ................\n\e[38;2;255;0;0m%s\e[0m................ccRender DONE\n", 
		col,row,
		ccFB 
		);
	*/
	if( asBar == true ){
		ccFB[ strcspn( ccFB, "\n") ] = '\0';
		printf(",[\n");
		printf(" {\"name\":\"canvA\",\"full_text\":\"%s\"}", ccFB );
		printf(",{\"name\":\"ccRenderC\",\"full_text\":\"%i\",\"color\":\"#ff%i%iff\"}", ccRenderCount, ( ccRenderCount % 9 ),  ( ccRenderCount % 9 ));
		printf("\n]\n");
	}else{
		for( int c=0; c< col; c++ )
			printf("-");
		printf("\n%s\n", ccFB );
	}

	ccRenderCount++;
}

void ccRender_byId( int cId ){
	

}

char tmsg[51200];
// mem res 121252 	virt 1560
// 	   1316		virt 1368
// 	   1241		virt 1576
// 	   1935		virt 1416
// 	   1943		     1576

// to get nice time up
// cat /proc/uptime | awk '{printf "%.2f min.\n", $1/60}'

#ifdef CCANVASTEST

int main( int argc, char *argv[] ){
	

	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;
		
	if( asBar == false )	
		printf( "ccanvas ... test argc(%i)\n", argc );
	
	ccInit();
	//ccRender();
	cc_clear( chFill );
	//ccDraw();
	//ccRender();
		
	//strcpy( ccNs[0].text, "123Full Text Of Entry 0 " );
	//ccDraw();
	//ccRender();
	dogsStart();

	int mLevel = 0;
	int kBin = 0;

	// main loop START
	while( SMWork == 1 ){
		SMLoop++;
		if( ch == '\n' ){

			if( line[0] == 'q' ){
				SMWork = 0;
				break;
			} else if( line[0] == 'c' && strlen( line ) == 2 ){
				chFill = (char)line[1];
				cc_clear( chFill );

			} else if( line[0] == 'N' ){
				snprintf( tmsg, 512, "net(N):\n%s", cmd_to_chars("ip a | grep inet | awk '{print $2}'") );
				cc_printf( 1, 3 , tmsg );

			} else if( line[0] == 'T' ){
				snprintf( tmsg, 512, "cmd(T):[%s]", cmd_to_chars("date") );
				cc_printf( 2, 3 , tmsg );

			} else if( line[0] == 'p' ){
				cc_printf( 2, 3 , "5x11 land" );

			} else if( line[0] == 'c' ){
				cc_clear( chFill );

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
	


			for( kBin=0; true; kBin++ ){
				if( keyBinds[kBin].parentId == -1 ) break;

				if( asBar == false ) 
					printf( "kBin cmp [%s] = [%s]\n", keyBinds[kBin].ch, line );

				if( keyBinds[kBin].parentId == mLevel && 
					strcmp( line, keyBinds[kBin].ch ) == 0 ){
					printf("OK\n");

					if( keyBinds[kBin].doWhat == 0 ){ // cmd
						snprintf( tmsg, 512, keyBinds[kBin].parser, cmd_to_chars( keyBinds[kBin].args  ) );
						cc_printf( 2, 3 , tmsg );


					} else if( keyBinds[kBin].doWhat == 1 ){ // mqtt push / publish
						// TODO mqtt publish

					} else {
						printf(" | . . . keyBind exec EE NOT IMPlemented yet doWhat [%i]\n", keyBinds[kBin].doWhat);	
					}
					break;
				}

			}


			//cc_clear( chFill );
			ccUpdate();
			ccDraw();
			ccRender();

			snprintf( tmsg, 512, 
				"[%i]To quit press [q] fill[%c] size[ %ix%i ]", 
				mLevel, chFill, col, row );
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

#endif


