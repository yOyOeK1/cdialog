

#ifndef CCONFIGSET
//---------------------------------------------------------
#define CCONFIGSET "1"

char *machineName = "yDell";

// at pinebook pro offset is
int TIME_ZONE_OFFSET = 0;// sec
// at dell yoyo
//int TIME_ZONE_OFFSET = -5 * 60 * 60; // sec


//--------------------------- Mqtt
#include "mqNode.h"
#include <stdbool.h>

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
	{0,	"Temp",			"%lf",	' ',		"%.1f'C\n",		"e01Mux/C", 			"",	0 },
	{0,	"Humidity",		"%lf",	' ',		"%.0f%%\n",		"e01Mux/humidity", 		"",	0 },
	{0,	"🔛 Tesla selected",	"%s",	' ',		"No# %s\n",		"e01Mux/batSel", 		"",	0 },
	
	{0,	"🔀 e01Mux switch ...",	"%lf",	't',		"%s\n",			"e01Mux/left", 			"",	0 },
	//{0,	"🔀 e01Mux switch ...",	"%lf",	' ',		"%.0f sec.\n",		"e01Mux/left", 			"",	0 },
	
	{0,	/*Tesla */" - No# 0",	"%lf",	' ',		"%.3f vol.\n",		"e01MuxFix/teslaBat0Volt", 	"",	0 },
	{0,	/*Tesla */" - No# 1",	"%lf",	' ',		"%.3f vol.\n",		"e01MuxFix/teslaBat1Volt", 	"",	0 },
	
	{0,	"🔋 House battery",	"%lf",	' ',		"%.3f vol.\n",		"e01MuxFix/homeBatVolt", 	"",	0 },
	{0,	"🔋 House percent",	"%lf",	'p',		"[%s]\n",		"e01MuxFix/homeBatPerc", 	"",	0 },
	{0,	"🔋 Huawei percent",	"%lf",	'p',		"[%s]\n",		"hu/bat/percent",	 	"",	0 },
	//{0,	"🔋 House percent",	"%lf",	' ',		"%.1f %%\n",		"e01MuxFix/homeBatPerc", 	"",	0 },
	
	{0,	"percent test ",	"%lf",	'p',		"* [%s] as str\n",	"and/test/perc",	 	"",	0 },
	{0,	"percent test 2",	"%s",	' ',		"[%s]\n",		"and/test/str",		 	"",	0 },
	
	{0,	"GPS",			"%s",	' ',		"[%s]\n",			"nex7/gps/ll",		 	"",	0 },
	
	{-1}
};

struct machNode{
	int id;
	bool onStart;
	long everyMs;
	char name[512];
	int typeOf; // 0 - cmd
	char cmd[512];
	char result[512];
	bool isRunning;
};

struct machNode machNs[] = {
//	id		onStart		everyMs		name			typeOf	cmd
	{1,		true,		0,		"at start", 		0,	"date"		},
	{2,		true,		1000,		"1sec iter at start", 	0,	"echo 'ping'"		},
	{3,		true,		0,		"battery capacity", 	0,	"cat /sys/class/power_supply/*/capacity"		},
	{4,		true,		0,		"loadavg", 		0,	"cat /proc/loadavg"		},
	{5,		true,		0,		"hostname", 		0,	"hostname"		},
	{6,		true,		0,		"mem used", 		0,	"free | grep Mem | awk '{print $3}'"		},
	{7,		true,		0,		"ps count", 		0,	"ps x | wc -l"		},
	{8,		true,		0,		"interfaces", 		0,	"ip a | grep -e ': ' -e 'inet ' | awk '{print $2}'"	},
	{9,		true,		0,		"uptime", 		0,	"cat /proc/uptime"	},
	{10,		true,		0,		"at start", 		0,	"date"		},
	{11,		false,		0,		"test none", 		0,	"echo 'none'"		},
	{-1}
};

// -- C NODE NUDDLE FLOW START
//

// cnnMsg
struct cnn_Msg{
	int id;
	char topic[512];
	char payload[512];
	long tStart;
	long tEnd;
};
struct cnn_Msg cnMs[] = {
	{.id=1,		.topic="and/test/iterNo",	.payload="0"		},
	{.id=2,		.topic="and/test/iterNo2",	.payload="2"		},
	{-1}
};
// cnnCanvas
struct cnn_Canvas{
	int id;
	char name[512];
	bool autoSize;
	int col;
	int row;
	char ch;
	char *ccFB;
	int pCount;
};
struct cnn_Canvas cnCanvass[] = {
	{1,	"debug",	false,	10,	40,	'1'	},
	{2,	"small canvas",	false,	30,	5,	'2'	},
	{3,	"auto canvas",	true,	0,	0,	'3'	},
	{4,	"top banner",	false,	40,	40,	' '	},
	{-1}
};


// cnnAtStart
// id 1
#define CNNATSTART 1
struct cnn_atStart{
	int id;
	bool onStart;
	char name[512];
	int msgId;
};
struct cnn_atStart cnnAtStarts[] = {
	/*id		onStart		name*/			
	{1,		true,		"cnn at start",			1  },
	{2,		true,		"cnn battery capacity",		2 },
	{-1}
};

// cnnPrintf
// id 2
#define CNNPRINTF 2
struct cnn_Printf{
	int id;
	char name[512];
	char printAs[512];
	bool doTopic;
	int msgId;
};
struct cnn_Printf cnnPrintfs[] = {
	{1,	"cc print id1",	"Printfs test1 : %s<OK", true, -1 },
	{2,	"cc print id2",	"Printfs test2 :%s<OK(2)", false, -1 },
	{3,	"cc print id3",	"Printfs test3 :%s<OK(3)", false, -1 },
	{-1}
};
// cnnAdd
// id 3
#define CNNADD 3
struct cnn_Add{
	int id;
	char name[512];
	float add;
	int msgId;
};
struct cnn_Add cnnAdds[] = {
	{1,	"cc add test 1.1",	1.1, -1 },
	{2,	"cc add test 3.2",	3.2, -1 },
	{-1}
};
// cnnDiv
// id 4
#define CNNDIV 4
struct cnn_Div{
	int id;
	char name[512];
	float divBy;
	int msgId;
};
struct cnn_Div cnnDivs[] = {
	{1,	"cc div test 1.5",	1.5, -1 },
	{2,	"cc div test 4.0",	4.0, -1 },
	{-1}
};
// cnnNudle
struct cnn_Nudle{
	int id;
	int srcType;
	int srcId;
	int targetType;
	int targetId;
};
struct cnn_Nudle cnnNudles[] = {
	{1,	1,		1,	2,		1	},
	{2,	CNNATSTART,	2,	CNNADD,		1	},
	{3,	CNNADD,		1,	CNNPRINTF,	2	},
	{4,	CNNPRINTF,	2,	CNNADD,		2	},
	{5,	CNNADD,		2,	CNNDIV,		1	},
	{5,	CNNDIV,		1,	CNNPRINTF,	3	},
	{-1}	
};


//
// -- C NODE NUDDLE FLOW END

/*// not implemented
struct mqttHost mqHosts[] = {
	{ 1, "hu", "192.168.43.1", 10883, "mqttHost4Hu"  },
	//{ 2, "ydell", "127.0.0.1", 10883, "mqttHost4ydel"  },
	{-1}
};

--- not implemented */
#endif


