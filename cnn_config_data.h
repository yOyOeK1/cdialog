
#ifndef CNN_DATA_H
#define CNN_DATA_H

#include "cnn_config_types.h"

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

extern cnn_Nudle cnnNudles[];
extern int cnnNudlesCount;

#endif
