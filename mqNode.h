
struct mqttHost{
	int id;
	char name[512];
	char host[512];
	int port;
	char clientId[512];
};

struct mqSub{
	int mqHostId;
	char topic[512];
	char parser[512];
	char args[512];
};

struct mqNode {
	int parentId;
	char title[512];
	char args[512];
	char postp;
	char printAs[512];
	char topic[512];
	char payload[1024];
	int entryDate;
};

/*  not implemented
struct mqttHost{
	int id;
	char name[512];
	char host[512];
	int port;
	char clientId[512];
	bool connected;
	int mqMosqi;
	bool dogRun;
	pthread_t thread_id;
};
*/
