
#ifndef CNN_TYPES_H
#define CNN_TYPES_H

// cnnMsg
typedef struct{
	int id;
	char topic[512];
	char payload[512];
	long tStart;
	long tEnd;
} cnn_Msg;


#include <mosquitto.h>
typedef struct {
	int id;
	char name[512]; 
	char *host;
	int port;
	char *chlientId;
	char *topicPrefix;

	struct mosquitto *mqMosqi;
	struct mosquitto *mqHeader;

} MqHost;

typedef struct {
	int id;
	int mqHostId;
	char name[512];
	char topic[512];
	int entryDate;
} cnn_mqttSub;

#endif
