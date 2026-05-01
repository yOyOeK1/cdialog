
#include "mqNode.h"
#include "cnn_config_data.h"

char *cnn_Version = "260426_tt11";


cnn_Msg cnMs[] = {
	{.id=1,		.topic="and/test/iterNo",	.payload="0"		},
	{.id=2,		.topic="and/test/iterNo2",	.payload="2"		},
	{.id=3,		.topic="e01Mux/left org",	.payload="1234567890"	},
	{.id=4,		.topic="e01Mux/humidity org"},
	{.id=5,		.topic="and/as/key/bind/test",	.payload="In as payload from key bind test." },
	{.id=6,		.topic="and/as/progress",	.payload="18.11" },
	{-1}
};

cnn_atStart cnnAtStarts[] = {
	/*id		onStart		name*/			
	{1,		true,		"cnn at start",			1  },
	{2,		true,		"cnn battery capacity",		2 },
	{3,		true,		"cnn debug / test",		6 },
	{-1}
};

// ... mqtt connection ... START 
MqHost MqHosts[] = {
	{1,	"at hu",	"192.168.43.1",		10883,		"cDialogTest2",		"and/"	},
	{2,	"at local",	"localhost",		10883,		"cDialogTest2",		"and/"	}
};
int MqHostsCount = 2;


cnn_mqttSub cnn_MqttSubs[] = {
	{1,	1,	"and all",		"and/#"		},
	{2,	1,	"switch left",		"e01Mux/left",		3	},
	{3,	1,	"all",			"e01Mux/#"	},
	{4,	1,	"humidity",		"e01Mux/humidity",	4	},
};
int cnn_MqttSubsCount = 4;
// ... mqtt connection ... END

cnn_Printf cnnPrintfs[] = {
	{1,	"cc print id1",		"Printfs test1 : %s<OK", 		true, -1 },
	{2,	"cc print id2",		"Printfs test2 :%s<OK(2)", 		false, -1 },
	{3,	"cc print id3",		"Printfs test3 :%s<OK( 4.200 ...)", 	false, -1 },
	{4,	"ccp mqttres1",		"Printfs :%s <- payload\n", 		true, -1 },
	{5,	"cprin_humidity",	"%s %% :)\n", 				true, -1 },
	{6,	"For from printf to pts",	"%s pts test \n", 		true, -1 },
	{7,	"Uptime test1",		" | . . .   [ %s min. up ]\n", 			true, -1 },
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
	{3,	"by 60.00",		60.0, -1 },
	{-1}
};
// cnn_MqttSub
// id 5
//
// cnnCmd
// id 6
cnn_Cmd cnnCmds[] = {
	{ 1,	"echo test",		"echo 'Hello from cnnCmds[0] :)'"	},
	{ 2,	"cat uptime",		"cat /proc/uptime"	},
	{ -1 }
};
int cnnCmdsCount = 2;

//
// cnn_MqttPub
// id 8
cnn_MqttPub cnn_MqttPubs[] = {
	{ 1,	1,	"mqtt public hu at" },
	{ -1}
};
int cnn_MqttPubsCount = 1;

cnn_Canvas cnn_Canvass[] = {
	{1,	"debug",	false,	10,	40,	'1'	},
	{2,	"small canvas",	false,	30,	5,	'2'	},
	{3,	"auto canvas",	true,	0,	0,	'3'	},
	{4,	"top banner",	false,	40,	40,	' '	},
	{-1}
};
int cnn_CanvassCount = 4;

//
// cnn_CanvClear
// id 9
cnn_CanvClear cnn_CanvClears[] = {
	/*id,	name,			chFill	canvId	 */
	{ 1,	"clean for test1", 	'-', 	2 	},
	{ -1 }
};
int cnn_CanvClearsCount = 1;

//
// cnn_CanvPrintf
// id 10
cnn_CanvPrintf cnn_CanvPrintfs[] = {
	/*id,	name,		canvId,	x,	y	*/
	{ 1,	"cc printf", 	2,	1,	1  },
	{ -1 }
};
int cnn_CanvPrintfsCount = 1;

// cnn_CanvRender
// id 11
cnn_CanvRender cnn_CanvRenders[] = {
	{ 1,	"Make test render of canv id 2", 	2 	},
	{ -1 }
};
int cnn_CanvRendersCount = 1;

// cnn_TimeSince
// id 12
cnn_TimeSince cnn_TimeSinces[] = {
	{ 1,	"tt uptime", "%lf", " | . . . o o o Uptime:\n"
				    " |                [%s] <- tt test" },
	{ -1 }
};
int cnn_TimeSincesCount = 1;

