#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* time_now_tt(){
	time_t tnow;
	time( &tnow );
	struct tm *mtime = localtime( &tnow );
	char *tr = asctime( mtime );
	

	sprintf( tr, "[%d%02d%02d_tt%02d%02d%02d]", mtime->tm_year-100,
            mtime->tm_mon + 1, mtime->tm_mday ,
            mtime->tm_hour, mtime->tm_min, mtime->tm_sec
	    );	

	//printf("Tm_tt [%s]\n", tr );//asctime( mtime) );
	return tr; //asctime( mtime);// ::NiceTime ::";
}
char* time_now_nice(){
	time_t tnow;
	time( &tnow );
	struct tm *mtime = localtime( &tnow );
	char *tr = asctime( mtime );
	//printf("Tm [%s]\n", tr );//asctime( mtime) );
	return tr; //asctime( mtime);// ::NiceTime ::";
}

int main(){

	printf("Time test ...\n");
	printf("[tTest_tt][%s]\n", time_now_tt());
	printf("[tTest][%s]\n", time_now_nice());
	return 0;
}

