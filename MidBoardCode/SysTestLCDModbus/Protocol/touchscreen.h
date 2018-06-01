#ifndef __TOUCHSCREEN_H
#define __TOUCHSCREEN_H

#include <stdio.h>
#include "stm32f10x.h"
#include "protocol.h"
#include "Globle.h"

#define TSLENGTH 3      //UI���ݰ�(��ͷ+���ݶ�+��β),��ͷ�ĳ�����3��  ����С��֮���ͨ��

float getAIPhysicalValue(float eletricData,PARAMS par);
float getAOPhysicalValue(float eletricData,PARAMS par);
void TSDataProcess(void);
void TSreadPorts(char* readPortsBuffer);
void TSSentDataGeneration(int length,char* dataBuffer,char* sentBuffer);
int CheckTSReceivedData(char* receivedBuffer);
int TSPacketAnalysis(char * data);
void GetTouchScreenValue(void);

#endif
