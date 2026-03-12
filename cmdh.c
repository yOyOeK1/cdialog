#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


char* cmd_to_chars( char *cmd ){
	FILE *f = popen( cmd, "r" );
	if( f == NULL ){
		perror("CMD error\n");
		return NULL;
	}
	
	//printf("#c ... cmd DONE\n");
	char line[512];
	static char lineLast[512];
	int lineN = 0;
	int tSize = 0;
	while( fgets( line, 512, f ) != NULL ){
		strcat(lineLast, line);
		tSize+= strlen( line );
		//printf( "[%i]%s", lineN++, line );
	}
	if( tSize > 0 ) lineLast[ tSize-1 ] = 0;
	//printf( "As last size (%i) / (%i)\n--------\n[%s]\n-------------\n", sizeof(lineLast), tSize, lineLast );
	//fseek( f, 0, SEEK_END);
	//long fSize = ftell( f );
	//char tr[ fSize+1 ];
	//char *tr = (char *)malloc(  fSize+1 );
	//fseek( f, 0, 0 );
	//fgets( tr, fSize, f );
	
	pclose( f );
	
	//printf("CMD res -----\n%s\n---------\n", lineLast );

	return lineLast;
}

/*
int main(){

	printf("Cmd test ...\n");
	printf("[cTest][%s]\n", cmd_to_chars("cal"));
	
	return 0;

}
*/
