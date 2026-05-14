
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <pthread.h>
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()

#include "cnn_config_data.h"
#include "cmachine2.h"
#include "ctcpS_v2.h"

#define CNN_TCP_SERVER_MAX 512 
#define SA struct sockaddr 

void cnn_tcp_printf(  ){
}

void cnn_tcpS_doClick( int chNo, int sNo, int cNo, char *topic, char *msg ){
	cnn_Msg msgT;
	strcpy( msgT.topic, topic );
	strcpy( msgT.payload, msg );
	msgT.nIndex = 0;
	cm_doWorkAt_byNId( cnn_tcpServers[ sNo ].id, CNNTCPSERVER, chNo, &msgT );
}


void cnn_tcpS_onMsg( int sNo, int cNo, char *msg ){
        printf(" | [TCPS][%i] . . . msg from clientNo[%i] (%i): %s\n", sNo, cNo, strlen(msg), msg ); 
	cnn_tcpS_doClick( 0, sNo, cNo, "/and/test/tcp/server/onMsg", msg );
}

//void cnn_tcpS_func(int connfd, int sNo, int cNo){ 
//    char buff[CNN_TCP_SERVER_MAX]; 
//    cnn_tcpServers[ sNo ].online[ cNo ] = true;
//    int n; 
//    for (;;) { 
// 	memset( buff, 0, CNN_TCP_SERVER_MAX );
//        read(connfd, buff, sizeof(buff)); 
//	cnn_tcpS_onMsg( sNo, cNo, buff );
//	if( strlen( buff ) == 0 ) break;
//    } 
//    cnn_tcpServers[ sNo ].online[ cNo ] = false;
//    printf("[TCPS][%i] client[%i] left ...\n", sNo, cNo );
//} 

void cnn_tcpServer_disconnect( int nId, cnn_Msg *msgT ){
	printf("[TCPS] disconnect all clients for server id[%i]\n", nId );
	for( int nInd=0; true; nInd++ ){
		if( cnn_tcpServers[ nInd ].id == -1 ) break;
		if( cnn_tcpServers[ nInd ].id == nId ){
			for( int c=0; c<CNN_TCP_SERVER_CLIENTS_MAX; c++ ){
				if( cnn_tcpServers[ nInd ].online[ c ] ){
					printf(" - client slot[%i]\n", c );
					close( cnn_tcpServers[ nInd].connfds[ c ] );

				}
			}
		}
	}
}
void cnn_tcpServer_clients( int nId, cnn_Msg *msgT ){
	printf("[TCPS] clients dump for server id[%i]\n", nId );
	for( int nInd=0; true; nInd++ ){
		if( cnn_tcpServers[ nInd ].id == -1 ) break;
		if( cnn_tcpServers[ nInd ].id == nId ){
			for( int c=0; c<CNN_TCP_SERVER_CLIENTS_MAX; c++ ){
				if( cnn_tcpServers[ nInd ].online[ c ] ){
					printf(" - client slot[%i]\n", c );

				}
			}
		}
	}
}


char tcpBuff[512];
void cnn_tcpServer_pub( int nId, cnn_Msg *msgT ){
	printf("[TCPS] pub msg ... id[%i]\n", nId);
	for( int nInd=0; true; nInd++ ){
		if( cnn_tcpServers[ nInd ].id == -1 ) break;
		if( cnn_tcpServers[ nInd ].id == nId ){
			for( int c=0; c<CNN_TCP_SERVER_CLIENTS_MAX; c++ ){
				if( cnn_tcpServers[ nInd ].online[ c ] ){
					printf(" %i ", c);
					write( cnn_tcpServers[ nInd ].connfds[ c ], msgT->payload, sizeof( msgT->payload ) );

				}
			}
			break;
		}
	}
}


