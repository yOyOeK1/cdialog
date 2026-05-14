/*
 * Copyright (C) 2016-2023 Davidson Francis <davidsondfgl@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ws.h>

#include "cnn_config_data.h"
#include "cmachine2.h"


//typedef struct {
//    int id;
//    char name[32];
//    char ip[16];
//    int port;
//} ws_setting_t;


void cnn_wsServer_pub( int nId, cnn_Msg *msg ){
	printf("TODO\n");
}


int cwsS_getServerIndex_fromWsCli( ws_cli_conn_t client ){
	int sId = ws_getSId( client );
	for( int s=0; true; s++ ){
		if( cnn_wsServers[ s ].id == -1 ) break;
		if( cnn_wsServers[ s ].id == sId){
			return s;
		}
	}

	return -1;
}

void cwsS_onopen(ws_cli_conn_t client){
	char *cli, *port;
	cli  = ws_getaddress(client);
	port = ws_getport(client);
	char *sName = ws_getSName( client );
	int sId = ws_getSId( client );
	int s = cwsS_getServerIndex_fromWsCli( client );
	//struct ws_server sc = ws_get_server_context( client );
	//ws_setting_t si = (ws_setting_t)ws_get_server_user_data(client);
	printf("[WSS][%i] Connection opened, addr: %s, port: %s cNo:%i [%s]\n", sId, cli, port, client, sName );
	//ws_sendframe_txt( client, "{\"time\":1,\"a\":1}" );


	printf("[WSS][%i] Lookinf for a spot for client ....\n", sId );
	for( int c=0; c<CNN_WS_SERVER_CLIENTS_MAX; c++ ){
		if( cnn_wsServers[ s ].online[ c ] == false ){
			printf(" - slot [%i / %i]\n", c, CNN_WS_SERVER_CLIENTS_MAX );
			cnn_wsServers[ s ].online[ c ] = true;
			cnn_wsServers[ s ].clients[ c ] = (void*)client;
			break;
		}
	}



	cnn_Msg msgT;
	strcpy( msgT.topic, "and/test/ws/server/status/newClient" );
	strcpy( msgT.payload, "newClient" );
	msgT.nIndex = 0;
	cm_doWorkAt_byNId( sId, CNNWSSERVER, 1, &msgT );
}

void cwsS_onclose(ws_cli_conn_t client){
	char *cli;
	cli = ws_getaddress(client);
	int sId = ws_getSId( client );
	int s = cwsS_getServerIndex_fromWsCli( client );
	for( int c=0; c<CNN_WS_SERVER_CLIENTS_MAX; c++ ){
		if( cnn_wsServers[ s ].online[ c ] == true &&
			cnn_wsServers[ s ].clients[ c ] == client ){
			printf(" - at slot [%i]\n", c );
			cnn_wsServers[ s ].online[ c ] = false;
			break;
			
		}
	}
	printf("[WSS][%i] Connection closed, addr: %s\n", sId, cli);
}
void cwsS_onmessage(ws_cli_conn_t client,
	const unsigned char *msg, uint64_t size, int type){
	char *cli;
	cli = ws_getaddress(client);
	printf("I receive a message: %s (size: %" PRId64 ", type: %d), from: %s\n",
		msg, size, type, cli);

	//ws_sendframe_bcast(8080, (const char*)msg, size, type);

	cnn_Msg msgT;
	strcpy( msgT.topic, "and/test/ws/server/onMsg" );
	strcpy( msgT.payload, msg );
	msgT.nIndex = 0;
	cm_doWorkAt_byNId( cnn_wsServers[ 0 ].id, CNNWSSERVER, 0, &msgT );
}

void *cmInit_wsServer_pthread( void *vargp ){
	int s = (int)vargp;
	bool initStatus = true;
	while( true ){

		ws_socket(&(struct ws_server){
			.host = cnn_wsServers[ s ].ipBind, //"0.0.0.0",
			.port = cnn_wsServers[ s ].port, //8080,
			.id = cnn_wsServers[ s ].id,
			.name = cnn_wsServers[ s ].name,
			.thread_loop   = 0,
			.timeout_ms    = 1000,
			.evs.onopen    = &cwsS_onopen,
			.evs.onclose   = &cwsS_onclose,
			.evs.onmessage = &cwsS_onmessage
		});


	}
}

int cmInit_wsServer(){
	printf("[WSS] ... init START\n");
	for( int s=0; true ; s++){
		if( cnn_wsServers[ s ].id == -1 ) break;	

		printf("[WSS][%i] id[%i] init  [%s]\n"
				"\t%s:%i\n",
			s, cnn_wsServers[ s ].id, cnn_wsServers[ s ].name,
				cnn_wsServers[ s ].ipBind, cnn_wsServers[ s ].port
			);

		pthread_create( &cnn_wsServers[ s ].tId, NULL, cmInit_wsServer_pthread, (void *)s );


	}
	
	printf("[WSS] ... init END\n");
	return 0;

}

#ifdef CPPCWSSTEST
int main(void)
{
	ws_socket(&(struct ws_server){
		.host = "0.0.0.0",
		.port = 8080,
		.thread_loop   = 0,
		.timeout_ms    = 1000,
		.evs.onopen    = &cwsS_onopen,
		.evs.onclose   = &cwsS_onclose,
		.evs.onmessage = &cwsS_onmessage
	});

	return (0);
}
#endif
