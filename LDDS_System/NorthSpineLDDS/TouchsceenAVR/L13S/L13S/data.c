#include "data.h"
#include "config.h"

unsigned char StartFlag=0,LocFlag=0;
unsigned char OpenFlag=1, UserSetFlag=0, SetDFlag=0;
unsigned int AI1=0,AI2=0,AI3=0,AI4=0,AI5=0,AI6=0,AI7=0,AI8=0;
unsigned int SetTemperature=25;
unsigned int AO1=0,AO2=0,DO1=0,DO2=0;
float GetTemperature=0,GetHumidity=0,GetFeedback=0;
unsigned char getdataflag=0,getsensorflag=0,sendtype=0;
unsigned int stime=0;
unsigned int port1flag=0,port2flag=0;
unsigned char ST1data1=0, ST1data2=0, ST1data3=0, ST1data4=0, ST1data5=0, ST1data6=0, ST1data7=0, ST1data8=0, ST1data9=0, ST1data10=0, ST1data11=0, ST1data12=0;
unsigned char ST2data1=0, ST2data2=0, ST2data3=0, ST2data4=0, ST2data5=0, ST2data6=0, ST2data7=0, ST2data8=0, ST2data9=0, ST2data10=0, ST2data11=0, ST2data12=0;
float P1=0,P2=0,I1=0,I2=0,D1=0,D2=0;
unsigned int Tflag=0,Oflag=0;
struct PID_DATA pidData;
unsigned int starflag=0,starcount=0,starfinflag=0;
char ss[6];
char touchcase=0,touchflag=0,waitcount=0;

void usarS(void)
{
	 sendtype=0;
}

void usarP(unsigned int data1,unsigned int data2,unsigned int data3,unsigned int data4,unsigned int data5,unsigned int data6,unsigned int data7,unsigned int data8,unsigned int data9,unsigned int data10,unsigned int data11,unsigned int data12)
{
 	 send_data0(3);
	 ST2data1=data1;
	 ST2data2=data2;
	 ST2data3=data3;
	 ST2data4=data4;
	 ST2data5=data5;
	 ST2data6=data6;
	 ST2data7=data7;
	 ST2data8=data8;
	 ST2data9=data9;
	 ST2data10=data10;
	 ST2data11=data11;
	 ST2data12=data12;
	 sendtype=3;
}

void usarH(unsigned int data1,unsigned int data2,unsigned int data3,unsigned int data4,unsigned int data5,unsigned int data6,unsigned int data7,unsigned int data8,unsigned int data9,unsigned int data10,unsigned int data11,unsigned int data12)
{
   send_data0(1);
   if((data1==1)&&(UserSetFlag==0))
   {
   		ST1data1=1;
		ST1data2=data2;
   		ST1data3=data3;
   		ST1data4=data4;
   		ST1data5=data5;
   		ST1data6=data6;
   		ST1data7=data7;
   		ST1data8=data8;
   		ST1data9=data9;
   		ST1data10=data10;
   		ST1data11=data11;
   		ST1data12=data12;
   		sendtype=1;
		LCD_BG_H;
   }
   else if(data1==0)
   {
   		ST1data1=0;
		ST1data2=0;
   		ST1data3=0;
   		ST1data4=0;
   		ST1data5=0;
   		ST1data6=0;
   		ST1data7=0;
   		ST1data8=0;
   		ST1data9=0;
   		ST1data10=0;
   		ST1data11=0;
   		ST1data12=0;
   		sendtype=1;
		UserSetFlag=0;
		LCD_BG_L;
   }
}

void usarT(unsigned int data1)
{
   SetTemperature=data1;
   send_data0(2);
   delayms(10);
   sendtype=2;
}

void usarSD(void)
{
}

void usarHD(void)
{}

void usarTD(void)
{}

void getTandH(unsigned int T,unsigned int H)
{
    double Pa=0,Dewpoint=0;
	GetTemperature=T,GetHumidity=H;
	getsensor(T*10,H*10,LocFlag);
	Pa=GetHumidity*exp(17.368*GetTemperature/(238.88+GetTemperature));
    Dewpoint=238.88*log(Pa/6.1121)/(17.368-log(Pa/6.1121));
	
	if(StartFlag==1)
	{
		if(Dewpoint>(Chillwatertem+2))
		{
			if(GetTemperature>((SetTemperature+1)*10))
			{
				RELAY1_ON;
				DO1=1;
			}
			else if(GetTemperature<((SetTemperature-1)*10))
			{
				RELAY1_OFF;
				DO1=0;
			}
		}
		else if(Dewpoint<(Chillwatertem+2))
		{
			RELAY1_OFF;
			DO1=0;
		}
		getdo(DO1,DO2);
	}	
}


