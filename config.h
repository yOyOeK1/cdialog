

#ifndef CCONFIGSET
//---------------------------------------------------------
#define CCONFIGSET 

char *machineName = "yDell";

// at pinebook pro offset is
int TIME_ZONE_OFFSET = 0;// sec
// at dell yoyo
//int TIME_ZONE_OFFSET = -5 * 60 * 60; // sec


//--------------------------- Mqtt
#include "mqNode.h"

char *mqttHost = "192.168.43.1";
int mqttPort = 10883;
char *mqttClientId = "cDialogTest";
char *mqTopicPrefix = "and/";


struct mqSub mqSubsN[] = {
	{ 0, "#", 			"%s", "%t: @[%T]->[%M]" },
	{ 0, "e01MuxFix/homeBatPerc", 	"%d", "BAT.oiysh.home: %M %"},
	{-1},
};

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

struct mqNode mqNodes[] = {
	{0,	"🔛 Tesla selected",	"%d",	' ',		"No# %i\n",		"e01Mux/batSel", 		"",	0 },
	
	{0,	"🔀 e01Mux switch ...",	"%lf",	't',		"%s\n",			"e01Mux/left", 			"",	0 },
	//{0,	"🔀 e01Mux switch ...",	"%lf",	' ',		"%.0f sec.\n",		"e01Mux/left", 			"",	0 },
	
	{0,	/*Tesla */" - No# 0",	"%lf",	' ',		"%.3f vol.\n",		"e01MuxFix/teslaBat0Volt", 	"",	0 },
	{0,	/*Tesla */" - No# 1",	"%lf",	' ',		"%.3f vol.\n",		"e01MuxFix/teslaBat1Volt", 	"",	0 },
	
	{0,	"🔋 House battery",	"%lf",	' ',		"%.3f vol.\n",		"e01MuxFix/homeBatVolt", 	"",	0 },
	{0,	"🔋 House percent",	"%lf",	'p',		"[%s]\n",			"e01MuxFix/homeBatPerc", 	"",	0 },
	//{0,	"🔋 House percent",	"%lf",	' ',		"%.1f %%\n",		"e01MuxFix/homeBatPerc", 	"",	0 },
	
	{0,	"percent test ",	"%lf",	'p',		"* [%s] as str\n",	"and/test/perc",	 	"",	0 },
	
	{-1}
};


/*// not implemented
struct mqttHost mqHosts[] = {
	{ 1, "hu", "192.168.43.1", 10883, "mqttHost4Hu"  },
	//{ 2, "ydell", "127.0.0.1", 10883, "mqttHost4ydel"  },
	{-1}
};

--- not implemented */
#endif


