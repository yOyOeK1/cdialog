
/*
 *
 */

#define VER 2026.03.02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <ncurses.h>

#include "config.h"




struct mosquitto *mosq1;


void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    //int rc = MOSQ_ERR_SUCCESS;

    printf("mqtth ... connect\n");
    if(!result){
        mosquitto_subscribe(mosq, NULL, "#", 0);
        printf("mqtth ... subscribed\n");
    }else{
        fprintf(stderr, "EE mqtth ... \n%s\n", mosquitto_connack_string(result));
    }
}


int add = 0;
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	printf(" [_ 󰃌 _]%s --> [%i] %s\n", 
		message->topic, 
		message->payloadlen, 
		message->payload
	);
	add++;
}

void mqttInit(){
	printf("mqtt - init ... to [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_lib_init();
	mosq1 = mosquitto_new( NULL, true, NULL);
	mosquitto_connect_callback_set( mosq1, on_connect );
	mosquitto_message_callback_set( mosq1, on_message );
	mosquitto_connect( mosq1, mqttHost, mqttPort, 60 );

}

void mqttDoIt(){
	mosquitto_loop_forever(mosq1, -1, 1);
	//mosquitto_disconnect() and mosquitto_loop_stop()
	mosquitto_destroy(mosq1);
    	mosquitto_lib_cleanup();

}

int mqIter = 0;
void *myThread( void *vargp){
	while( true ){
		//printf( "iter...%i\n", add );
		//move( 1, 2 );
		if( (add%2)==0 )
			printf("  %i\n",mqIter++);
		else
			printf("  %i\n",mqIter++);
		sleep(1);

	}

}





int main(){

	printf("mqtth test ...\n");
	pthread_t thread_id;
	pthread_create( &thread_id, NULL, myThread, NULL );

	mqttInit();
	mqttDoIt();

}
