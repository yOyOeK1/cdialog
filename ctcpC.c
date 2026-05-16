#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cnn_config_data.h"
#include "cmachine2.h"

#define SA struct sockaddr

//typedef struct {
//    int id;
//    char name[32];
//    char ip[16];
//    int port;
//} tcpC_setting_t;

//int cnn_tcpC_getServerIndex_fromWsCli( tcpC_cli_conn_t client ){
//	int sId = ws_getSId( client );
//	for( int s=0; true; s++ ){
//		if( cnn_tcpCClients[ s ].id == -1 ) break;
//		if( cnn_tcpCClients[ s ].id == sId){
//			return s;
//		}
//	}
//
//	return -1;
//}

void cnn_tcpCClient_pub( int nId, cnn_Msg *msg ){
	int s;
	for( int s=0; true; s++ ){
		if( cnn_tcpCClients[ s ].id == -1 ) break;
		if( cnn_tcpCClients[ s ].id == nId ) break;

			//ws_sendframe_txt( (long unsigned int)cnn_tcpCClients[ s ].clients[ c ],
			//		msg->payload 
			//	);

		
	
	}
}


/*
void cwsS_onopen(ws_cli_conn_t client) {
	char *cli, *port;
	//cli  = ws_getaddress(client);
	//port = ws_getport(client);
	//char *sName = ws_getSName( client );
	//int sId = ws_getSId( client );
	//int s = cwsS_getServerIndex_fromWsCli( client );
	//struct ws_server sc = ws_get_server_context( client );
	//ws_setting_t si = (ws_setting_t)ws_get_server_user_data(client);
	printf("[TCPC][%i] Connection opened, addr: %s, port: %s cNo:%i [%s]\n", sId, cli, port, client, sName );
	//ws_sendframe_txt( client, "{\"time\":1,\"a\":1}" );

	printf("[TCPC][%i] Lookinf for a spot for client ....\n", sId );
	for( int c=0; c<CNN_WS_SERVER_CLIENTS_MAX; c++ ){
		if( cnn_tcpCClients[ s ].online[ c ] == false ){
			printf(" - slot [%i / %i]\n", c, CNN_WS_SERVER_CLIENTS_MAX );
			cnn_tcpCClients[ s ].online[ c ] = true;
			cnn_tcpCClients[ s ].clients[ c ] = (void*)client;
			break;
		}
	}



	cnn_Msg msgT;
	strcpy( msgT.topic, "and/test/ws/server/status/newClient" );
	strcpy( msgT.payload, "newClient" );
	msgT.nIndex = 0;
	cm_doWorkAt_byNId( sId, CNNTCPCERVER, 1, &msgT );

}

void cwsS_onclose(ws_cli_conn_t client) {
	char *cli;
	cli = ws_getaddress(client);
	int sId = ws_getSId( client );
	int s = cwsS_getServerIndex_fromWsCli( client );
	for( int c=0; c<CNN_WS_SERVER_CLIENTS_MAX; c++ ){
		if( cnn_tcpCClients[ s ].online[ c ] == true &&
			cnn_tcpCClients[ s ].clients[ c ] == client ){
			printf(" - at slot [%i]\n", c );
			cnn_tcpCClients[ s ].online[ c ] = false;
			break;
			
		}
	}
	printf("[TCPC][%i] Connection closed, addr: %s\n", sId, cli);
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
	cm_doWorkAt_byNId( cnn_tcpCClients[ 0 ].id, CNNTCPCERVER, 0, &msgT );
}
*/
void cm_tcpC_function( int i ){
	char buff[512];
	int n;

	cnn_Msg msgT;
	strcpy( msgT.topic, "and/test/tcp/client/status/connected" );
	strcpy( msgT.payload, "connected" );
	cnn_tcpCClients[ i ].online = true;
	msgT.nIndex = 0;
	cm_doWorkAt_byNId( cnn_tcpCClients[ i ].id, CNNTCPCLIENT, 1, &msgT );

	for (;;) {
		bzero(buff, sizeof(buff));
			;
		//write( cnn_tcpCClients[ i ].sockfd, buff, sizeof(buff));
		//bzero(buff, sizeof(buff));
		

		read( cnn_tcpCClients[ i ].sockfd, buff, sizeof(buff));
		if( strlen(buff) == 0 ) break; 
		//printf("[TCPC] From Server : %s\n", buff);

		strcpy( msgT.topic, "and/test/tcp/client/onMsg" );
		strcpy( msgT.payload, buff );
		msgT.nIndex = 0;
		cm_doWorkAt_byNId( cnn_tcpCClients[ i ].id, CNNTCPCLIENT, 0, &msgT );
		
		//if ((strncmp(buff, "exit", 4)) == 0) {
		//	printf("Client Exit...\n");
		//	break;
		//}
	}

}
int cmInit_tcpC_byIndex( int i ){
	cnn_tcpCClients[ i ].sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cnn_tcpCClients[ i ].sockfd == -1) {
		printf("[TCPC] socket creation failed...\n");
		return -2;
	}
	//else
	//	printf("[TCPC] Socket successfully created..\n");
	bzero(&cnn_tcpCClients[ i ].servaddr, sizeof(cnn_tcpCClients[ i ].servaddr));

	// assign IP, PORT
	cnn_tcpCClients[ i ].servaddr.sin_family = AF_INET;
	cnn_tcpCClients[ i ].servaddr.sin_addr.s_addr = inet_addr( cnn_tcpCClients[ i ].ipBind );
	cnn_tcpCClients[ i ].servaddr.sin_port = htons(cnn_tcpCClients[ i ].port );

	// connect the client socket to server socket
	if (connect(cnn_tcpCClients[ i ].sockfd, (SA*)&cnn_tcpCClients[ i ].servaddr, sizeof(cnn_tcpCClients[ i ].servaddr))
			!= 0) {
		printf("[TCPC] connection with the server failed...[%s:%i]\n",
			cnn_tcpCClients[ i ].ipBind, cnn_tcpCClients[ i ].port );
		return -1;
	}
	else
		printf("[TCPC] connected to the server...[%s:%i]\n",
			cnn_tcpCClients[ i ].ipBind, cnn_tcpCClients[ i ].port);

	
	cm_tcpC_function( i );


	cnn_Msg msgT;
	strcpy( msgT.topic, "and/test/tcp/client/status/disconnected" );
	strcpy( msgT.payload, "disconnected" );
	cnn_tcpCClients[ i ].online = false;
	msgT.nIndex = 0;
	cm_doWorkAt_byNId( cnn_tcpCClients[ i ].id, CNNTCPCLIENT, 1, &msgT );
	//
	// close the socket
	close(cnn_tcpCClients[ i ].sockfd);	
	return 0;
}

