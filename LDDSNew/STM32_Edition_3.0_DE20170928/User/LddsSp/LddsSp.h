#ifndef _LDDSSP_H
#define _LDDSSP_H

#define DESTVALUE             1	//     继电器启动
#define DESPVALUE			  0	//     继电器停止

// preset value
//#define DSLEVELSTART		 31 //除湿换液开始	33
#define DSLEVELSTOP			 13  //除湿换液停止
//#define DSLEVELMAXALARM      40 //除湿溶液上限报警
//#define DSLEVELMINALARM      5  //除湿溶液下限报警
//#define SSLEVELMAXALARM      115 //strong溶液上限报警
//#define SSLEVELMINALARM		 5 //STRONG SOLUTION LOW LIMITED WARNING
//#define SSLEVELMAX			 100 //strong溶液上限

#define WSLEVELMAXALARM      99 //strong溶液上限报警
#define WSLEVELMAX			 95 //strong溶液上限
#define CHILLEDVALVEO        99  //chilled water valve init
#define CPUMPO       		 40 //circulation pump init
#define SFANO       		 49  //supply fan init

#define DESTEMPSP            16  //溶液工作区适合温度
#define DEPUMPSP             40  //泵的初始化默认频率
#define DEFANSP              40  //风机的初始化默认频率
#define DESDENSITY           30  //盐溶液浓度  
//#define DEAPPLEVEL			 23	  //de most proper working level

#define  DEWFLOWMINALARM	 5 //flowratealarm
#define  DESTEMAXALARM		 21//csalarm
//AI
#define   FLOWRATE           0   //circulation pump feedback
#define   CPUMPFB            1   //solution flowrate
#define   SFANFB             2   //supply fan feedback
#define   CWVALVEFB			 3   //chilled water feedback
#define   TIN   			 4   //inlet temperature
#define   RHIN  		     5   //inlet RH
#define   TOUT   			 6   //outlet temperature
#define   RHOUT  		     7   //outlet RH
#define   DSLEVEL            8   //dehumidifier level
#define   SSLEVEL            11   //strong solution level
#define   DATASET           10  //RH set value

#define   TSIN		           0  //除湿Inlet温度
#define   TSOUT		           1  //除湿Outlet温度
#define   TWIN		           2  //CHILL WATER Inlet温度
#define   TWOUT		           3  //热水Outlet温度

//DO
#define   VSD_PUMP 		       0  //VSD pump
#define   VSD_FAN              1  //vsd fan
#define   TRPUMP			   2  //transfer pump
#define	  STVALVE			   3  //solution tank valve
#define   ALARM			       5
#define   LEVELADM			   7

//DI
#define   LOCALORREMOTE      0  //本地开关
#define   FAUT_PUMPVSD       1  //pump vsd fault
#define   FAUT_FANVSD        2  //fan vsd fault
#define   FAUT_TFPUMP        3  //transfer pump OL fault
#define   REMONOFF           4
//AO
#define   CPUMP 			   0  //VSD circulation pump
#define   SFAN 			       1  //VSD supply fan
#define   CWVALVE 			   2  //chilled water valve
#define   SSLEVELSD            3
#define   RHDATA 			   5  //current RH
//
#define   SPHUM					0
#define   SPTEMP				1
#define   SETRELHUM				2

#define   CONLENTH			   19
#define   TLENTH  			   13
#define   STACON			   19
#define   STATEM			   15


static float templocker=0;
extern float concentration;
static float   hummatric[CONLENTH][TLENTH]={0};

