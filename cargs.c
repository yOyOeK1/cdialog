
#include <stdio.h>
#include <string.h>


int col = 70;
int row = 10;
bool asBar = false;
int chFill = '.';
//extern int col;
//extern int row;
//extern bool asBar;
//extern int chFill;

int cc_main_argcParse( int argc, char *argv[] ){
       for( int a=0; a<argc ; a++ ){
		if( strncmp( argv[ a ], "-row=", 5 ) == 0 ){
			//printf("#* ... -row=\n");
			sscanf( argv[ a ], "-row=%d", &row );
		} else if( strncmp( argv[ a ], "-asBar", 6 ) == 0 ){
			//printf("{ \"version\": 1, \"click_events\": true }\n[\n[]\n");
			//printf("{ \"version\": 1, \"stop_signal\": 10, \"cont_signal\": 12, \"click_events\": true }\n[\n[]\n");
			printf("{ \"version\": 1 }\n[\n[]\n");
			asBar = true;

		} else if( strncmp( argv[ a ], "-col=", 5 ) == 0 ){
			//printf("#* ... -col=\n");
			sscanf( argv[ a ], "-col=%d", &col );
		} else if( strncmp( argv[ a ], "-chFill=", 8) == 0 ){
			chFill = argv[ a ][8];
			printf("#* ... -chFill= (%c)\n",chFill );
			//sscanf( argv[ a ], "-chFill=%c", chFill );
		} else if( strncmp( argv[ a ], "-h", 2) == 0 ){
			printf("#* ... -h	- this help (external function)\n\n"
				"-asBar		- to run it as i3bar / str standard and jsonish\n"
				"-row=N		- N rows to set\n"
				"-col=N		- N cols / lines to set\n"
				"-chFill=.	- . char to use as filler in clear\n"
				);
			return 0;
		}
	}

       return 1;
}


