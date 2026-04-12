
/*
 *
 */

#define VER 2026.0405

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <ncurses.h>

#include "config.h"

#include "cargs.h"
#include "cpostprocess.h"


extern int col;
extern int row;
extern bool asBar;
extern int chFill;


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

	for( int q=0; true; q++ ){
		printf("mqNode q:[%i]\n\t[ %s ] @ [ %s ]\n", q, mqNodes[ q ].title, mqNodes[ q ].topic );
		mosquitto_subscribe( mosq, NULL, mqNodes[ q ].topic, 0 );


		if( mqNodes[ q + 1 ].parentId == -1 ) break;

	}


	for( mqSubsCount=0; true; mqSubsCount++ ){
		if( mqSubs[ mqSubsCount ] == 0 ){
			mqSubsCount--;
			break;
		}else{
			printf("#* mq-sub to [ %s ]\n", mqSubs[ mqSubsCount ] );
			mosquitto_subscribe( mosq, NULL, mqSubs[ mqSubsCount ], 0 );
		}
	}
        printf("mqtth ... subscribed\n");
	mqHandler = mosq;
	mqConnection = true;
    }else{
        fprintf(stderr, "EE mqtth ... \n%s\n", mosquitto_connack_string(result));
    }
}

int add = 0;
bool addDone = false;
char mesBuff[512];
long int mesLong;
float mesFloat;
void on_message( struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	addDone = false;
	//printf("obj [%i] topic: [%s]\n", message->mid, message->topic ); 
	
	for( int q=0; true; q++ ){
		if( strcmp( mqNodes[ q ].topic, message->topic ) == 0 ){
			//printf("D as i:[%i] d:[%d] f:[%f]\n", mesBuff, mesBuff, mesBuff	);	
			if( mqNodes[ q ].postp == ' ' ){
				sscanf( message->payload, mqNodes[ q ].args, &mesBuff );
				snprintf( mqNodes[ q ].payload, 512, mqNodes[ q ].printAs, *mesBuff );
			
			} else if( mqNodes[ q ].postp == 't' ){
				mesLong = strtol( message->payload, NULL, 10 );
				snprintf( mqNodes[ q ].payload, 512, mqNodes[ q ].printAs, cPP_secLeft( mesLong  ) );
			
			} else if( mqNodes[ q ].postp == 'p' ){
				mesFloat = strtof( message->payload, NULL );
				//printf("as progress got float [%f]\n", mesFloat );
				snprintf( mqNodes[ q ].payload, 512, mqNodes[ q ].printAs, cPP_asProgress( mesFloat  ) );
			
			}


			//strcpy( mqNodes[ q ].payload, message->payload );
			mqNodes[ q ].entryDate = add;
			printf( "%s\n\t%s", mqNodes[ q ].title, mqNodes[ q ].payload );
			addDone = true;
			break;
		}


		if( mqNodes[ q + 1 ].parentId == -1 ) break;
	}

	if( addDone == false ){
		printf(" [_ 󰃌 _]%s --> [%i] %s\n", 
			message->topic, 
			message->payloadlen, 
			message->payload
		);
	}
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


int main( int argc, char *argv[] ){

	if( argc > 1 && cc_main_argcParse( argc, argv )!= 1 )  return 0;

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

