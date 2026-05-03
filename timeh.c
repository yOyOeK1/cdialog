#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "config.h"

extern int TIME_ZONE_OFFSET;


int time_now(){
	time_t tNow;
	time( &tNow );
	tNow+= TIME_ZONE_OFFSET;
	return tNow;
}

char* time_now_tt(){
	time_t tnow = time_now();
	//time( &tnow );
	// time zone offset
	//tnow+= TIME_ZONE_OFFSET;//60*60*-5;
	struct tm *mtime = localtime( &tnow );
	char *tr = asctime( mtime );
	

	sprintf( tr, "%02d%02d%02d_tt%02d%02d%02d", mtime->tm_year-100,
            mtime->tm_mon + 1, mtime->tm_mday ,
            mtime->tm_hour, mtime->tm_min, mtime->tm_sec
	    );	
	// end it
	tr[15] = 0;
	//printf("Tm_tt [%s]\n", tr );//asctime( mtime) );
	return tr; //asctime( mtime);// ::NiceTime ::";
}
char* time_now_nice(){
	time_t tnow = time_now();
	//time( &tnow );
	struct tm *mtime = localtime( &tnow );
	char *tr = asctime( mtime );
	//printf("Tm [%s]\n", tr );//asctime( mtime) );
	return tr; //asctime( mtime);// ::NiceTime ::";
}

/*int main(){

	printf("Time test ...\n");
	printf("[tTest_tt][%s]\n", time_now_tt());
	printf("[tTest][%s]\n", time_now_nice());
	return 0;
}
*/
