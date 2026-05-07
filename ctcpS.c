
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

#define CNN_TCP_SERVER_MAX 1024 
#define PORT 8081 
#define SA struct sockaddr 

void cnn_tcp_printf(  ){
}

void cnn_tcpS_onMsg( int sNo, int cNo, char *msg ){
        printf(" | . . . From client(%i): %s\n", strlen(msg), msg ); 
	cnn_Msg msgT;
	strcpy( msgT.topic, "/and/test/tcp/server/onMessage" );
	strcpy( msgT.payload, msg );
	cm_doClick( 1, 0, msgT, CNNTCPSERVER, cnn_tcpServers[ sNo ].id );
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
} 

char tcpBuff[512];
void cnn_tcpServer_pub( int nId, cnn_Msg *msgT ){
	printf("tcp server pub ... no[%i]\n", nId);
	for( int c=0; c<CNN_TCP_SERVER_CLIENTS_MAX; c++ ){
		if( cnn_tcpServers[ nId ].online[ c ] ){
			printf(" %i ", c);
			snprintf( tcpBuff, 512, "hi %s\n", msgT->payload );
			write( cnn_tcpServers[ nId ].connfds[ c ], tcpBuff, sizeof( tcpBuff ) );
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
	    // socket create and verification 
	    cnn_tcpServers[ s ].sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	    if ( cnn_tcpServers[ s ].sockfd == -1) { 
		printf("* tcp server socket creation failed...\n"); 
		printf("-11\n"); 
	    } else
		printf("* tcp server sSocket successfully created..\n"); 
	    memset(&cnn_tcpServers[ s ].servaddr, ' ', sizeof(cnn_tcpServers[ s ].servaddr)); 
	  

	    // assign IP, PORT 
	    cnn_tcpServers[ s ].servaddr.sin_family = AF_INET; 
	    cnn_tcpServers[ s ].servaddr.sin_port = htons( cnn_tcpServers[ s ].port); 
	    //cnn_tcpServers[ s ].servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	    if( inet_pton( AF_INET, cnn_tcpServers[ s ].ipBind, &cnn_tcpServers[ s ].servaddr.sin_addr ) <= 0 ){
		printf("* tcp server sEE tcp server error when making ip bind\n");
		printf("-1\n");
	    }

	    // Binding newly created socket to given IP and verification 
	    if ((bind(cnn_tcpServers[ s ].sockfd, (SA*)&cnn_tcpServers[ s ].servaddr, sizeof(cnn_tcpServers[ s ].servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		printf("-2\n");
	    } 
	    else
		printf("* tcp server sSocket successfully binded..\n"); 
	  
	    // Now server is ready to listen and verification 
	    if ((listen(cnn_tcpServers[ s ].sockfd, 5)) != 0) { 
		printf("* tcp server sListen failed...\n"); 
		printf("-3\n");
	    } else
		printf("Server listening..\n"); 
	    
	    cnn_tcpServers[ s ].len = sizeof( cnn_tcpServers[ s ].cli ); 
	  

	    // Accept the data packet from client and verification 
	    int connfd = accept( cnn_tcpServers[ s ].sockfd, (SA*)&cnn_tcpServers[ s ].cli, &cnn_tcpServers[ s ].len ); 
	    if (connfd < 0) { 
		printf("server accept failed...\n"); 
		printf("-4\n");
	    } else
		printf("server accept the client...\n"); 
	  
	    cnn_tcpServers[ s ].connfds[ tcpClientNo ] = connfd;
	    // Function for chatting between client and server 
	    cnn_tcpS_func(connfd, s, tcpClientNo++ ); 
		
	    // After chatting close the socket 
	    close(cnn_tcpServers[ s ].sockfd); 
}

int cmInit_tcpServer(){
	printf("* [TCPS] ... init START\n");
	for( int s=0; true ; s++){
		if( cnn_tcpServers[ s ].id == -1 ) break;	

		printf("* tcp server init  %s:%i\n   \\__ sNo[%i] as: [ %s ]\n", 
			cnn_tcpServers[ s ].ipBind, cnn_tcpServers[ s ].port, s, cnn_tcpServers[ s ].name );
		
		int sNo = s;
		pthread_create( &cnn_tcpServers[ s ].tId, NULL, cmInit_tcpServer_pthread, (void *)sNo );


	}
	
	printf("* [TCPS] ... init END\n");
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

