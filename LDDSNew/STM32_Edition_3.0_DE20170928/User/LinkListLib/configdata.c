//#include "configdata.h"
// 
//DATAPACK MainDataPack[MAINBOXMAX];    
//DATAPACK SubDataPack[SUBBOXMAX];
////volatile MODESEL ModeSel = STOP; 
////////////////////////////////////////////////////////////////////
/////<功能描述>对存储区数据进行解析--数据包结构转换
/////<参数1>maindatapack 存储数组解析后生成的的主线程的数据包
/////<参数2>subdatapack  存储数组解析后生成的的子线程的数据包
/////<返回值>返回1--解析成功，0--解析失败
////////////////////////////////////////////////////////////////////
//int DataAnalysis(char* receivedData)
//{
//	int i,j = 0;
//    int switchFlag = 1;	//主线程/子线程数据标志位 1--主 0--子
//	int mainDataPackNum,subDataPackNum;
//	char mainData[MAINBOXMAX*NUM];
//	char subData[SUBBOXMAX*NUM];
//
//   for(i=0;i<(MAINBOXMAX+SUBBOXMAX)*NUM;i++)
//   {
//      if((receivedData[i] & receivedData[i+1] & 0xff) != 0xff) 
//	  {
//	     if(i%NUM == 0 && receivedData[i] == FIDENTRYNODE)
//		    switchFlag = 0;
//
//		 if(switchFlag)
//		   mainData[i] = receivedData[i];
//		 else
//		   subData[j++] = receivedData[i]; 
//	  }
//	  else
//	    break;
//   }
//   
//   if(i!= 0 && i%NUM == 0 && j%NUM == 0)
//   {
//     mainDataPackNum = i/NUM - j/NUM;
//	 subDataPackNum	= j/NUM;
//   }
//   else
//	 return 0;
//
//    for(i=0;i<mainDataPackNum;i++)
//	{
//	    maindatapack[i].fid   = mainData[i*NUM+0];
//		maindatapack[i].port  = mainData[i*NUM+1];
//		maindatapack[i].flag1 = mainData[i*NUM+2];
//		maindatapack[i].flag2 = mainData[i*NUM+3];
//		maindatapack[i].flag3 = mainData[i*NUM+4];
//		maindatapack[i].par1  = (mainData[i*NUM+5]&0x7f)*100 + mainData[i*NUM+6] + mainData[i*NUM+7]/100.0 + mainData[i*NUM+8]/10000.0;
//		maindatapack[i].par2  = (mainData[i*NUM+9]&0x7f)*100 + mainData[i*NUM+10] + mainData[i*NUM+11]/100.0 + mainData[i*NUM+12]/10000.0;
//		maindatapack[i].par3  = (mainData[i*NUM+13]&0x7f)*100 + mainData[i*NUM+14] + mainData[i*NUM+15]/100.0 + mainData[i*NUM+16]/10000.0;
//		maindatapack[i].index  = mainData[i*NUM+17] + mainData[i*NUM+18]/100.0;
//		if(mainData[i*NUM+5]&0x80) maindatapack[i].par1 *= -1;
//		if(mainData[i*NUM+9]&0x80) maindatapack[i].par2 *= -1;
//		if(mainData[i*NUM+13]&0x80) maindatapack[i].par3 *= -1;
//	}
//
//	for(j=0;j<subDataPackNum;j++)
//	{
//   	    subdatapack[j].fid      = subData[j*NUM+0]  & 0xff;
//		subdatapack[j].port     = subData[j*NUM+1]  & 0xff;
//		subdatapack[j].flag1    = subData[j*NUM+2]  & 0xff;
//		subdatapack[j].flag2    = subData[j*NUM+3]  & 0xff;
//		subdatapack[j].flag3    = subData[j*NUM+4]  & 0xff;
//		subdatapack[j].par1  = (subData[j*NUM+5]&0x7f)*100 + subData[j*NUM+6] + subData[j*NUM+7]/100.0 + subData[j*NUM+8]/10000.0;
//		subdatapack[j].par2  = (subData[j*NUM+9]&0x7f)*100 + subData[j*NUM+10] + subData[j*NUM+11]/100.0 + subData[j*NUM+12]/10000.0;
//		subdatapack[j].par3  = (subData[j*NUM+13]&0x7f)*100 + subData[j*NUM+14] + subData[j*NUM+15]/100.0 + subData[j*NUM+16]/10000.0;
//		subdatapack[j].index  = subData[j*NUM+17] + subData[j*NUM+18]/100.0;
//		if(subData[j*NUM+5]&0x80) subdatapack[j].par1 *= -1;
//		if(subData[j*NUM+9]&0x80) subdatapack[j].par2 *= -1;
//		if(subData[j*NUM+13]&0x80) subdatapack[j].par3 *= -1;
//	}
//	return 1;
//}
//
//
