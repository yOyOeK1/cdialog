/* file: [ ./cwsS.c ] */
void cnn_wsServer_pub( int nId, cnn_Msg *msg );
int cwsS_getServerIndex_fromWsCli( ws_cli_conn_t client );
void cwsS_onopen(ws_cli_conn_t client);
void cwsS_onclose(ws_cli_conn_t client);
void *cmInit_wsServer_pthread( void *vargp );
int cmInit_wsServer();
