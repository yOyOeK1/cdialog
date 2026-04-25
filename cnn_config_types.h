
#ifndef CNN_TYPES_H
#define CNN_TYPES_H

#include <stdbool.h>

// cnnMsg
typedef struct{
	int id;
	char topic[512];
	char payload[512];
	long tStart;
	long tEnd;
} cnn_Msg;

#define CNNATSTART 1
typedef struct{
	int id;
	bool onStart;
	char name[512];
	int msgId;
} cnn_atStart;

#define CNNPRINTF 2
typedef struct{
	int id;
	char name[512];
	char printAs[512];
	bool doTopic;
	int msgId;
} cnn_Printf;

#define CNNADD 3
typedef struct{
	int id;
	char name[512];
	float add;
	int msgId;
} cnn_Add;

#define CNNDIV 4
typedef struct{
	int id;
	char name[512];
	float divBy;
	int msgId;
} cnn_Div;

#define CNNMQTTSUB 5
typedef struct {
	int id;
	int mqHostId;
	char name[512];
	char topic[512];
	int msgId;
	int entryDate;
} cnn_mqttSub;


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


typedef struct{
	int id;
	int srcType;
	int srcId;
	int targetType;
	int targetId;
} cnn_Nudle;

typedef struct{
	int id;
	char name[512]; 
}cnn_KeyMode;

typedef struct{
	int parentId;
	char ch[51];
	int doWhat; 
	char parser[512];
	char args[512];
}cnn_KeyBind;

#endif
