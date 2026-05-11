#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#ifdef CCANVASTEST
#include "config.h"
#endif

extern int TIME_ZONE_OFFSET;


int time_now(){
	time_t tNow;
	time( &tNow );
	tNow+= TIME_ZONE_OFFSET;
	return tNow;
}

long time_now_stamp(){
	return (long)time( NULL );
}

uint64_t time_now_stampMS(){
    struct timespec ts;
    // CLOCK_REALTIME: Wall clock time (can jump if NTP adjusts time)
    // CLOCK_MONOTONIC: Time since boot (better for measuring intervals)
    clock_gettime(CLOCK_REALTIME, &ts);

    // Convert seconds to ms and nanoseconds to ms
    return (uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000;
}
uint64_t time_now_deltaMS( uint64_t tStart ){
	return time_now_stampMS() - tStart;
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
