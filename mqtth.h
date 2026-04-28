
/* auto header for [ ./mqtth.c ] */

void mqttInit( );
void mqttInit2( void *pts_on_message );
void mqttDoIt2();
void mqttDoIt( );
void mqttDestroy( );
void mqtt_publish( char *topic, char *msg );
void mqtth_publish_byHea( struct mosquitto *mqH, char *topic, char *msg );
void *myThread( void *vargp );


