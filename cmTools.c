
#include <stdio.h>
#include <string.h>

#include "cnn_config_data.h"
#include "cmdh.h"

void cmt_start_byNode( machNode mn ){
	printf("\t* start by id ... %i\n", mn.id );	

	if( mn.typeOf == 0 ){ // cmd
		mn.isRunning = true;
		strcpy( mn.result, cmd_to_chars( mn.cmd ) );
		printf( "\t* ... result [ %s ]\n", mn.result );

	}else{
		printf("\tEE type not implemented [%i]\n", mn.typeOf );
	}
}

void cmt_NodeName( char *type, int id, char *name ){
	printf(" |\n |__  %s id[%i][ %s ]\n |\n", type, id, name );
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
