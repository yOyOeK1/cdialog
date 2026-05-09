
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

#define CNN_TCP_SERVER_MAX 512 
#define SA struct sockaddr 

void cnn_tcp_printf(  ){
}

void cnn_tcpS_doClick( int chNo, int sNo, int cNo, char *topic, char *msg ){
	cnn_Msg msgT;
	strcpy( msgT.topic, topic );
	strcpy( msgT.payload, msg );
	//cm_doClick( 1, 0, msgT, CNNTCPSERVER, cnn_tcpServers[ sNo ].id );
	//cm_doWorkAt_byNId( cnn_tcpServers[ sNo ].id, CNNTCPSERVER, chNo, &msgT );
	cm_doWorkAt_byNId( sNo, CNNTCPSERVER, chNo, &msgT );
}


void cnn_tcpS_onMsg( int sNo, int cNo, char *msg ){
        printf(" | [TCPS]No[%i] . . . msg from clientNo[%i] (%i): %s\n", sNo, cNo, strlen(msg), msg ); 
	cnn_tcpS_doClick( 0, sNo, cNo, "/and/test/tcp/server/onMsg", msg );

//	cnn_Msg msgT;
//	strcpy( msgT.topic, "/and/test/tcp/server/onMsg" );
//	strcpy( msgT.payload, msg );
//	cm_doClick( 1, 0, msgT, CNNTCPSERVER, cnn_tcpServers[ sNo ].id );
}

void cnn_tcpS_func(int connfd, int sNo, int cNo){ 
    char buff[CNN_TCP_SERVER_MAX]; 
    cnn_tcpServers[ sNo ].online[ cNo ] = true;
    int n; 
    // infinite loop for chat 
    for (;;) { 
        //bzero(buff, CNN_TCP_SERVER_MAX); 
 	memset( buff, 0, CNN_TCP_SERVER_MAX );
	// on hello to client  
//	strcpy( buff, "$GPGGA,172814.0,3723.46587704,N,12202.26957864,W,2,6,1.2,18.893,M,-25.669,M,2.0,0031*4F\n" );
//	write( connfd, buff, sizeof(buff));

        // read the message from client and copy it in buffer 
        read(connfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        //printf("From client(%i): %s\n", strlen(buff), buff); 
	cnn_tcpS_onMsg( sNo, cNo, buff );
	if( strlen( buff ) == 0 ) break;
        //bzero(buff, CNN_TCP_SERVER_MAX); 
 	memset( buff, 0, CNN_TCP_SERVER_MAX );
 //       n = 0; 
        // copy server message in the buffer 
//        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // and send that buffer to client 
//        write(connfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
//        if (strncmp("exit", buff, 4) == 0) { 
//            printf("Server Exit...\n"); 
//            break; 
//        } 
    } 
    cnn_tcpServers[ sNo ].online[ cNo ] = false;
    printf("[TCPS][%i] client[%i] left ...\n", sNo, cNo );
} 

char tcpBuff[512];
void cnn_tcpServer_pub( int nInd, cnn_Msg *msgT ){
	printf("[TCPS] pub msg ... NoSer[%i] not id\n", nInd);
	for( int c=0; c<CNN_TCP_SERVER_CLIENTS_MAX; c++ ){
		if( cnn_tcpServers[ nInd ].online[ c ] ){
			printf(" %i ", c);
			//snprintf( tcpBuff, 512, "hi %s\n", msgT->payload );
			//write( cnn_tcpServers[ nInd ].connfds[ c ], tcpBuff, sizeof( tcpBuff ) );
			write( cnn_tcpServers[ nInd ].connfds[ c ], msgT->payload, sizeof( msgT->payload ) );

		}
	}
}


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
			
		    // After chatting close the socket 
		    close(cnn_tcpServers[ s ].sockfd); 
		    printf("[TCPS] ... end thread\n");
	}
	printf("[TCPS] ... end status(%s)\n", initStatus?"OK":"ERROR");
}

int cmInit_tcpServer(){
	printf("[TCPS] ... init START\n");
	for( int s=0; true ; s++){
		if( cnn_tcpServers[ s ].id == -1 ) break;	

		//printf("[TCPS] init  %s:%i\n   \\__ sNo[%i] as: [ %s ]\n", 
		//	cnn_tcpServers[ s ].ipBind, cnn_tcpServers[ s ].port, s, cnn_tcpServers[ s ].name );
		printf("[TCPS] init  [%s]\n"
				"\t%s:%i\n",
			cnn_tcpServers[ s ].name,
				cnn_tcpServers[ s ].ipBind, cnn_tcpServers[ s ].port
			);

		int sNo = s;
		pthread_create( &cnn_tcpServers[ s ].tId, NULL, cmInit_tcpServer_pthread, (void *)sNo );


	}
	
	printf("[TCPS] ... init END\n");
	return 0;
}

#ifdef CNN_TCP_SERVER_TEST
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

