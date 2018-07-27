#ifndef __COTROLLERDESIGN_H
#define __COTROLLERDESIGN_H


#define CS_VAL		 ((float)0x0000) //cooling source adjustment basic value	
#define CS_STEP_VAL  ((float)0x0000) //cooling source adjustment step value	

#define FR_VAL	     ((float)0x0000) //flowrate adjustment basic value
#define FR_STEP_VAL	 ((float)0x0000) //flowrate adjustment step value


#define  FR_ACCRCY	 ((float)0x0000)   //followrate accuarcy  
#define  STRT_T_PUMP ((u8)0x0001)	   //transfer pump start 
#define  DE_APP_LEVEL	 ((u8)0x0001)  //appropriate liquid level

#define  STRT_SV3   	 ((u8)0x0001)	 // open sv3 
#define  STRT_TO_PUMP	 ((u8)0x0001)	 // optional pump replace sv3
#define  SV3ORPUMP		 ((u8)0x0001)	 // configuration of sv3/pump system
/*  00:SV3
    01:PUMP
	02:SV3&PUMP
*/



#define  DELIQMAX  	     ((u8)0x0000)	  //dehumidifer maximum liquid level
#define  DELIQMIN	     ((u8)0x0000)	  //dehumidifer minimum liquid level

#define  TEMPMIN		 ((u8)0x0000)	  // adjustment temperature threshold
#define  FLOWMAX		 ((u8)0x0000)	  // adjustment flowrate threshold

#define  ST_APP_LEVEL	 ((u8)0x0001) 	 //strong solution tank	approprated level
#define  DT_APP_LEVEL	 ((u8)0x0001)    //diluted solution tank approprated level



#define DECPUMPFBCHAN 1//除湿循环泵反馈端口
#define DECPUMPDEF    1//除湿循环泵默认值
//#define DEPUMPFREQR   1//除湿泵频率范围
#define DECPUMPSTOP	  1//除湿泵暂停

#define DEWFLOWMIN    1//除湿罐流量最小值


#define DEFANFREQ     1//除湿罐风扇频率范围                   
#define DESTEMPMAX    1//除湿罐正常运行溶液温度上限
#define DESTEMPMIN    1//除湿罐正常运行溶液温度下限
#define DEWTIM        1//除湿罐等待最大时间

//#define DEFANFREQR    1//除湿罐风扇频率范围
#define DEFANFBCHAN   1//除湿罐风扇反馈端口
#define DEFANDEF      1//除湿罐风扇默认值
#define DEFANSTOP     1//除湿罐风扇停止

#define	SETPlENGTH	  ((u8)0x0001)   // Setpoint Structure Length
//AI
#define COOLINGSOURCE_TEMP 		       0
#define SOLUTION_TEMP 				   1
#define INLET_TEMP					   2
#define INLET_ HUMIDITY				   3
#define OUTLET_TEMP					   4
#define OUTLET_HUMIDITY				   5
#define SOLUTION_FLOWRATE			   6
#define DE_SOLU_LEVEL	               7
#define DILU_T_SOLU_LEVEL	           8
#define STR_T_SOLU_LEVEL	           9

//DO
#define   START 			  0
#define   TRANSFERPUMP		  1
#define	  SV1				  2
#define	  SV3				  3
#define	  LIQUIDLEVEL		  4
#define	  OTHER			      5
#define	  SV3OPTIONAL_PUMP	  6

//AO
#define   DE_PUMP 			  0
#define   DE_FAN		      1   
#define   DE_CS 			  2
    
//Setpoint
#define   START			      0
#define   SETP_TEMPERATURE    1
#define	  SETP_HUMIDITY 	  2
#define	  STOP			   	  3



/*	 Setpoint
    0   start
	1  temperature
	2  humidity 
	3  stop


	*/
void Lookup_table(float Daq[],float setpoint[],float arout[8]);
u8 ctrlalgorthim(float Daq[],float setpoint[],u8 flowratecnt,float arout[8] );
float coolingsouce_adj(u8 tempstep);
float flowrate_adj(u8 flowratestep);

void highlevel_alarm(float Daq);
void lowlevel_sv_alarm(float Daq);
void lowlevel_pump_alarm(float Daq);

void circulation_alarm(float arout[]);
u8 arrary_compare(float Daq_temp[],float Daq[]);
//void solutiontransfer(float Daq[] );
float *plastdata(float *pData_temp,float *pData);

void coolingsource_alarm(void);				

u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8]);
u8 dehStop(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8]);

#endif
