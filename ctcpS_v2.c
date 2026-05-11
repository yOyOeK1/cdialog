#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include "cnn_config_data.h"
#include "ctcpS.h"

#define CNN_TCP_SERVER_MAX 512 

// Thread function to handle individual client communication
void *client_handler(void *socket_desc) {
	int sock = *(int*)socket_desc;
	free(socket_desc); // Free the memory allocated in the main thread
	char buffer[CNN_TCP_SERVER_MAX];
	int read_size;

	// Send a welcome message
	char *message = "Connected to the server. Echoing back: \n";
	send(sock, message, strlen(message), 0);

	// Receive data from client
	while ((read_size = recv(sock, buffer, CNN_TCP_SERVER_MAX, 0)) > 0) {
		buffer[read_size] = '\0';
		send(sock, "echo\n", 5, 0);
		send(sock, buffer, strlen(buffer), 0); // Echo back to client
		memset(buffer, 0, CNN_TCP_SERVER_MAX);
	}

	if (read_size == 0) {
		puts("Client disconnected");
	} else if (read_size == -1) {
		perror("recv failed");
	}

	close(sock);
	pthread_exit(NULL);
}

// for cmachine2 ....
int tcpV2ClientNo = 0; // TODO
void *cnn_tcpSV2_func( void *socket_desc ){
	cnn_tcpClient client = *(cnn_tcpClient*)socket_desc;
	int sock = client.connfd;
	//int sock = *(int*)socket_desc;
	free(socket_desc); // Free the memory allocated in the main thread
	char buffer[CNN_TCP_SERVER_MAX];
	int read_size;

	// Send a welcome message
	char *message = "Connected to the server. Echoing back: \n";
	//send(sock, message, strlen(message), 0);

	cnn_tcpS_doClick( 1, client.sNo, client.cNo, "/and/test/tcp/server/status/newClient", "newClient" );
	// Receive data from client
	while ((read_size = recv(sock, buffer, CNN_TCP_SERVER_MAX, 0)) > 0) {
		buffer[read_size] = '\0';
		
		cnn_tcpS_onMsg( client.sNo, client.cNo, buffer  );

		//send(sock, "echo\n", 5, 0);
		//send(sock, buffer, strlen(buffer), 0); // Echo back to client
		memset(buffer, 0, CNN_TCP_SERVER_MAX);
	}

	if (read_size == 0) {
		puts("Client disconnected");
		cnn_tcpS_doClick( 1, client.sNo, client.cNo, "/and/test/tcp/server/status/disconnectedClient", "disconnectedClient" );
	} else if (read_size == -1) {
		perror("recv failed");
	}

	close(sock);
	cnn_tcpServers[ client.sNo ].online[ client.cNo ] = false;
	pthread_exit(NULL);
}

int ctcpSv2_init_server( int hPort ) {
	int server_fd, client_sock, *new_sock;
	struct sockaddr_in server, client;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	// 1. Create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	// 2. Bind socket to port
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( hPort );
	bind(server_fd, (struct sockaddr *)&server, sizeof(server));

	// 3. Listen for connections
	listen(server_fd, 5);
	printf("Server listening on port %d...\n", hPort );

	// 4. Accept loop
	while ((client_sock = accept(server_fd, (struct sockaddr *)&client, &addr_len))) {
		pthread_t thread_id;
		new_sock = malloc(sizeof(int)); // Use heap to avoid race conditions
		*new_sock = client_sock;

		if (pthread_create(&thread_id, NULL, client_handler, (void*)new_sock) < 0) {
			perror("Could not create thread");
			return 1;
		}

		// Detach the thread to reclaim resources automatically upon exit
		pthread_detach(thread_id);
		puts("Handler assigned to client");
	}

	close(server_fd);
	return 0;
}

#ifdef CTCPV2TEST
int main(){
	printf("ctcp v2 start \n");

	ctcpSv2_init_server( 8090 );

	printf("ctcp v2 END \n");


	return 0;
}

#endif

