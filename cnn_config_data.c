
#include "mqNode.h"
#include "cnn_config_data.h"

char *cnn_Version = "260425_tt10";


cnn_Msg cnMs[] = {
	{.id=1,		.topic="and/test/iterNo",	.payload="0"		},
	{.id=2,		.topic="and/test/iterNo2",	.payload="2"		},
	{.id=3,		.topic="e01Mux/left org",	.payload="1234567890"	},
	{.id=4,		.topic="e01Mux/humidity org"},
	{-1}
};

cnn_atStart cnnAtStarts[] = {
	/*id		onStart		name*/			
	{1,		true,		"cnn at start",			1  },
	{2,		true,		"cnn battery capacity",		2 },
	{-1}
};

// ... mqtt connection ... START 
MqHost MqHosts[] = {
	{1,	"at hu",	"192.168.43.1",		10883,		"cDialogTest2",		"and/"	},
	{2,	"at local",	"localhost",		10883,		"cDialogTest2",		"and/"	}
};
int MqHostsCount = 2;


#define CNNMQTTSUB 5
cnn_mqttSub cnn_MqttSubs[] = {
	{1,	1,	"and all",		"and/#"		},
	{2,	1,	"switch left",		"e01Mux/left",		3	},
	{3,	1,	"all",			"e01Mux/#"	},
	{4,	1,	"humidity",		"e01Mux/humidity",	4	},
};
int cnn_MqttSubsCount = 4;
// ... mqtt connection ... END

cnn_Printf cnnPrintfs[] = {
	{1,	"cc print id1",		"Printfs test1 : %s<OK", 	true, -1 },
	{2,	"cc print id2",		"Printfs test2 :%s<OK(2)", 	false, -1 },
	{3,	"cc print id3",		"Printfs test3 :%s<OK(3)", 	false, -1 },
	{4,	"ccp mqttres1",		"Printfs :%s <- payload\n", 	true, -1 },
	{5,	"cprin_humidity",	"%s %% :)\n", 			true, -1 },
	{-1}
};
// cnnAdd
// id 3
cnn_Add cnnAdds[] = {
	{1,	"cc add test 1.1",	1.1, -1 },
	{2,	"cc add test 3.2",	3.2, -1 },
	{-1}
};
// cnnDiv
// id 4
cnn_Div cnnDivs[] = {
	{1,	"cc div test 1.5",	1.5, -1 },
	{2,	"cc div test 4.0",	4.0, -1 },
	{-1}
};

cnn_Nudle cnnNudles[] = {
	{1,	1,		1,	2,		1	},
	{2,	CNNATSTART,	2,	CNNADD,		1	},
	{3,	CNNADD,		1,	CNNPRINTF,	2	},
	{4,	CNNPRINTF,	2,	CNNADD,		2	},
	{5,	CNNADD,		2,	CNNDIV,		1	},
	{6,	CNNDIV,		1,	CNNPRINTF,	3	},
	{7,	CNNMQTTSUB,	2,	CNNPRINTF,	4	},
	{8,	CNNMQTTSUB,	4,	CNNPRINTF,	5	},
	{-1}	
};

int cnn_KeyModeNow = 0;
cnn_KeyMode cnn_KeyModes[] = {
	{0,	"root"		},
	{1,	"main"		},
	{2,	"help"		},
	{3,	"main3"		},
	{4,	"main4"		},
	{-1}
};

cnn_KeyBind cnn_KeyBinds[] = {
	/*id,	key,	cmdh,			*/	
	{ 1,	 0, 	"?",	0,		"help\n%s",		"cat ./configKeys.h | grep -e \"^\t{ 0,\"" },
	{ 2,	 0, 	"W",	0,		"ip's:\n%s",		"ip a | grep 'inet ' | awk '{print $2}'" },
	{ 3,	 0,    "w",	0,		"%s",			"whoami" },
	{ 4,	 0,    "l",	0,		"load:\n%s",		"cat /proc/loadavg" },
	{ 5,	 0,    "o",	0,		"cpu's online:\n%s",	"cd /sys/devices/system/cpu && grep '1' ./cpu*/online" },
	{ 6,	 0,    "\"",	0,		"brightnes +",		"sudo ~/.viteyss/oven/oMachine/brightness.sh +" },
	{ 7,	 0,    ":",	0,		"brightnes -",		"sudo ~/.viteyss/oven/oMachine/brightness.sh -" },
	{ 8,	 0,    "u",	0,		"uptime:\n%s",		"uptime | awk '{print $1}'" },
	{ 9,	 0,    "f",	0,		"%s",			"free -h" },
	
	{ 10,	 0,    "hh",	0,		"test hh\n\t%s",	"echo HH" },
	{ 11,	 0,    "mp",	1,		"and/test/perc",	"11.11" },
	
	{-1}
};

