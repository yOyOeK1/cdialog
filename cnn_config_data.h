
#ifndef CNN_DATA_H
#define CNN_DATA_H

#include "cnn_config_types.h"

#include "cmTime.h"
#ifdef CM_DO_INIT_CANVAS
#include "cmCanvas.h"
#endif
#include "cmMath.h"
#include "cmAs.h"
#include "cmLogic.h"

extern bool cmtDeb_verbose;
extern bool cmtBen;

extern char *cnn_name;
extern char *cnn_target;
extern char *cnn_Version;

extern cnn_Msg cnMs[];
extern int cnMsCount;


extern machNode machNs[];

extern cnn_atStart cnnAtStarts[];
extern int cnnAtStartsCount;

extern cnn_Printf cnnPrintfs[];
extern int cnnPrintfsCount;

extern cnn_Add cnnAdds[];
extern int cnnAddsCount;

extern cnn_Div cnnDivs[];
extern int cnnDivsCount;

#ifdef CM_DO_INIT_MQTT
extern MqHost MqHosts[];
extern int MqHostsCount;

extern cnn_mqttSub cnn_MqttSubs[];
extern int cnn_MqttSubsCount;

extern cnn_MqttPub cnn_MqttPubs[];
extern int cnn_MqttPubsCount;
#endif

#ifdef CM_DO_INIT_WSSERVER
extern cnn_wsSPub cnn_wsSPubs[];
extern int cnn_wsSPubsCount;

extern cnn_wsServer cnn_wsServers[];
extern int cnn_wsServersCount;
#endif

#ifdef CM_DO_INIT_TCPSERVER
extern cnn_tcpServer cnn_tcpServers[];
extern int cnn_tcpServersCount;
#endif

#ifdef CM_DO_INIT_CANVAS
extern cnn_Canvas cnn_Canvass[];
extern int cnn_CanvassCount;

extern cnn_CanvClear cnn_CanvClears[];
extern int cnn_CanvClearsCount;

extern cnn_CanvPrintf cnn_CanvPrintfs[];
extern int cnn_CanvPrintfsCount;

extern cnn_CanvRender cnn_CanvRenders[];
extern int cnn_CanvRendersCount;
#endif

extern cnn_TimeSince cnn_TimeSinces[];
extern int cnn_TimeSincesCount;

extern cnn_ProgressBar cnn_ProgressBars[];
extern int cnn_ProgressBarCount;

extern cnn_Compas cnn_Compass[];
extern int cnn_CompassCount;

extern cnn_if cnn_ifs[];
extern int cnn_ifsCount;

extern cnn_Cmd cnnCmds[];
extern int cnnCmdsCount;



void cmn_test0( int id, int msgPts );


extern cnn_Hash cnn_Hashs[];
extern int cnn_HashsCount;

extern cnn_Nudle cnnNudles[];
extern int cnnNudlesCount;

#ifdef CM_DO_INIT_KEYBIND
extern cnn_KeyMode cnn_KeyModes[];
extern int cnn_KeyModesCount;

extern int cnn_KeyModeNow;

extern cnn_KeyBind cnn_KeyBinds[];
extern int cnn_KeyBindsCount;
#endif

#endif
