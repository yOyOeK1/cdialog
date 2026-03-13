
#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#include "config.h"


struct mosquitto *mqc;

void mqtt_on_connect( struct mosquitto *mosq, void *obj, int result )
{
	int rc = MOSQ_ERR_SUCCESS;

	printf("mqtt on _ connected\n");
	if( !result ){
		printf("mqtt subscribe\n");
		mosquitto_subscribe( mosq, NULL, "#", 0 );
	}else{
		fprintf( stderr, "EE mqtt on connection\n%s\n", mosquitto_connack_string( result ) );
	}
}

int mqttLineC=0;
void mqtt_on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	/*
	printf(" [_ _]  mqtt msg\t%s --> [%i] %s\n", 
		message->topic, 
		message->payloadlen, 
		message->payload
		);

	if( true ){// if need to fillter or post process 
		//putMsg( message->topic, message->payload );
		move( 5+( mqttLineC++%4)  ,5 );
		printw( "%s[@][%p]\n", message->topic, message->payload );
	}else{
		printf("---------\ndrop msg topic [%s] \n-------------\n",
			message->topic
		);
	}
	*/
}

void mqtt_init()
{
	printf("mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_lib_init();
	printf("1mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
	mqc = mosquitto_new( NULL, true, NULL);
	printf("2mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_connect_callback_set( mqc, mqtt_on_connect );
	printf("3mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_message_callback_set( mqc, mqtt_on_message );
	printf("4mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_connect( mqc, mqttHost, mqttPort, 60 );
	printf("5mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );

}

void mqtt_doIt(){
	
	printf("90mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_loop_forever( mqc, -1, 1 );
	printf("91mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
	mosquitto_destroy( mqc );
	printf("92mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );
    	mosquitto_lib_cleanup();
	printf("93mqtt - init ... [ %s : %i ]\n", mqttHost, mqttPort );

}

///*
int main( void ){

	printf("## mqtth test .....\n");

	mqtt_init();
	mqtt_doIt();
	
	printf("## mqtth test .....DONE\n");
	return 0;
}

//*/
