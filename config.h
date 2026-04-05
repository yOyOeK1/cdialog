
/*
// not implemented
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




// not implemented
struct mqttHost mqHosts[] = {
	{ 1, "hu", "192.168.43.1", 10883, "mqttHost4Hu"  },
	//{ 2, "ydell", "127.0.0.1", 10883, "mqttHost4ydel"  },
	{-1}
};

*/


struct mqSub{
	int mqHostId;
	char topic[512];
	char parser[512];
	char args[512];
};
struct mqSub mqSubsN[] = {
	{ 0, "#", 			"%s", "%t: @[%T]->[%M]" },
	{ 0, "e01MuxFix/homeBatPerc", 	"%d", "BAT.oiysh.home: %M %"},
	{-1},
};


int TIME_ZONE_OFFSET = -5 * 60 * 60; // sec

char *mqttHost = "192.168.43.1";
int mqttPort = 10883;
char *mqttClientId = "cDialogTest";

char *mqTopicPrefix = "and/";
char *mqSubs[] = {
	//"#",
	"e01Mux/batSel", // 🔋 🔀
	"e01Mux/left",
	"e01MuxFix/teslaBat0Volt",
	"e01MuxFix/teslaBat1Volt",
	"e01MuxFix/homeBatVolt",
	"hu/#",
	"dell/bat/#",
	"dell/cpu/loadavg",
	"and/#",
	//"e01MuxFix/#",
	0
};

struct mqNode {
	int parentId;
	char title[512];
	char args[512];
	char printAs[512];
	char topic[512];
	char payload[1024];
	int entryDate;
};
struct mqNode mqNodes[] = {
	{0,	"Battery selected",	"%d",		"No# %i\n",	"e01Mux/batSel", 		"",	0 },
	{0,	"🔀 e01Mux switch ...",	"%lf",		"%.0f sec.\n",	"e01Mux/left", 			"",	0 },
	{0,	"Tesla No# 0",		"%lf",		"%.3f vol.\n",	"e01MuxFix/teslaBat0Volt", 	"",	0 },
	{0,	"Tesla No# 1",		"%lf",		"%.3f vol.\n",	"e01MuxFix/teslaBat1Volt", 	"",	0 },
	{0,	"🔋 House battery",	"%lf",		"%.3f vol.\n",	"e01MuxFix/homeBatVolt", 	"",	0 },
	{-1}
};




char *machineName = "yDell";
