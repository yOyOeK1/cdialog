/* file: [ ./ctcpS.c ] */
void cnn_tcp_printf(  );
void cnn_tcpS_doClick( int chNo, int sNo, int cNo, char *topic, char *msg );
void cnn_tcpS_onMsg( int sNo, int cNo, char *msg );
void cnn_tcpS_func(int connfd, int sNo, int cNo); 
void cnn_tcpServer_pub( int nInd, cnn_Msg *msgT );
void *cmInit_tcpServer_pthread( void *vargp );
int cmInit_tcpServer();
void *cmInit_tcpServerSpone1( void *vargp );
