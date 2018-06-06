#ifndef _LDDSSP_H
#define _LDDSSP_H
#define Number               8
// preset value

//#define DELTAHumidity        43         //�����ھ���ʪ�Ȳ�

//#define RSLEVELSTART         30         //������Һ����
//#define RSLEVELMAXALARM      35         //������Һ����
//#define RSLEVELSTOP          18         //������Һ����
//#define RSLEVELMINALARM      7          //������Һ����
//#define WSLEVELMAX           90         //weak��Һ����
//#define WSLEVELMAXALARM      95         //weak��Һ����
//#define SSLEVELMAX           90         //strong solution ��Һ����
//#define SSLEVELMAXALARM      115         //strong solution ��Һ����

#define HOTVALVEO            10         //��ˮ����ʼֵ

#define RESTEMPSP            16         //��Һ�������ʺ��¶�
#define REPUMPSP             40         //�õĳ�ʼ��Ĭ��Ƶ��
#define REFANSP              40         //����ĳ�ʼ��Ĭ��Ƶ��
#define RESDENSITY           30         //����ҺŨ��  
#define RELTAHumidity        43         //�����ھ���ʪ�Ȳ�

//AI
#define   TOUT               0          //outlet�¶�
#define   RHOUT              1          //outletʪ��
#define   TIN                2          //inlet�¶�
#define   RHIN			     3          //inletʪ��
#define   RSLEVEL			 4          //����Һλ  RE LEVEL
#define   WSLEVEL		     5          //weak solutionҺλ   WS LEVEL
#define   DE_LEVEL           7          //DE ϵͳ�ź�


#define   TSIN		         0         //solution Inlet�¶�
#define   TSOUT		         1         //solution Outlet�¶�
#define   TWIN		         2         //hot water Inlet�¶�
#define   TWOUT		         3         //hot water Outlet�¶�

//DO
#define	  CPUMP				 0          //circulation pump
#define   REFAN				 1          //regeneration fan
#define   WSVALVE            2          //weak solution valve
#define   TFVALVE 		     3          //transfer valve
#define   HEATPUMP           4          //heat pump
#define   RE_ALARM           5          //������Ϣ

//DI
#define   LOCALORREMOTE      0          //Local or remote mode selection 
#define   FAUT_PUMP          1          //pump 
#define   FAUT_FAN           2          //fan
#define   REMOTEONFF         4          //Remote on/off
#define   DETransFlag        7          //de ��Һ��־λ

//AO
#define   HWVALVE 			     0          //hot water valve

extern char System_On;
extern char DE_Level;                     //��ʪҺλ
extern char SS_Level;                     //ǿ��ҺҺλ
extern char System_On;                    //ϵͳ������Ϣ
extern char De_On;                        //��ʪϵͳ����״̬


char reg_algorithm(float analogIn[], float arout[]);                                       //�����㷨��Ϣ
void reInit(float arr[8]);                                                               //����ϵͳ��ʼ��
void reClever(void);                                                 //�豸�������
void reDefault(void);                                                                    //�豸Ĭ��ģʽ��������
void getlevel(float relevel,float wslevel,float hottemp,float hwvfb,float tempout);                    //��ȡҺλ��Ϣ

float ConCalculate(void);                                                                //Ũ�ȼ���  Concentration Calculate  
float RH2HR(float temp, float relativehum);                                              //���ʪ�Ⱥ;���ʪ��ת��
char JudgeFlag(void);
;
//u8 De_TranFlag=0;

                                                               //����ϵͳҺλ����
char SS_Re_Transfer(char TFlag);									                                               //��Һ����
float AverageFilter(float data);
float recursive_average_filter(float data);



#endif /* __STM32F10x_H */
