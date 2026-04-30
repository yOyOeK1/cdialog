
/* auto header for [ ./cmachine2.c ] */

void cmachine_start_byNode( struct machNode mn );
void cmiNodeName( char *type, int id, char *name );
int cm_msg_getIndex_byId( int id );
cnn_Msg cm_msgClone( int msgId );
void cm_div( int id, cnn_Msg *msgT );
void cm_add( int id, cnn_Msg *msgT );
void cm_printf( int id, cnn_Msg *msgT );
void cm_cmd( int cmdId, cnn_Msg *msgT );
void cm_mqttPub( int mqttPubId, cnn_Msg *msgT );
void cm_CanvClear_byId( int ccId );
void cm_CanvClear( int ccId, cnn_Msg *msgT );
void cm_CanvPrintf( int ccpId, cnn_Msg *msgT );
bool cm_doWorkAt( cnn_Msg *msgT, int nType, int nId );
void cm_doClick( int level, int msgId, cnn_Msg msgTp, int srcType, int srcId );
void cmInit_cnnAtStart();
void cmInit_cnCanvass();
void cmCanvasRender( int cId );
void cmInit();
void cnn_mqtt_on_message( struct mosquitto *mosq, void *obj, const struct mosquitto_message *message );
void cmInit_machNs();
void cmInit_mqtt();


