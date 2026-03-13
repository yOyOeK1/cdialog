void mqtt_on_connect( struct mosquitto *mosq, void *obj, int result );
void mqtt_on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);
void mqtt_init();