void *cmInit_tcpCClient_pthread( void *vargp ){
	int s = (int)vargp;
	bool initStatus = true;
	while( true ){

		printf("[TCPC][%i] ... spoon\n", s );
		cmInit_tcpC_byIndex( s );
		sleep( CNN_TCP_CLIENTS_RECONNECT );
		/*
		ws_socket(&(struct ws_server){
			.host = cnn_tcpCClients[ s ].ipBind, //"0.0.0.0",
			.port = cnn_tcpCClients[ s ].port, //8080,
			.id = cnn_tcpCClients[ s ].id,
			.name = cnn_tcpCClients[ s ].name,
			.thread_loop   = 0,
			.timeout_ms    = 1000,
			.evs.onopen    = &cwsS_onopen,
			.evs.onclose   = &cwsS_onclose,
			.evs.onmessage = &cwsS_onmessage
		});
		*/

	}
}

int cmInit_tcpCClient(){
	printf("[TCPC] ... init START\n");
	for( int s=0; true ; s++){
		if( cnn_tcpCClients[ s ].id == -1 ) break;	

		printf("[TCPC][%i] id[%i] init  [%s]\n"
				"\t%s:%i\n",
			s, cnn_tcpCClients[ s ].id, cnn_tcpCClients[ s ].name,
				cnn_tcpCClients[ s ].ipBind, cnn_tcpCClients[ s ].port
			);

		pthread_create( &cnn_tcpCClients[ s ].tId, NULL, cmInit_tcpCClient_pthread, (void *)s );


	}
	
	printf("[TCPC] ... init END\n");
	return 0;

}

#ifdef CPPCTCPCTEST
int main(void)
{
//	ws_socket(&(struct ws_server){
//		.host = "0.0.0.0",
//		.port = 8080,
//		.thread_loop   = 0,
//		.timeout_ms    = 1000,
//		.evs.onopen    = &cwsS_onopen,
//		.evs.onclose   = &cwsS_onclose,
//		.evs.onmessage = &cwsS_onmessage
//	});

	return (0);
}
#endif
