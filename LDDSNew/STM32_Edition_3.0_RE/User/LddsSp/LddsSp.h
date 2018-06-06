#ifndef _LDDSSP_H
#define _LDDSSP_H
#define Number               8
// preset value

//#define DELTAHumidity        43         //进出口绝对湿度差

//#define RSLEVELSTART         30         //再生溶液上限
//#define RSLEVELMAXALARM      35         //再生溶液上限
//#define RSLEVELSTOP          18         //再生溶液下限
//#define RSLEVELMINALARM      7          //再生溶液下限
//#define WSLEVELMAX           90         //weak溶液上限
//#define WSLEVELMAXALARM      95         //weak溶液上限
//#define SSLEVELMAX           90         //strong solution 溶液上限
//#define SSLEVELMAXALARM      115         //strong solution 溶液上限

#define HOTVALVEO            10         //热水阀初始值

#define RESTEMPSP            16         //溶液工作区适合温度
#define REPUMPSP             40         //泵的初始化默认频率
#define REFANSP              40         //风机的初始化默认频率
#define RESDENSITY           30         //盐溶液浓度  
#define RELTAHumidity        43         //进出口绝对湿度差

//AI
#define   TOUT               0          //outlet温度
#define   RHOUT              1          //outlet湿度
#define   TIN                2          //inlet温度
#define   RHIN			     3          //inlet湿度
#define   RSLEVEL			 4          //再生液位  RE LEVEL
#define   WSLEVEL		     5          //weak solution液位   WS LEVEL
#define   DE_LEVEL           7          //DE 系统信号


#define   TSIN		         0         //solution Inlet温度
#define   TSOUT		         1         //solution Outlet温度
#define   TWIN		         2         //hot water Inlet温度
#define   TWOUT		         3         //hot water Outlet温度

//DO
#define	  CPUMP				 0          //circulation pump
#define   REFAN				 1          //regeneration fan
#define   WSVALVE            2          //weak solution valve
#define   TFVALVE 		     3          //transfer valve
#define   HEATPUMP           4          //heat pump
#define   RE_ALARM           5          //报警信息

//DI
#define   LOCALORREMOTE      0          //Local or remote mode selection 
#define   FAUT_PUMP          1          //pump 
#define   FAUT_FAN           2          //fan
#define   REMOTEONFF         4          //Remote on/off
#define   DETransFlag        7          //de 换液标志位

//AO
#define   HWVALVE 			     0          //hot water valve

extern char System_On;
extern char DE_Level;                     //除湿液位
extern char SS_Level;                     //强溶液液位
extern char System_On;                    //系统运行信息
extern char De_On;                        //除湿系统运行状态


char reg_algorithm(float analogIn[], float arout[]);                                       //再生算法信息
void reInit(float arr[8]);                                                               //再生系统初始化
void reClever(void);                                                 //设备清零操作
void reDefault(void);                                                                    //设备默认模式参数设置
void getlevel(float relevel,float wslevel,float hottemp,float hwvfb,float tempout);                    //读取液位信息

float ConCalculate(void);                                                                //浓度计算  Concentration Calculate  
float RH2HR(float temp, float relativehum);                                              //相对湿度和绝对湿度转换
char JudgeFlag(void);
;
//u8 De_TranFlag=0;

                                                               //再生系统液位报警
char SS_Re_Transfer(char TFlag);									                                               //换液函数
float AverageFilter(float data);
float recursive_average_filter(float data);



#endif /* __STM32F10x_H */
