
#include <stdio.h>

#include "cnn_config_data.h"


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