static float   con2dens[12][11] = {{1106.66, 1106.50, 1106.33, 1106.14, 1105.94, 1105.73, 1105.51, 1105.28, 1105.04, 1104.78, 1104.51  },
                                  {1113.00, 1112.84, 1112.67, 1112.48, 1112.29, 1112.07, 1111.85, 1111.62, 1111.37, 1111.12, 1110.85  }	,
                                  {1119.40, 1119.23, 1119.06, 1118.87, 1118.67, 1118.46, 1118.24, 1118.00, 1117.76, 1117.50, 1117.23 } ,
                                  {1125.83, 1125.67, 1125.50, 1125.31, 1125.11, 1124.90, 1124.67, 1124.43, 1124.19, 1123.93, 1123.66  },
                                  {1132.32, 1132.16, 1131.98, 1131.79, 1131.59, 1131.38, 1131.15, 1130.91, 1130.66, 1130.40, 1130.13  },
                                  {1138.86, 1138.69, 1138.52, 1138.33, 1138.12, 1137.91, 1137.68, 1137.44, 1137.19, 1136.93, 1136.65 }, 
                                  {1145.44, 1145.27, 1145.10, 1144.90, 1144.70, 1144.48, 1144.25, 1144.01, 1143.76, 1143.50, 1143.22 } ,
                                  {1152.07, 1151.90, 1151.72, 1151.53, 1151.33, 1151.11, 1150.88, 1150.63, 1150.38, 1150.11, 1149.84 }, 
                                  {1158.75, 1158.58, 1158.40, 1158.21, 1158.00, 1157.78, 1157.55, 1157.30, 1157.05, 1156.78, 1156.50  },
                                  {1165.47, 1165.31, 1165.12, 1164.93, 1164.72, 1164.50, 1164.27, 1164.02, 1163.77, 1163.50, 1163.22  },
                                  {1185.96, 1185.79, 1185.61, 1185.41, 1185.20, 1184.97, 1184.74, 1184.49, 1184.22, 1183.95, 1183.67  },
                                  {1199.89, 1199.72, 1199.53, 1199.33, 1199.12, 1198.89, 1198.65, 1198.40, 1198.13, 1197.86, 1197.57  },
								  }	;



