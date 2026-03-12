#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>



void *myDogTest( void * vargp ){
	printw("[dog.c] \n");
	int lNo = 0;
	while( true ){
		move( 2, (lNo%5) );
		printw("[d](%i) loop\n", lNo);
		refresh();
		sleep( 1 );
		lNo++;
	}

	printw("[dog.c] ... DONE\n");
}

// TODO FIX IT
int dog_create( char *myFunction ){
	pthread_t tId;
	pthread_create( &tId, NULL, myDogTest, NULL ); 
	return 0;
}
