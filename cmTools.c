
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "cnn_config_data.h"
#include "cmdh.h"


typedef struct{
	char blame[512];
	char line[512];
}cmtDeb_item;

#define CMTDEB_MAX 10
#define CMTDEB 1
extern bool cmtDeb_verbose;
int cmtDeb_No = 0;
cmtDeb_item cDEBS[ CMTDEB_MAX + 5];


void cmtDeb_dump(){
	printf("[DEB] --------------- START\n");
	for( int l=cmtDeb_No-1; l<CMTDEB_MAX; l++ ){
		printf("[DEB%03i][% 8s] \t%s\n", l,  cDEBS[ (l%CMTDEB_MAX) ].blame, cDEBS[ (l%CMTDEB_MAX) ].line );
	}
	printf("[DEB] --------------- END\n");
}

int cmtDeb( char *blame, const char *format, ... ){
#ifndef CMTDEB
	return 0;
#endif
	va_list args;
	va_start( args, format );
	int len = vsnprintf( NULL, 0, format, args );
	va_end( args );
	if( len < 0 ){
		printf("EE in cmtDeb 9879 in \n");
		return 1;
	}

	va_start( args, format );
	if( cmtDeb_verbose ){
		printf("[DEBUG] cmachine [%s]\n", blame );
		vprintf( format, args );
	}
	strcpy( cDEBS[ cmtDeb_No ].blame, blame ); 
	vsnprintf( cDEBS[ cmtDeb_No  ].line, 512, format, args );
	cDEBS[ cmtDeb_No ].line[511] = 0;
	va_end( args );

	cmtDeb_No++;
	if( cmtDeb_No > CMTDEB_MAX )
		cmtDeb_No = 0;

	//cmtDeb_dump();

	return 0;
}

void cmt_start_byNode( machNode mn ){
	cmtDeb("startByNode", "\t* start by id ... %i\n", mn.id );	

	if( mn.typeOf == 0 ){ // cmd
		mn.isRunning = true;
		strcpy( mn.result, cmd_to_chars( mn.cmd ) );
		cmtDeb( "startByNode", "\t* ... result [ %s ]\n", mn.result );

	}else{
		cmtDeb( "startByNode","\tEE type not implemented [%i]\n", mn.typeOf );
	}
}

void cmt_NodeName( char *type, int id, char *name ){
	cmtDeb( name, " |\n |__  %s id[%i][ %s ]\n |\n", type, id, name );
}

void cmt_hashsDump( ){
	printf("cnn_Hashs ... START\n");
	printf("## h |id | N |Ntyp|    *fpts       | name \n" );
	for( int h=0; true; h++ ){
		if( cnn_Hashs[ h ].id == -1 ) break;
		printf("##% 3i|% 3i| %c | % 3i|% 16p| %s\n", 
			h, cnn_Hashs[ h ].id, 
			( cnn_Hashs[ h ].isNode ? 'X' : ' ' ),
			cnn_Hashs[ h ].nType, 
			cnn_Hashs[ h ].fPts, cnn_Hashs[ h ].name 
			);

		if( 0 && h == 1 ){
			cnn_Msg msgt = { -1, "and/testHot123", "42.02" };
			cnn_Hashs [ h ].fPts( 1, &msgt );
		}

	}
	printf("------ cnn_Hashs END \n");

}