int tcpClientNo = 0;
void *cmInit_tcpServer_pthread( void *vargp ){
	int s = (int)vargp;
	bool initStatus = true;
	while( true ){

		    // socket create and verification 
		    cnn_tcpServers[ s ].sockfd = socket(AF_INET, SOCK_STREAM, 0); 
		    if ( cnn_tcpServers[ s ].sockfd == -1) { 
			printf("[TCPS][%i] EE socket creation failed...\n", s ); 
			initStatus = false;
			break;
		    } else
			printf("[TCPS][%i] sSocket successfully created..\n", s ); 
		    memset(&cnn_tcpServers[ s ].servaddr, ' ', sizeof(cnn_tcpServers[ s ].servaddr)); 
		  

		    // assign IP, PORT 
		    cnn_tcpServers[ s ].servaddr.sin_family = AF_INET; 
		    cnn_tcpServers[ s ].servaddr.sin_port = htons( cnn_tcpServers[ s ].port); 
		    //cnn_tcpServers[ s ].servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
		    if( inet_pton( AF_INET, cnn_tcpServers[ s ].ipBind, &cnn_tcpServers[ s ].servaddr.sin_addr ) <= 0 ){
			printf("[TCPS][%i] EE when making ip bind\n", s );
			initStatus = false;
			break;
		    }

		    // Binding newly created socket to given IP and verification 
		    if ((bind(cnn_tcpServers[ s ].sockfd, (SA*)&cnn_tcpServers[ s ].servaddr, sizeof(cnn_tcpServers[ s ].servaddr))) != 0) { 
			printf("[TCPS][%i] EE socket bind failed...\n", s ); 
			initStatus = false;
			break;
		    } 
		    else
			printf("[TCPS][%i] sSocket successfully binded..\n", s ); 
		  
		    // Now server is ready to listen and verification 
		    if ((listen(cnn_tcpServers[ s ].sockfd, 5)) != 0) { 
			printf("[TCPS][%i]EE Listen failed...\n", s ); 
			initStatus = false;
			break;
		    } else
			printf("[TCPS][%i] Server listening..\n", s ); 
		    
		    cnn_tcpServers[ s ].len = sizeof( cnn_tcpServers[ s ].cli ); 
		  
		/*
	   while( true ){

		    printf("[TCPS][%i] ... waiting for client...\n", s ); 
		    // Accept the data packet from client and verification 
		    int connfd = accept( cnn_tcpServers[ s ].sockfd, (SA*)&cnn_tcpServers[ s ].cli, &cnn_tcpServers[ s ].len ); 
		    if (connfd < 0) { 
			initStatus = false;
			break;
			printf("[TCPS][%i] EE server accept failed...\n", s ); 
			printf("-4\n");
		    } else {
			printf("[TCPS][%i] server accept the client...\n", s ); 
		    	
			cnn_tcpS_doClick( 1, s, tcpClientNo, "/and/test/tcp/server/status/newClient", "newClient" );
		    }
		    cnn_tcpServers[ s ].connfds[ tcpClientNo ] = connfd;
		    // Function for chatting between client and server 
		    cnn_tcpS_func(connfd, s, tcpClientNo++ ); 
		    printf("[TCPS] ... left client function ...\n");
		    cnn_tcpS_doClick( 1, s, tcpClientNo, "/and/test/tcp/server/status/disconnectClient", "disconnectetClient" );
		usleep( 1000*500 );

	   }
	   */
				
		// 4. Accept loop
		int connfd;
		//int *new_sock;
		cnn_tcpClient *nClient;
		int cSlot = -1;
		while ((connfd = accept( cnn_tcpServers[ s ].sockfd, (SA*)&cnn_tcpServers[ s ].cli, &cnn_tcpServers[ s ].len))) {
			pthread_t thread_id;
		//	new_sock = malloc(sizeof(int)); // Use heap to avoid race conditions

			printf("[TCPSv2][%i] Lookinf for a spot for client ....\n", s );
			cSlot = -1;
			for( int c=0; c<CNN_TCP_SERVER_CLIENTS_MAX; c++ ){
				if( cnn_tcpServers[ s ].online[ c ] == false ){
					printf(" - slot [%i / %i]\n", c, CNN_TCP_SERVER_CLIENTS_MAX );
					cnn_tcpServers[ s ].connfds[ c ] = connfd;
					cnn_tcpServers[ s ].online[ c ] = true;
					//cnn_tcpServers[ s ].sNo[ c ] = s;
					cSlot = c;
					nClient = malloc( sizeof( cnn_tcpClient ) );
					nClient->cNo = c;
					nClient->sNo = s;
					nClient->connfd = connfd;
					cnn_tcpServers[ s ].clients[ c ] = (void*)nClient;
					break;
				}
			}

			if( cSlot != -1 ){
				if (pthread_create(&thread_id, NULL, cnn_tcpSV2_func, (void*)nClient) < 0) {
					printf("[TCPSv2][%i] EE Could not create thread", s);
					break;
				}

				// Detach the thread to reclaim resources automatically upon exit
				pthread_detach(thread_id);
				printf("[TCPSv2][%i]DD Handler assigned to client\n", s);
			} else {
				printf("[TCPSV2][%i] server to many clients\n", s );
			}
		}

		    // After chatting close the socket 
		    close( cnn_tcpServers[ s ].sockfd ); 
		    printf("[TCPS] ... end thread\n");
	}
	printf("[TCPS] ... end status(%s)\n", initStatus?"OK":"ERROR");
}

int cmInit_tcpServer(){
	printf("[TCPS] ... init START\n");
	for( int s=0; true ; s++){
		if( cnn_tcpServers[ s ].id == -1 ) break;	

		printf("[TCPS][%i] id[%i] init  [%s]\n"
				"\t%s:%i\n",
			s, cnn_tcpServers[ s ].id, cnn_tcpServers[ s ].name,
				cnn_tcpServers[ s ].ipBind, cnn_tcpServers[ s ].port
			);

		pthread_create( &cnn_tcpServers[ s ].tId, NULL, cmInit_tcpServer_pthread, (void *)s );


	}
	
	printf("[TCPS] ... init END\n");
	return 0;
}

#ifdef CNN_TCP_SERVER_TEST
int tcpSC = 0;
void *cmInit_tcpServerSpone1( void *vargp ){
	while( true ){
		printf(".\n");
		tcpSC++;
		for( int s=0; true; s++ ){
			if( cnn_tcpServers[ s ].id == -1 ) break;
			for( int c=0; c<CNN_TCP_SERVER_CLIENTS_MAX; c++ ){
				
				if( cnn_tcpServers[ s ].online[ c ] ){
					printf(" %i ", c);
					snprintf( tcpBuff, 512, "hi %i\n", tcpSC );
					write( cnn_tcpServers[ s ].connfds[ c ], tcpBuff, sizeof( tcpBuff ) );
				}
			}
		}
		sleep(1);
	}
}
// Driver function 
int main( ){

	pthread_t tId;
	pthread_create( &tId, NULL, cmInit_tcpServerSpone1, NULL ); 

	int tcpSRes = cmInit_tcpServer();
	printf("TCP Server exit result [%i]\n", tcpSRes );
	return 0;
	
/*
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server accept the client...\n"); 
  
    // Function for chatting between client and server 
    func(connfd, 1, 1); 
  
    // After chatting close the socket 
    close(sockfd); 
    */
}
#endif

