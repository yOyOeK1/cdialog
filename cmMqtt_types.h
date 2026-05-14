
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