SIGNAL(SIG_OVERFLOW1)
{
	TCNT1H = 0xC2; //reload counter high value
	TCNT1L = 0xF7; //reload counter low value
	getdataflag=1;
	if(starflag==1)starcount++;
	if(starcount==3600)starfinflag=1;
	waitcount++;
	if(waitcount==60)
	{
		waitcount=0;
		LCD_BG_L;
		touchflag=1;		
	}
}

SIGNAL(SIG_OVERFLOW2)
{
	Tflag++;
	if(Tflag==10)
	{
		Oflag=1;
	}
	else if(Tflag==40)
	{
		TCCR2 = 0x0;
		TCNT2 = 0;
		Oflag=0;
		Tflag=0;
	}
}

void getflag(void)
{
	port1flag=1;
}

void Mainfunction(void)
{
	while(1)
	{
		if(starfinflag==1)
		{
			starflag=0;
		}
	 	if((PIND&0x02)==0)
		{
			waitcount=0;
			if (touchflag==1)
			{
				LCD_BG_H;
			} 
			else
			{
				if(Oflag==2)
				{
					touchcase=function();
				}
				else if(Oflag==0)
				{
					Oflag=2;
					TCNT2 = 0x64;TCCR2 = 0x05;
				}
				else if(Oflag==1)
				{
					switch(touchcase)
					{
						case 1:SetTemperature--;inttostrC(SetTemperature,ss);showzifustr(180,220,ss,0,0xffff);break;
						case 2:SetTemperature++;inttostrC(SetTemperature,ss);showzifustr(180,220,ss,0,0xffff);break;
						case 3:
						if (StartFlag==0)
						{
							showzifustr(355,198,"ON",0xffff,0x012C);
							showzifustr(410,198,"OFF",0x8410,0x012C);
							StartFlag=1;
							LocFlag=0;
							RELAY2_ON;
							DO2=1;
							getdo(DO1,DO2);
						}
						else if(StartFlag==1)
						{
							showzifustr(355,198,"ON",0x8410,0x012C);
							showzifustr(410,198,"OFF",0xffff,0x012C); 
							StartFlag=0;
							LocFlag=1;
							RELAY1_OFF;
							DO1=0;
							RELAY2_OFF;
							DO2=0;
							getdo(DO1,DO2);
						}
						default:break;
					}
					touchcase=0;
					UserSetFlag=1;
				}
			}
			touchflag=0;
		}
		if(port1flag==1)
		{
			Reciver_process1();
			port1flag=0;
		}
		if(getdataflag==1)
		{
		 	DHTReadData();
			getdataflag=0;
			switch(sendtype)
			{
			 	case 0:send_data1(0,0,0,0,0,0,0,0,0,0,0,0,0);break;
				case 1:send_data1(1,ST1data1,ST1data2,ST1data3,ST1data4,ST1data5,ST1data6,ST1data7,ST1data8,ST1data9,ST1data10,ST1data11,ST1data12);sendtype=0;break;
				case 2:send_data1(2,SetTemperature,0,0,0,0,0,0,0,0,0,0,0);sendtype=0;break;
				case 3:send_data1(3,ST2data1,ST2data2,ST2data3,ST2data4,ST2data5,ST2data6,ST2data7,ST2data8,ST2data9,ST2data10,ST2data11,ST2data12);sendtype=0;break;
				case 4:send_data1(4,0,0,0,0,0,0,0,0,0,0,0,0);sendtype=0;break;
				default:break;
			}
		}
	}
}

unsigned int returnT(void)
{return GetTemperature*10;}

unsigned int returnH(void)
{return GetHumidity*10;}

void ACBinit(void)
{
	UI();
	starflag=1;
	sendtype=4;
//	RELAY2_ON;
//  pid_Init(1,1,1,&pidData);
}

void pid_Init(int P, int I, int D, struct PID_DATA *pid)
{
	pid->Proportion=P;
	pid->Integral=I;
	pid->Derivative=D;
}

double pid_Calc(struct PID_DATA *pid,double NextPoint)
{
	double dError,Error;
	Error = pid->SetPoint - NextPoint; // 偏差
	pid->SumError += Error; // 对偏差进行积累计算积分项
	dError = pid->LastError - pid->PrevError; // 当前微分
	pid->PrevError = pid->LastError; //更新e(k-1)
	pid->LastError = Error;     //更新e(k)
	/* u(k)=Kp*e(k) + Ki*[e(0)+e(1)+...+e(k)] + Kd*[e(k)-e(k-1) + u0] */
	return (pid->Proportion * Error + pid->Integral * pid->SumError + pid->Derivative * dError); //开始进行PID控制时的原始值u0=0
}
