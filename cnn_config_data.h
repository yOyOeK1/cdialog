
#ifndef CNN_DATA_H
#define CNN_DATA_H

#include "cnn_config_types.h"

#include "cmTime.h"
#include "cmCanvas.h"


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

extern MqHost MqHosts[];
extern int MqHostsCount;

extern cnn_mqttSub cnn_MqttSubs[];
extern int cnn_MqttSubsCount;

extern cnn_MqttPub cnn_MqttPubs[];
extern int cnn_MqttPubsCount;

extern cnn_Canvas cnn_Canvass[];
extern int cnn_CanvassCount;

extern cnn_CanvClear cnn_CanvClears[];
extern int cnn_CanvClearsCount;

extern cnn_CanvPrintf cnn_CanvPrintfs[];
extern int cnn_CanvPrintfsCount;

extern cnn_CanvRender cnn_CanvRenders[];
extern int cnn_CanvRendersCount;

extern cnn_TimeSince cnn_TimeSinces[];
extern int cnn_TimeSincesCount;

extern cnn_ProgressBar cnn_ProgressBars[];
extern int cnn_ProgressBarCount;

extern cnn_Compas cnn_Compass[];
extern int cnn_CompassCount;

extern cnn_Cmd cnnCmds[];
extern int cnnCmdsCount;



void cmn_test0( int id, int msgPts );


extern cnn_Hash cnn_Hashs[];
extern int cnn_HashsCount;

extern cnn_Nudle cnnNudles[];
extern int cnnNudlesCount;

extern cnn_KeyMode cnn_KeyModes[];
extern int cnn_KeyModesCount;
extern int cnn_KeyModeNow;

extern cnn_KeyBind cnn_KeyBinds[];
extern int cnn_KeyBindsCount;

#endif
