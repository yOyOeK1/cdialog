#include <stdio.h>
#include <stdlib.h>



char* file_read_to_chars( char *filePath ){
	FILE *f = fopen( filePath, "r" );
	if( f == NULL ){
		perror("File error\n");
		return NULL;
	}
	
	fseek( f, 0, SEEK_END);
	long fSize = ftell( f );
	//char tr[ fSize+1 ];
	char *tr = (char *)malloc(  fSize+1 );
	fseek( f, 0, 0 );
	fgets( tr, fSize, f );
	fclose( f );
	
	//printf("File size is: %ld\nFile content -----\n%s\n---------\n", fSize, tr );

	return tr;
}


//int main(){

//	printf("File test ...\n");
//	printf("[fTest][%s]\n", file_read_to_chars("/tmp/d"));
//	return 0;

//}
