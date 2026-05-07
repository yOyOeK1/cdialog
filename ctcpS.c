
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
#define MAX 1024 
#define PORT 8081 
#define SA struct sockaddr 

#define CNN_TCP_SERVER_CLIENTS_MAX 10
typedef struct{
	int id;
	char name[512];

	char ipBind[14]; // 123.567.890.123
	int port;

	bool running;
	int connfds[ CNN_TCP_SERVER_CLIENTS_MAX ];
	bool online[ CNN_TCP_SERVER_CLIENTS_MAX ];

	int sockfd, len;
	struct sockaddr_in servaddr, cli; 

} cnn_tcpServer;
cnn_tcpServer cnn_tcpServers[] = {
	{ 1,	"tcp test at 8088",	"127.0.0.1", 8088	},
	//{ 2,	"tcp test at 8089",	"127.0.0.1", 8089	},
	{ -1 }
};
int cnn_tcpServersCount = 1;

// Function designed for chat between client and server. 
void func(int connfd, int sNo, int cNo){ 
    char buff[MAX]; 
    cnn_tcpServers[ sNo ].online[ cNo ] = true;
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
 
	// on hello to client  
//	strcpy( buff, "$GPGGA,172814.0,3723.46587704,N,12202.26957864,W,2,6,1.2,18.893,M,-25.669,M,2.0,0031*4F\n" );
//	write( connfd, buff, sizeof(buff));

        // read the message from client and copy it in buffer 
        read(connfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\n", buff); 
        bzero(buff, MAX); 
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

int tcpSC = 0;
char tcpBuff[512];
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
int cmInit_tcpServer(){
	for( int s=0; true ; s++){
		if( cnn_tcpServers[ s ].id == -1 ) break;	
		printf("* tcp server init  [%s]:[%i]\n  as: [ %s ]\n", 
			cnn_tcpServers[ s ].ipBind, cnn_tcpServers[ s ].port, cnn_tcpServers[ s ].name );
		    // socket create and verification 
		    cnn_tcpServers[ s ].sockfd = socket(AF_INET, SOCK_STREAM, 0); 
		    if ( cnn_tcpServers[ s ].sockfd == -1) { 
			printf("socket creation failed...\n"); 
			return -11; 
		    } else
			printf("Socket successfully created..\n"); 
		    bzero(&cnn_tcpServers[ s ].servaddr, sizeof(cnn_tcpServers[ s ].servaddr)); 
		  
		    // assign IP, PORT 
		    cnn_tcpServers[ s ].servaddr.sin_family = AF_INET; 
		    cnn_tcpServers[ s ].servaddr.sin_port = htons( cnn_tcpServers[ s ].port); 
		    //cnn_tcpServers[ s ].servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
		    if( inet_pton( AF_INET, cnn_tcpServers[ s ].ipBind, &cnn_tcpServers[ s ].servaddr.sin_addr ) <= 0 ){
		    	printf("EE tcp server error when making ip bind\n");
			return -1;
	            }

		    // Binding newly created socket to given IP and verification 
		    if ((bind(cnn_tcpServers[ s ].sockfd, (SA*)&cnn_tcpServers[ s ].servaddr, sizeof(cnn_tcpServers[ s ].servaddr))) != 0) { 
			printf("socket bind failed...\n"); 
			return -2;
		    } 
		    else
			printf("Socket successfully binded..\n"); 
		  
		    // Now server is ready to listen and verification 
		    if ((listen(cnn_tcpServers[ s ].sockfd, 5)) != 0) { 
			printf("Listen failed...\n"); 
			return -3;
		    } 
		    else
			printf("Server listening..\n"); 
		    cnn_tcpServers[ s ].len = sizeof(cnn_tcpServers[ s ].cli); 
		  

		    // Accept the data packet from client and verification 
		    int connfd = accept(cnn_tcpServers[ s ].sockfd, (SA*)&cnn_tcpServers[ s ].cli, &cnn_tcpServers[ s ].len); 
		    if (connfd < 0) { 
			printf("server accept failed...\n"); 
			return -4;
		    } 

		    else
			printf("server accept the client...\n"); 
		  
		    cnn_tcpServers[ s ].connfds[ tcpClientNo ] = connfd;
		    // Function for chatting between client and server 
		    func(connfd, s, tcpClientNo++ ); 
	    
			
		    // After chatting close the socket 
		    close(cnn_tcpServers[ s ].sockfd); 



	}
}

// Driver function 
int main( ){

	pthread_t tId;
	pthread_create( &tId, NULL, cmInit_tcpServerSpone1, NULL ); 

	cmInit_tcpServer();
	return 0;

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
}

