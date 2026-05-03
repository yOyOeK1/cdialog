
/* auto header for [ ./cmachine2.c ] */

int cm_msg_getIndex_byId( int id );
cnn_Msg cm_msgClone( int msgId );
void cm_div( int id, cnn_Msg *msgT );
void cm_add( int id, cnn_Msg *msgT );
void cm_TimeSince( int tsId, cnn_Msg *msgT );
void cm_ProgressBar( int pId, cnn_Msg *msgT );
void cm_Compas( int nId, cnn_Msg *msgT );
void cmi_timestamp( int id, cnn_Msg *msgT );
void cmi_timeNowTT( int id, cnn_Msg *msgT );
void cm_printf( int id, cnn_Msg *msgT );
void cm_cmd( int cmdId, cnn_Msg *msgT );
void cm_mqttPub( int mqttPubId, cnn_Msg *msgT );
void cm_CanvClear_byId( int ccId );
void cm_CanvClear( int ccId, cnn_Msg *msgT );
int cmCanvPrintf( int ccId, int x, int y, char *msg );
void cm_CanvPrintf( int ccpId, cnn_Msg *msgT );
void cmCanvasRender( int cId );
void cm_CanvRender( int ccrId, cnn_Msg *msgT );
bool cm_doWorkAt( cnn_Msg *msgT, int nType, int nId );
void cm_doClick( int level, int msgId, cnn_Msg msgTp, int srcType, int srcId );
void cmInit();
void cnn_mqtt_on_message( struct mosquitto *mosq, void *obj, const struct mosquitto_message *message );
void cmInit_mqtt();


