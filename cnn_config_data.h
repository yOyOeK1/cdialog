
#ifndef CNN_DATA_H
#define CNN_DATA_H

#include "cnn_config_types.h"

extern char *cnn_Version;

extern cnn_Msg cnMs[];
extern int cnMsCount;

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

extern cnn_CanvClear cnn_CanvClears[];
extern int cnn_CanvClearsCount;

extern cnn_CanvPrintf cnn_CanvPrintfs[];
extern int cnn_CanvPrintfsCount;

extern cnn_CanvRender cnn_CanvRenders[];
extern int cnn_CanvRendersCount;

extern cnn_Cmd cnnCmds[];
extern int cnnCmdsCount;



void cmn_test0( int id, int msgPts );


extern cnn_Nudle cnnNudles[];
extern int cnnNudlesCount;

extern cnn_KeyMode cnn_KeyModes[];
extern int cnn_KeyModesCount;
extern int cnn_KeyModeNow;

extern cnn_KeyBind cnn_KeyBinds[];
extern int cnn_KeyBindsCount;

#endif
