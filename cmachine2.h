/* file: [ ./cmachine2.c ] */
int cm_msg_getIndex_byId( int id );
cnn_Msg cm_msgClone( int msgId );
void cm_printf( int id, cnn_Msg *msgT );
void cm_cmd( int cmdId, cnn_Msg *msgT );
void cm_mqttPub( int mqttPubId, cnn_Msg *msgT );
bool cm_doWorkAt( int level, cnn_Msg *msgT, int nIndex, int nType, int nId );
void cm_doClick_opts( int level, int msgId, cnn_Msg msgTp, int srcType, int srcId, int niStart );
void cm_doWorkAt_byNId( int nId, int nType, int chaNo, cnn_Msg *msgT );
void cm_doClick( int level, int msgId, cnn_Msg msgTp, int srcType, int srcId );
void cmInit();
void cnn_mqtt_on_message( struct mosquitto *mosq, void *obj, const struct mosquitto_message *message );
void cmInit_mqtt();
