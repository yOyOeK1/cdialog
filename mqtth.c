
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




struct mosquitto *mqMosqi;

struct mosquitto *mqHandler;
bool mqConnection = false;

void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    //int rc = MOSQ_ERR_SUCCESS;

    printf("mqtth ... connect\n");
    if(!result){
        //mosquitto_subscribe(mosq, NULL, "#", 0);
        mosquitto_subscribe(mosq, NULL, "dell/#", 0);
        mosquitto_subscribe(mosq, NULL, "hu/#", 0);
        printf("mqtth ... subscribed\n");
	mqHandler = mosq;
	mqConnection = true;
    }else{
        fprintf(stderr, "EE mqtth ... \n%s\n", mosquitto_connack_string(result));
    }
}


int add = 0;
void on_message( struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	printf(" [_ 󰃌 _]%s --> [%i] %s\n", 
		message->topic, 
		message->payloadlen, 
		message->payload
	);
	add++;
}

void mqttInit(  ){
	printf("mqtt - init ... to [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_lib_init();
	mqMosqi = mosquitto_new( NULL, true, NULL);
	mosquitto_connect_callback_set( mqMosqi, on_connect );
	mosquitto_message_callback_set( mqMosqi, on_message );
	mosquitto_connect( mqMosqi, mqttHost, mqttPort, 60 );

}

void mqttDoIt( ){
	mosquitto_loop_forever( mqMosqi, -1, 1);
	//mosquitto_disconnect() and mosquitto_loop_stop()
}
void mqttDestroy(){
	printf("#* ... mq destroy ... ");
	if( mqMosqi ){
		mosquitto_destroy( mqMosqi );
    		mosquitto_lib_cleanup();
		printf(" OK\n");
	}else{
		printf(" Abord\n");
	}
}

int rc;
void mqtt_publish( char *topic, char *msg ){
	if( mqConnection ){
	    rc = mosquitto_publish( mqHandler , NULL, topic, strlen( msg ), msg, 1, false);
	    if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "Error publishing: %s\n", mosquitto_strerror(rc));
	    }
	} else {
	    printf("#* ... waiting for connection to mqtt ...\n");
	}

}

int mqIter = 0;
void *myThread( void *vargp){

	while( true ){
		//printf( "iter...%i\n", add );
		//move( 1, 2 );
		if( (add%2)==0 ){
			printf("  %i\n",mqIter++);
			mqtt_publish( "and/ping", "okok"  );
		}else
			printf("  %i\n",mqIter++);
		sleep( 1 );

		if( mqIter > 3 ){
			printf("#* ... mqtt disconect ...\n");
			//mosquitto_loop_stop( mqHandler, false );
			//mqttDestroy();
			mosquitto_disconnect( mqMosqi );

			printf("#* ... mqtt disconect ... DONE\n");
			break;
		}

	}

	printf("#* ... mqtt dog DONE\n");
	return 0;
}





int main(){

	printf("mqtth test ...\n");
	pthread_t thread_id;
	pthread_create( &thread_id, NULL, myThread, NULL );

	mqttInit( );
	mqttDoIt( );
	mqttDestroy();


	printf("mqtth test ... DONE\n");
}