// cnn_ProgressBar
// id 13
cnn_ProgressBar cnn_ProgressBars[] = {
	{ 1,	"test progress mini",	20,	"%lf",	"\n | . . . test progress mini ...\n | [%s]\n |"	},
	{ -1 }
};
int cnn_ProgressBarsCount = 1;

#include <stdio.h>
void cmn_test0( int id, int msgPts ){
	printf("cmn_test0 id[%i] msgPts[%i]\n", id, msgPts );
}
const int *cmn_test0_pts;
cnn_Nudle cnnNudles[] = {
	{1,	1,		1,	2,		1	},
	{2,	CNNATSTART,	2,	CNNADD,		1	},
	{3,	CNNADD,		1,	CNNPRINTF,	2	},
	{4,	CNNPRINTF,	2,	CNNADD,		2	},
	{5,	CNNADD,		2,	CNNDIV,		1	},
	{6,	CNNDIV,		1,	CNNPRINTF,	3	},
	{7,	CNNMQTTSUB,	2,	CNNPRINTF,	4	},
	{8,	CNNMQTTSUB,	4,	CNNPRINTF,	5	},
	{9,	CNNKEYBIND,	8,	CNNCMD,		2	},
	//{10,	CNNCMD,		2,	CNNDIV,		3	},
	//{11,	CNNDIV,		3,	CNNPRINTF,	7	},

	{12,	CNNKEYBIND,	12,	CNNCMD,		1	},
	{13,	CNNCMD,		1,	CNNPRINTF,	5	},
	{14,	CNNKEYBIND,	13,	CNNPRINTF,	6	},
	{15,	CNNPRINTF,	6,	CNNMQTTPUB,	1	},
//	{15,	CNNPRINTF,	6,	(int)cmn_test0_pts,	1	},

	{16,	CNNKEYBIND,	3,	CNNCANVPRINTF,	1	},


	{17,	CNNKEYBIND,	14,	CNNCANVRENDER,	1	},
	{18,	CNNKEYBIND,	15,	CNNCANVCLEAR,	1	},
	{18,	CNNKEYBIND,	16,	CNNCANVPRINTF,	1	},

	{19,	CNNCMD,		2,	CNNTIMESINCE,	1	},
	{20,	CNNTIMESINCE,	1,	CNNPRINTF,	5	},

	{21,	CNNATSTART,	3,	CNNPROGRESSBAR,	1	},
	{22,	CNNPROGRESSBAR,	1,	CNNPRINTF,	1	},

	{-1}	
};

int cnn_KeyModeNow = 0;
cnn_KeyMode cnn_KeyModes[] = {
	{0,	"root"		},
	{1,	"main"		},
	{2,	"help"		},
	{3,	"main3"		},
	{4,	"main4"		},
	{5,	"DEB_canvas"	},
	{-1}
};

cnn_KeyBind cnn_KeyBinds[] = {
	/*id,	parentId,	keys,	cmdh,			*/	
	{ 1,	 0,		"?",	0,		"help\n%s",		"cat ./configKeys.h | grep -e \"^\t{ 0,\"" },
	{ 2,	 0,		"W",	0,		"ip's:\n%s",		"ip a | grep 'inet ' | awk '{print $2}'" },
	{ 3,	 0,	       "w",	0,		"%s",			"whoami" },
	{ 4,	 0,	       "l",	0,		"load:\n%s",		"cat /proc/loadavg" },
	{ 5,	 0,	       "o",	0,		"cpu's online:\n%s",	"cd /sys/devices/system/cpu && grep '1' ./cpu*/online" },
	{ 6,	 0,	       "\"",	0,		"brightnes +",		"sudo ~/.viteyss/oven/oMachine/brightness.sh +" },
	{ 7,	 0,	       ":",	0,		"brightnes -",		"sudo ~/.viteyss/oven/oMachine/brightness.sh -" },
	{ 8,	 0,	       "u",	0,		"uptime:\n%s",		"uptime | awk '{print $1}'",	5  },
	{ 9,	 0,	       "f",	0,		"%s",			"free -h" },
	
	{ 10,	 0,	       "hh",	0,		"test hh\n\t%s",	"echo HH" },
	{ 11,	 0,	       "mp",	1,		"and/test/perc",	"11.11" },
	{ 12,	 0,	       "c",	0,		"cmd tint",		"",	5  },
	{ 13,	 0,	       "p",	0,		"pts test as func",	"",	5  },
	
	{ 14,	 5,	       "r",	0,		"test render",		"",	5  },
	{ 15,	 5,	       "c",	0,		"test clear",		"",	5  },
	{ 16,	 5,	       "p",	0,		"test printf",		"",	5  },
	
	{-1}
};

