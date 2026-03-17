#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct ccNode{
	int id;
	int pos[2];
	int size[2];
	char color[4];
	char name[512];
	char text[512];
	char fUpdate[128];
	int entryDate;

};

//
// widTic
//
int widgetTickC=0;
int *widgetTick(  struct ccNode *cN, int frameNo ){
	widgetTickC++;
	printf(" widget tick ! %i\n", widgetTickC );
	snprintf( cN->text, 50, "ok!(%i)", widgetTickC);
}

//

int *fUpdateDef( struct ccNode *cN, int frameNo ){
	
	printf("fUpdateDef ... fNo[%i] of [ %s ]\n", frameNo, cN->name );
	return 0;
}


struct ccNode ccNs[10];
int ccNsCount = 0;

int col = 20;
int row = 4;
char *ccFB;

int ccInit(){
	
	int tChar = col*row + 1;
	ccFB = malloc( tChar * sizeof( char ) );
	printf("#* .. ccFB size [ %i ] for [ %i x %i ] terminal size\n", tChar, col, row );


	struct ccNode cPwd = { 1, {0, 0 }, {0, 0 }, { 255,0,0,255 }, "Entry0","Full text of entry 0", "widgetTick", 0 };
	//printf("* at adding cPwd and name [ %s ] \n",cPwd.name);
	ccNs[ ccNsCount++ ] = cPwd;
	
	struct ccNode cRenderC = { 2, {0, 0 }, {0, 0 }, { 255,255,255,255 }, "ERenderC","123456790",  "fUpdateD", 1 };
	ccNs[ ccNsCount++ ] = cRenderC;

	struct ccNode cLastCmd = { 2, {0, -1 }, {0, 0 }, { 255,255,255,255 }, "lastCmd","123456790",  "fUpdateLastCmd", 1 };
	ccNs[ ccNsCount++ ] = cLastCmd;

	return ccNsCount;
}

int CC_NODE_MARGIN = 2;

char line[512] = "-";

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

int ccDraw(){
	int cur = 0;
	int wLen = 0;
	int c;

	for(int w=0; w<ccNsCount; w++ ){
		wLen = strlen( ccNs[w].text );
		printf( "w* cur[%i] [ %s ] len(%i)\n", cur, ccNs[w].name, wLen  );

		for( c=0; c<wLen ;c++ ){
			if( ((cur+1)%col) == 0 ){
				ccFB[ cur++ ] = '\n';
			} 
			ccFB[ cur++ ] = ccNs[w].text[ c ];
		}
		
		cur+= CC_NODE_MARGIN;
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
			if( x == (col-1) )
				*tmpc='\n';
			else
				*tmpc = cBlank;

		}
	}

}

void ccRender(){
	printf( "\n\nccRender ................\n%s................ccRender DONE\n", ccFB );
}


int SMWork = 1;
int ch;
int chNo = 0;

int main( int argc, char *argv[] ){
	
	printf( "ccanvas ... test\n" );

	ccInit();
	//ccRender();
	//ccClear('x');
	//ccDraw();
	//ccRender();
		
	//strcpy( ccNs[0].text, "123Full Text Of Entry 0 " );
	//ccDraw();
	//ccRender();


	// main loop START
	while( SMWork == 1 ){
		ccClear(' ');
		ccUpdate();
		ccDraw();
		ccRender();

		printf( "To quit press [q]\n" );
		//scanf( "%c", &ch );
		ch = getchar();
		if( ch == '\n' ){
			line[ chNo ] = 0;
			chNo = 0;
		}else{
			line[ chNo++ ] = ch;
		}

		printf("#* ... pressd [%c]\n", ch);

		if( ch == 'q' )
			SMWork = 0;
	
	}
	// main loop END


	printf( "ccanvas ... test ccCount(%i) DONE\n"
		" .. ccNs[0].name [ %s ]\n",
		ccNsCount,
		ccNs[0].name
		);

	return 0;
}
