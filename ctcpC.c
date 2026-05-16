#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cnn_config_data.h"
#include "cmachine2.h"

#define SA struct sockaddr

void cnn_tcpCClient_pub( int nId, cnn_Msg *msg ){
	int s;
	for( int s=0; true; s++ ){
		if( cnn_tcpCClients[ s ].id == -1 ) break;
		if( cnn_tcpCClients[ s ].id == nId &&
			cnn_tcpCClients[ s ].online == true ){

			write( cnn_tcpCClients[ s ].sockfd, msg->payload, sizeof( msg->payload ));
			break;
		}
			//ws_sendframe_txt( (long unsigned int)cnn_tcpCClients[ s ].clients[ c ],
			//		msg->payload 
			//	);

		
	
	}
}

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
		printf("[TCPC]EE connection with the server failed...[%s:%i]\n",
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

		cmInit_tcpC_byIndex( s );
		printf("[TCPC][%i] ... retry in (%i) sec.\n", s, CNN_TCP_CLIENTS_RECONNECT );
		
		sleep( CNN_TCP_CLIENTS_RECONNECT );

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

	return (0);
}
#endif
