#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdio.h>

#define LENGTH  10      //数据包（包头+数据段+包尾）的包头长度为 10，上位机通信

///////////////////////////////////////////////
//	数据包头的组成(unit: byte)
//	address1,
//  address2,
//  address3,
//  address4,
//	stagesel,
//  functionsel,
//  checkcode,
//  length_h,
//  length_l,
//  reserved
//////////////////////////////////////////////

int PacketHeaderAnalysis(char * data);
void PacketHeaderState(char * data);
void SentDataGeneration(int length,char* dataBuffer,char* sentBuffer);
int  CheckReceivedData(char* receivedBuffer);
char checkSentData(int length,char* dataBuffer);
char getIntHighByte(float data);
char getIntLowByte(float data);
char getDecHighByte(float data);
char getDecLowByte(float data);

#endif /*PROTOCOL_H*/

   