static float hummatric12[CONLENTH][TLENTH] ={ 
{	8.72 	,	8.85 	,	8.98 	,	9.11 	,	9.25 	,	9.39 	,	9.54 	,	9.69 	,	9.84 	,	10.00 	,	10.16 	,	10.33 	,	10.50 	}	,
{	8.66 	,	8.78 	,	8.91 	,	9.04 	,	9.18 	,	9.32 	,	9.46 	,	9.61 	,	9.76 	,	9.92 	,	10.08 	,	10.24 	,	10.41 	}	,
{	8.59 	,	8.72 	,	8.84 	,	8.97 	,	9.11 	,	9.24 	,	9.38 	,	9.53 	,	9.68 	,	9.83 	,	9.99 	,	10.15 	,	10.32 	}	,
{	8.53 	,	8.65 	,	8.77 	,	8.90 	,	9.03 	,	9.17 	,	9.31 	,	9.45 	,	9.60 	,	9.75 	,	9.90 	,	10.06 	,	10.23 	}	,
{	8.46 	,	8.58 	,	8.70 	,	8.83 	,	8.96 	,	9.09 	,	9.22 	,	9.37 	,	9.51 	,	9.66 	,	9.81 	,	9.97 	,	10.13 	}	,
{	8.39 	,	8.51 	,	8.63 	,	8.75 	,	8.88 	,	9.01 	,	9.14 	,	9.28 	,	9.42 	,	9.57 	,	9.72 	,	9.87 	,	10.03 	}	,
{	8.32 	,	8.44 	,	8.55 	,	8.67 	,	8.80 	,	8.93 	,	9.06 	,	9.19 	,	9.33 	,	9.48 	,	9.62 	,	9.77 	,	9.93 	}	,
{	8.25 	,	8.36 	,	8.48 	,	8.60 	,	8.72 	,	8.84 	,	8.97 	,	9.11 	,	9.24 	,	9.38 	,	9.53 	,	9.68 	,	9.83 	}	,
{	8.18 	,	8.29 	,	8.40 	,	8.52 	,	8.64 	,	8.76 	,	8.89 	,	9.02 	,	9.15 	,	9.29 	,	9.43 	,	9.57 	,	9.72 	}	,
{	8.10 	,	8.21 	,	8.32 	,	8.44 	,	8.55 	,	8.67 	,	8.80 	,	8.93 	,	9.06 	,	9.19 	,	9.33 	,	9.47 	,	9.62 	}	,
{	8.03 	,	8.14 	,	8.24 	,	8.36 	,	8.47 	,	8.59 	,	8.71 	,	8.83 	,	8.96 	,	9.09 	,	9.23 	,	9.37 	,	9.51 	}	,
{	7.96 	,	8.06 	,	8.16 	,	8.27 	,	8.38 	,	8.50 	,	8.62 	,	8.74 	,	8.87 	,	8.99 	,	9.13 	,	9.26 	,	9.40 	}	,
{	7.88 	,	7.98 	,	8.08 	,	8.19 	,	8.30 	,	8.41 	,	8.53 	,	8.65 	,	8.77 	,	8.89 	,	9.02 	,	9.16 	,	9.29 	}	,
{	7.80 	,	7.90 	,	8.00 	,	8.11 	,	8.21 	,	8.32 	,	8.43 	,	8.55 	,	8.67 	,	8.79 	,	8.92 	,	9.05 	,	9.18 	}	,
{	7.73 	,	7.82 	,	7.92 	,	8.02 	,	8.12 	,	8.23 	,	8.34 	,	8.46 	,	8.57 	,	8.69 	,	8.82 	,	8.94 	,	9.07 	}	,
{	7.65 	,	7.74 	,	7.84 	,	7.94 	,	8.04 	,	8.14 	,	8.25 	,	8.36 	,	8.47 	,	8.59 	,	8.71 	,	8.83 	,	8.96 	}	,
{	7.57 	,	7.66 	,	7.75 	,	7.85 	,	7.95 	,	8.05 	,	8.15 	,	8.26 	,	8.37 	,	8.49 	,	8.60 	,	8.73 	,	8.85 	}	,
{	7.49 	,	7.58 	,	7.67 	,	7.76 	,	7.86 	,	7.96 	,	8.06 	,	8.17 	,	8.27 	,	8.38 	,	8.50 	,	8.62 	,	8.74 	}	,
{	7.41 	,	7.50 	,	7.59 	,	7.68 	,	7.77 	,	7.87 	,	7.97 	,	8.07 	,	8.17 	,	8.28 	,	8.39 	,	8.51 	,	8.62 	}	,

								 }	;



