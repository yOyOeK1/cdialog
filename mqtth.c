
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

#ifdef CMQTTHTEST

#include "config.h"

#else

#include "cnn_config_data.h"

extern char *machineName;

extern char *mqttHost;
extern int mqttPort;
extern char *mqttClientId;
extern char *mqTopicPrefix;

//extern struct mqSub mqSubs[];


#endif



struct mosquitto *mqMosqi;

struct mosquitto *mqHandler;
bool mqConnection = false;
char mqTopicBase[512];
int mqSubsCount = 0;

void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    //int rc = MOSQ_ERR_SUCCESS;

    printf("mqtth ... connect\n");
    if(!result){
        //mosquitto_subscribe(mosq, NULL, "#", 0);
        //mosquitto_subscribe(mosq, NULL, "dell/#", 0);
        //mosquitto_subscribe(mosq, NULL, "hu/#", 0);
#ifdef MQTT_FROM_MQNODES
	for( int q=0; true; q++ ){
		if( mqNodes[ q + 1 ].parentId == -1 ) break;
		printf("mqNode q:[%i]\n\t[ %s ] @ [ %s ]\n", q, mqNodes[ q ].title, mqNodes[ q ].topic );
		mosquitto_subscribe( mosq, NULL, mqNodes[ q ].topic, 0 );

	}
#endif 

#ifdef MQTT_FROM_MQNODES2
	int mqHontId = 1;
	for( int c=0; c<cnn_MqttSubsCount; c++ ){
		if( cnn_MqttSubs[ c ].mqHostId == mqHontId ){
			printf("mqNode2 q:[%i]\n\t[ %s ] @ [ %s ]\n", c, cnn_MqttSubs[ c ].name, cnn_MqttSubs[ c ].topic );
			mosquitto_subscribe( mosq, NULL, cnn_MqttSubs[ c ].topic, 0 );
		}
	}
#endif


#ifdef MQTT_FROM_SUBS
	for( mqSubsCount=0; true; mqSubsCount++ ){
		if( mqSubs[ mqSubsCount ] == 0 ){
			mqSubsCount--;
			break;
		}else{
			printf("#* mq-sub to [ %s ]\n", mqSubs[ mqSubsCount ] );
			mosquitto_subscribe( mosq, NULL, mqSubs[ mqSubsCount ], 0 );
		}
	}
#endif
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



void mqttInit( ){
	printf("#* mqtt - init ...\n");
	
	/*
	for( int h=0; true; h++ ){
		if( mqHosts[h].id == -1 )  break;
	
		struct mosquitto *pts;
		
		mqHosts[h].mqMosqi = (int)pts;
		mqHosts[h].connected = false;
		mqHosts[h].dogRun = true;
		pts = mosquitto_new( NULL, true, NULL);
		mosquitto_connect_callback_set( pts, on_connect );
		mosquitto_message_callback_set( pts, on_message );
		mosquitto_connect( pts, mqHosts[h].host , mqHosts[h].port, 60 );
		printf(" ... No[%i] pointer is [%i]\n", h, mqHosts[h].mqMosqi );
		//pthread_create( &mqHosts[h].thread_id, NULL, myThread, NULL);
	}
	*/

	snprintf( mqTopicBase, 512, "%s%s", mqTopicPrefix, machineName );

	printf("mqtt - init ... to [ %s : %i ]\n"
		"  use prefix	[ %s/ ... ]\n"
		//"  topic's 	[ %i ]\n"
		, mqttHost, mqttPort, mqTopicBase//, mqSubsCount
		);
	mosquitto_lib_init();
	mqMosqi = mosquitto_new( NULL, true, NULL);
	mosquitto_connect_callback_set( mqMosqi, on_connect );
	mosquitto_message_callback_set( mqMosqi, on_message );
	mosquitto_connect( mqMosqi, mqttHost, mqttPort, 60 );

}
void mqttInit2(){
	mosquitto_lib_init();
	for( int c=0; c<MqHostsCount; c++ ){
		printf("* mqtt init 2 [%s]\n\t%s:%i\n", MqHosts[ c ].name,  MqHosts[ c ].host, MqHosts[ c ].port );
		MqHosts[ c ].mqMosqi = mosquitto_new( NULL, true, NULL);
		mosquitto_connect_callback_set( MqHosts[ c ].mqMosqi, on_connect );
		mosquitto_message_callback_set( MqHosts[ c ].mqMosqi, on_message );
		mosquitto_connect( MqHosts[ c ].mqMosqi, MqHosts[ c ].host, MqHosts[ c ].port, 60 );
	}
}
void mqttDoIt2(){
	for( int c=0; c<MqHostsCount; c++ ){
		printf("* mqtt do it ... 2 [%s]\n\t%s:%i\n", MqHosts[ c ].name,  MqHosts[ c ].host, MqHosts[ c ].port );

		//mosquitto_loop_forever( MqHosts[ c ].mqMosqi, -1, 1);
		mosquitto_loop_start( MqHosts[ c ].mqMosqi );
		if( c == 0 ) break;
	}
}

void mqttDoIt( ){
	mosquitto_loop_forever( mqMosqi, -1, 1);
	//mosquitto_disconnect() and mosquitto_loop_stop()
}
void mqttDestroy( ){
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
void *myThread( void *vargp ){

	while( true ){
		//printf( "iter...%i\n", add );
		//move( 1, 2 );
		if( (add++%2)==0 ){
			printf("  %i\n",mqIter++);
			mqtt_publish( "and/ping", "okok"  );
		}else
			printf("  %i\n",mqIter++);
		sleep( 10 );

		if( 0 &&  mqIter > 3 ){
			printf("#* ... mqtt disconect ...\n");
			// to force to close it / mqtt client down conection / disconnect
			mosquitto_disconnect( mqMosqi );

			printf("#* ... mqtt disconect ... DONE\n");
			break;
		}

	}

	printf("#* ... mqtt dog DONE\n");
	return 0;
}

/*
int main( ){
	printf("mqtth test ...\n");
	pthread_t thread_id;
	pthread_create( &thread_id, NULL, myThread, NULL );

//	
//	// over hosts
//	printf("mqtt broker to connect:\n");
//	for( int h=0; true; h++ ){
//		if( mqHosts[h].id == -1 )  break;
//		printf(" * id[%i] (%s)\n\thost[%s]	port [%i] ...\n", 
//			mqHosts[h].id, mqHosts[h].name,  mqHosts[h].host, mqHosts[h].port );
//	}
//	// over hosts DONE

	mqttInit( );
	mqttDoIt( );
	mqttDestroy();

	printf("mqtth test ... DONE\n");
}
*/
