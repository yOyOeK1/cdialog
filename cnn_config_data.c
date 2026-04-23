
#include "mqNode.h"
#include "cnn_config_data.h"

cnn_Msg cnMs[] = {
	{.id=1,		.topic="and/test/iterNo",	.payload="0"		},
	{.id=2,		.topic="and/test/iterNo2",	.payload="2"		},
	{-1}
};

MqHost MqHosts[] = {
	{1,	"at hu",	"192.168.43.1",		10883,		"cDialogTest2",		"and/"	},
	{2,	"at local",	"localhost",		10883,		"cDialogTest2",		"and/"	}
};
int MqHostsCount = 2;


#define CNNMQTTSUB 5
cnn_mqttSub cnn_MqttSubs[] = {
	{1,	1,	"and all",		"and/#"		},
	{2,	1,	"switch left",		"e01Mux/left"	},
	{3,	1,	"all",			"e01Mux/#"	}
};
int cnn_MqttSubsCount = 3;
