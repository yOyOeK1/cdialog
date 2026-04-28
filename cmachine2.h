
/* auto header for [ ./cmachine2.c ] */

void cmachine_start_byNode( struct machNode mn );
void cmiNodeName( char *type, int id, char *name );
int cm_getMsgIndexById( int id );
int cm_getDivIndexById( int id );
void cm_div( int id, int msgId );
int cm_getAddIndexById( int id );
void cm_add( int id, int msgId );
void cm_printf( int id, int msgId );
void cm_cmd( int cmdId, int msgId );
cnn_Msg cm_msgClone( int msgId );
void cm_doClick( int level, int msgId, int srcType, int srcId );
void cmInit_atStart();
void cmInit_cnCanvass();
void cmInit();
void cnn_mqtt_on_message( struct mosquitto *mosq, void *obj, const struct mosquitto_message *message );


