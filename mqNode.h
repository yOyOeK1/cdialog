
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


