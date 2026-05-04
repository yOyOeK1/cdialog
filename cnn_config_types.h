
#ifndef CNN_TYPES_H
#define CNN_TYPES_H

#define CM_DO_INIT_CANVAS 1
#define CM_DO_INIT_MQTT 1
#define CM_DO_INIT_KEYBIND 1

#define CNITIMESTAMP 15
#define CNITIMENOWTT 16
#define CNRDUMPMSG 18

#include <stdbool.h>


// cnnMsg
typedef struct{
	int id;
	char topic[512];
	char payload[512];
	bool asVar;
	long tStart;
	long tEnd;
	int nIndex;
} cnn_Msg;


typedef struct{
	int id;
	bool onStart;
	long everyMs;
	char name[512];
	int typeOf; // 0 - cmd
	char cmd[512];
	char result[512];
	bool isRunning;
} machNode;

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

#define CNNCMD 6
typedef struct {
	int id;
	char name[512];
	char cmd[512];

} cnn_Cmd;


#define CNNMQTTPUB 8
typedef struct{
	int id;
	int mqHostId;
	char name[512];
} cnn_MqttPub;


// cnn_Canvas
typedef struct{
	int id;
	char name[512];
	bool autoSize;
	int col;
	int row;
	char ch;
	char *ccFB;
	int pCount;
} cnn_Canvas;

#define CNNCANVCLEAR 9
typedef struct{
	int id;
	char name[512];
	char chf;
	int canvId;
} cnn_CanvClear;

#define CNNCANVPRINTF 10
typedef struct{
	int id;
	char name[512];
	int canvId;
	int x;
	int y;
} cnn_CanvPrintf;

#define CNNCANVRENDER 11
typedef struct{
	int id;
	char name[512];
	int canvId;
	unsigned int count;
} cnn_CanvRender;

#define CNNTIMESINCE 12
typedef struct{
	int id;
	char name[512];
	char parseArg[512];
	char printAs[512];
} cnn_TimeSince;

#define CNNPROGRESSBAR 13
typedef struct{
	int id;
	char name[512];
	int width;
	char parseArg[512];
	char printAs[512];
} cnn_ProgressBar;

#define CNNCOMPAS 14
typedef struct{
	int id;
	char name[512];
	int width;
	bool inCompasView;
	int angEvery;
	char parseArg[512];
	char printAs[512];
} cnn_Compas;

#define CNLIF 17
#define CNLIF_EQUAL '='
#define CNLIF_DIFRENT '!'
typedef struct{
	int id;
	char name[512];
	char ifType;
	char vThen[512];
} cnn_if;

typedef struct{
	int id;
	char name[512];
	int nType;
	bool isNode;
	void (*fPts)( int, cnn_Msg* );
} cnn_Hash;

typedef struct{
	int id;
	int srcType;
	int srcId;
	int targetType;
	int targetId;
	int srcChNo;
} cnn_Nudle;

typedef struct{
	int id;
	char name[512]; 
}cnn_KeyMode;

#define CNKEY_CMD 0
#define CNKEY_MQTTPUSH 1
#define CNKEY_NUDLE 2
#define CNNKEYBIND 7
typedef struct{
	int id;
	int parentId;
	char keys[51];
	int workType; 
	char parser[512];
	char args[512];
	int msgId;
}cnn_KeyBind;


#endif
