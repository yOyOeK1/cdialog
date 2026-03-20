

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

struct mqSub{
	int mqHostId;
	char topic[512];
	char parser[512];
	char args[512];
};




struct mqttHost mqHosts[] = {
	{ 1, "hu", "192.168.43.1", 10883, "mqttHost4Hu"  },
	{ 2, "ydell", "127.0.0.1", 10883, "mqttHost4ydel"  },
	{-1}
};


struct mqSub mqSubsN[] = {
	{ 0, "#", 			"%s", "%t: @[%T]->[%M]" },
	{ 0, "e01MuxFix/homeBatPerc", 	"%d", "BAT.oiysh.home: %M %"},
	{-1}
};


int TIME_ZONE_OFFSET = -5 * 60 * 60; // sec

char *mqttHost = "192.168.43.1";
int mqttPort = 10883;
char *mqttClientId = "cDialogTest";

char *mqTopicPrefix = "and/";
char *mqSubs[] = {
	//"#",
	"hu/#",
	"dell/bat/#",
	"dell/cpu/loadavg",
	"and/#",
	"e01MuxFix/#",
	0
};

char *machineName = "yDell";
