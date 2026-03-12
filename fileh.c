#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


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

char* file_read_dirList( char *dirPath ){
	DIR *dp;
	struct dirent *entry;

	dp = opendir( dirPath );
	if( dp != NULL ){
		while( ( entry = readdir( dp  ) ) ){
			printf("*t[%02i] [%s]\n", entry->d_type, entry->d_name);
		}	
	}else{
		perror("Dir list error\n");
	}
	return NULL;
}

/*
int main(){

	printf("File test ...\n");
	printf("[fTest][%s]\n", file_read_to_chars("/tmp/d"));
	
	// read dir 
	printf("[fTest][%s]\n", file_read_dirList("/tmp/") );
	return 0;

}
*/