static float hummatric10[CONLENTH][TLENTH] ={  
{	8.72 	,	8.85 	,	8.98 	,	9.11 	,	9.25 	,	9.39 	,	9.54 	,	9.69 	,	9.84 	,	10.00 	,	10.16 	,	10.33 	,	10.50 	}	,
{	8.66 	,	8.78 	,	8.91 	,	9.04 	,	9.18 	,	9.32 	,	9.46 	,	9.61 	,	9.76 	,	9.92 	,	10.08 	,	10.24 	,	10.41 	}	,
{	8.59 	,	8.72 	,	8.84 	,	8.97 	,	9.11 	,	9.24 	,	9.38 	,	9.53 	,	9.68 	,	9.83 	,	9.99 	,	10.15 	,	10.32 	}	,
{	8.53 	,	8.65 	,	8.77 	,	8.90 	,	9.03 	,	9.17 	,	9.31 	,	9.45 	,	9.60 	,	9.75 	,	9.90 	,	10.06 	,	10.23 	}	,
{	8.46 	,	8.58 	,	8.70 	,	8.83 	,	8.96 	,	9.09 	,	9.22 	,	9.37 	,	9.51 	,	9.66 	,	9.81 	,	9.97 	,	10.13 	}	,
{	8.39 	,	8.51 	,	8.63 	,	8.75 	,	8.88 	,	9.01 	,	9.14 	,	9.28 	,	9.42 	,	9.57 	,	9.72 	,	9.87 	,	10.03 	}	,
{	8.32 	,	8.44 	,	8.55 	,	8.67 	,	8.80 	,	8.93 	,	9.06 	,	9.19 	,	9.33 	,	9.48 	,	9.62 	,	9.77 	,	9.93 	}	,
{	8.25 	,	8.36 	,	8.48 	,	8.60 	,	8.72 	,	8.84 	,	8.97 	,	9.11 	,	9.24 	,	9.38 	,	9.53 	,	9.68 	,	9.83 	}	,
{	8.18 	,	8.29 	,	8.40 	,	8.52 	,	8.64 	,	8.76 	,	8.89 	,	9.02 	,	9.15 	,	9.29 	,	9.43 	,	9.57 	,	9.72 	}	,
{	8.10 	,	8.21 	,	8.32 	,	8.44 	,	8.55 	,	8.67 	,	8.80 	,	8.93 	,	9.06 	,	9.19 	,	9.33 	,	9.47 	,	9.62 	}	,
{	8.03 	,	8.14 	,	8.24 	,	8.36 	,	8.47 	,	8.59 	,	8.71 	,	8.83 	,	8.96 	,	9.09 	,	9.23 	,	9.37 	,	9.51 	}	,
{	7.96 	,	8.06 	,	8.16 	,	8.27 	,	8.38 	,	8.50 	,	8.62 	,	8.74 	,	8.87 	,	8.99 	,	9.13 	,	9.26 	,	9.40 	}	,
{	7.88 	,	7.98 	,	8.08 	,	8.19 	,	8.30 	,	8.41 	,	8.53 	,	8.65 	,	8.77 	,	8.89 	,	9.02 	,	9.16 	,	9.29 	}	,
{	7.80 	,	7.90 	,	8.00 	,	8.11 	,	8.21 	,	8.32 	,	8.43 	,	8.55 	,	8.67 	,	8.79 	,	8.92 	,	9.05 	,	9.18 	}	,
{	7.73 	,	7.82 	,	7.92 	,	8.02 	,	8.12 	,	8.23 	,	8.34 	,	8.46 	,	8.57 	,	8.69 	,	8.82 	,	8.94 	,	9.07 	}	,
{	7.65 	,	7.74 	,	7.84 	,	7.94 	,	8.04 	,	8.14 	,	8.25 	,	8.36 	,	8.47 	,	8.59 	,	8.71 	,	8.83 	,	8.96 	}	,
{	7.57 	,	7.66 	,	7.75 	,	7.85 	,	7.95 	,	8.05 	,	8.15 	,	8.26 	,	8.37 	,	8.49 	,	8.60 	,	8.73 	,	8.85 	}	,
{	7.49 	,	7.58 	,	7.67 	,	7.76 	,	7.86 	,	7.96 	,	8.06 	,	8.17 	,	8.27 	,	8.38 	,	8.50 	,	8.62 	,	8.74 	}	,
{	7.41 	,	7.50 	,	7.59 	,	7.68 	,	7.77 	,	7.87 	,	7.97 	,	8.07 	,	8.17 	,	8.28 	,	8.39 	,	8.51 	,	8.62 	}	,
								 }	;

short int  deh_transfer(void);
short int  highlevel_alarm(void)		   ;
short int  lowlevel_sv_alarm(void)	  ;

float opencnts(float error)	  ;
float RH2HR(float temp, float relativehum);
float softsensing(void);
void  concenalgorithm(float Setpoint[],float analogIn[16],float rangeIn[12],float analogOut[8],float rangeOut[8]) ;
float density(float temperature, float concen );
float SolInletPID(float aimed_solultiontemp);
float caimdetermin(float setpoint[], float conNow,float SolInTNow )	  ;
float opentimecnt(float tempTa,float concenw,float concens,float caim)	;

extern char algorithmstart ;

int valveopen(float t);
void deClever(void);
void deDefault(void);
short int deh_level_alarm(void);


#endif /* __STM32F10x_H */
