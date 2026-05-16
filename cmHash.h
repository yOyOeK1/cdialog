

#include "cnn_config_data.h"
#include <stdio.h>
#ifdef CM_DO_INIT_WSSERVER
#include <ws.h>
#include "cwsS.h"
#endif
#include "cmachine2.h"
#include "cmTools.h"
#include "cmCore.h"
#include "ckeyh.h"
#ifdef CM_DO_INIT_TCPSERVER
#include "ctcpS.h"
#endif




cnn_Hash cnn_Hashs[] = {
	{ 1,	"At start",		CNNATSTART, 	false,	0		},
#ifdef CM_DO_INIT_MQTT
	{ 5,	"mqtt sub",		CNNMQTTSUB,	false,	0		},
#endif
	{ 7,	"key bind",		CNNKEYBIND,	false,	0 		},
	
	{ 2,	"Printf",		CNNPRINTF,	true,	&cm_printf 	},
	{ 6,	"Cmd",			CNNCMD,		true,	&cm_cmd 	},
#ifdef CM_DO_INIT_MQTT
	{ 8,	"mqtt publish",		CNNMQTTPUB,	true,	&cm_mqttPub 	},
#endif

	{ 3,	"Add",			CNNADD,		true,	&cm_add		},
	{ 4,	"Divide",		CNNDIV,		true,	&cm_div 	},
	{ 12,	"as Time since",	CNNTIMESINCE,	true,	&cm_TimeSince 	},
	{ 13,	"as Progress bar",	CNNPROGRESSBAR,	true,	&cm_AsProgressBar 	},
	{ 14,	"as Compas",		CNNCOMPAS,	true,	&cm_AsCompas 	},
#ifdef CM_DO_INIT_CANVAS
	{ 9,	"Canvas clear",		CNNCANVCLEAR,	true,	&cm_CanvClear 	},
	{ 10,	"Canvas printf",	CNNCANVPRINTF,	true,	&cm_CanvPrintf 	},
	{ 11,	"Canvas render",	CNNCANVRENDER,	true,	&cm_CanvRender 	},
#endif
	{ 15,	"Get time stamp",	CNITIMESTAMP,	true,	&cmi_timeStamp	},
	{ 16,	"Get time now tt",	CNITIMENOWTT,	true,	&cmi_timeNowTT	},

	{ 17,	"Logic - compale",	CNLIF,		true,	&cml_if		},
	
	{ 18,	"Dump - msg's",		CNRDUMPMSG,	true,	&cmt_dump_msgs	},

	{ 19,	"Debug on",		CNRDEBUGON,	true,	&cmt_debug_on},
	{ 20,	"Debug off",		CNRDEBUGOFF,	true,	&cmt_debug_off},
#ifdef CM_DO_MOUSEKEYS
	{ 21,	"Mouse on",		CNIKEYMOUSE_ENABLE,	true,	&key_mouseKey_enable_byNode	},
	{ 22,	"Mouse off",		CNIKEYMOUSE_DISABLE,	true,	&key_mouseKey_disable_byNode	},
#endif
	{ 23,	"At mouseKey event",	CNNINPUTEVENT,	false,	0		},
#ifdef CM_DO_INIT_TCPSERVER
	{ 24,	"TCP Server",		CNNTCPSERVER,	false,	0		},
	{ 25,	"TCP Server - write",	CNNTCPSPUB,	true,	&cnn_tcpServer_pub	},
	{ 26,	"TCP Server - disconnect",	
					CNNTCPSDISCONNECT,	
							true,	&cnn_tcpServer_disconnect	},
	{ 27,	"TCP Server - clients",	CNNTCPSCLIENTS,	true,	&cnn_tcpServer_clients		},
#endif
#ifdef CM_DO_INIT_WSSERVER
	{ 28,	"WS Server",		CNNWSSERVER,	false,	0		},
	{ 29,	"WS Server - write",	CNNWSSPUB,	true,	&cnn_wsServer_pub	},
#endif	
	{ -1 }
}; 
int cnn_HashsCount = 23;



