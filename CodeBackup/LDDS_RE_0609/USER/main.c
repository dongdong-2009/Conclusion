#include "stm32f10x_config.h"

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

/*******************************************************************************
  * @brief  Main program.
  * @param  None
  * @retval None
  ******************************************************************************/
int aset=0,dset=9,dset1=9,abit=0;
int eevcount=0;	
int main(void)
{	
	RCC_Configuration(); 						//ϵͳʱ������
  Usart_Configuration(); 					//��������
  port_Configuration(); 					//�˿�����
  analog_in_init(); 							//������ѹ����ģ���ʼ��
	rtd_init();											//�¶�ģ���ʼ��
  dac_init();											//������ѹ�����ʼ��
  Time_Configuration();  					//��ʱ������
	UsartST();											//��������1�ж�
	UartST(); 											//��������2�ж�
  Tim3ST(); 											//����ʱ��3�����ݴ����ж�
	
	while(1)
  {
		//��ת��ťһ������������״̬��remote---local---stop, remote---1, stop/local---0
		while(!panelControl&&(!panelCStatus))      //��ȡ��ת��ť������Ϣ�����ж�������״̬
		{
			panelControl=DPortIn(0);                 //��ȡ��ת��ť��Ϣ
			if(panelControl)                         //panelControl remote/local ģʽ  
			{
				panelCStatus=1;
			}
		}
		if(!panelControl)                          //�ж�ϵͳ��ť�Ƿ�ر�,����stop״̬
		{
			DPortOut(RE_ALARM,1);                    //������Ϣ
			
			reClever(analogOut,digitalOut);          //AO��DOȫ�����㣬ϵͳ�رգ��޲���
			panelCStatus=0;                          //������״̬��Ϊ0
		}
		//���device run����λ������ָ���localControl��С�巢���Ŀ���ָ��
		//device run---1---start, device run---0---stop
		//localControl---1---start, localControl---0---stop
		//ϵͳ���������ж�
		if((deviceRun|localControl|System_On)&&(!runStatus)&&panelControl)  //���������жϱ���
		{
			//��ȡϵͳ����״̬��Ϣ���Ƿ���ڹ���
		 	alarmFlag=regStart(digitalIn, digitalOut,analogIn,rangeIn,analogOut,rangeOut,panelControl);
			re_alarm=(enum _alarm)alarmFlag;
			if(alarmFlag!=0)
			{
				DPortOut(RE_ALARM,1);
				
				DPortOut(HEATPUMP,0);
				delay_s(1);
				DPortOut(REFAN,0);                             //�ط���  
				delay_s(1);	   
				DPortOut(CPUMP,0);	                           //��ѭ����
			}
			runStatus=1;                                 //�豸��������
		}
		//ϵͳֹͣ�����ж�
		//��λ������ֹͣ���С�巢��ֹͣ���ϵͳ��������״̬����ת��ť��1��ϵͳ��������
		if((!deviceRun)&&(!localControl)&&(!System_On)&&runStatus&&panelControl&&(re_alarm==start_normal))   //��û�й���ʱֹͣϵͳ
		{
			//��ȡϵͳֹͣ����״̬��Ϣ
		 	alarmFlag=regStop(rangeIn, rangeOut,digitalOut);
			re_alarm=(enum _alarm)alarmFlag;
			if(alarmFlag!=0)
			{
				DPortOut(RE_ALARM,1);
				
				DPortOut(HEATPUMP,0);
				delay_s(1);
				DPortOut(REFAN,0);                             //�ط���  
				delay_s(1);	   
				DPortOut(CPUMP,0);	                           //��ѭ����
			}
			//reClever(analogOut,digitalOut);
			runStatus=0;
		}
		//device run ����λ�����ƣ�����ϵͳremoteģʽ
		//device run ��remote control ʱ�̶���0����ʾϵͳ��û����λ�����ƣ���Ҫ��ͨ��С�������ͣ������ͨ�������ťʹС�崦��remote/localģʽ
		while(runStatus&&panelControl&&((remoteControl&deviceRun)|localControl|System_On))
		if(runStatus) 														         //ϵͳ��������
		{
			Tran_Flag=JudgeFlag();
			//���ȿ���ʱ�򣬲Ż����Ũ�ȼ��㡣����û�п��Ļ���Ũ�����趨Ϊ21
			alarmFlag=SS_Re_Transfer(Tran_Flag);             //������Һ
			re_alarm=(enum _alarm)alarmFlag;                 //��ȡ������Ϣ
			if(alarmFlag!=0)
			{
				DPortOut(RE_ALARM,1);
				
				DPortOut(HEATPUMP,0);
				delay_s(1);
				DPortOut(REFAN,0);                             //�ط���  
				delay_s(1);	   
				DPortOut(CPUMP,0);	                           //��ѭ����
			}
		}	
  }
}
 
/*******************************************************************************
  * @brief  System clock setting.
  * @param  None
  * @retval None
  ******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;                    //�����ⲿ���پ�������״̬ö�ٱ�����
	RCC_DeInit();                                    //��λRCC�Ĵ�����Ĭ��ֵ��
	RCC_HSEConfig(RCC_HSE_ON);                       //���ⲿ�ĸ��پ��� 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();      //�ȴ��ⲿ����ʱ��׼����
	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);               //����AHB
		RCC_PCLK2Config(RCC_HCLK_Div1);                //����APB2 
		RCC_PCLK1Config(RCC_HCLK_Div2);                //����APB1       
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);             //PLL=8M*9=72M
		RCC_PLLCmd(ENABLE);                                              //ʱ��PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);              //�ȴ�PLL����	      
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                       //����ϵͳʱ��=PLL	  
		while(RCC_GetSYSCLKSource() != 0x08);                            //���PLLʱ���Ƿ���Ϊϵͳʱ��	       
	}
}

//��ȡС�巢��������Ϣ 24�ֽ�
void dataResponseLocal(void)
{
	//��ȡAI��DI������Ϣ
	APortCIn(TempanalogIn,rangeIn);
  DPortCIn(digitalIn);
	
	//outlet humidity
  tx1[3]=(u8)((u16)TempanalogIn[RHOUT]/100);	
  tx1[4]=(u8)((u16)TempanalogIn[RHOUT]%100);
	
	tx1[5]=0;	
  tx1[6]=0;
	
	//inlet humidity
	tx1[7]=(u8)((u16)TempanalogIn[RHIN]/100);	
  tx1[8]=(u8)((u16)TempanalogIn[RHIN]%100);
	
	//�豸������Ϣ
	tx1[9]=(u8)deviceRun|localControl|System_On;	
	
	//����¶�
  tx1[10]=(u8)((u16)TempanalogIn[TIN]%100);
	
	//�����¶�
	tx1[11]=(u8)((u16)TempanalogIn[TOUT]/100);
  tx1[12]=(u8)((u16)TempanalogIn[TOUT]%100);
	tx1[19]=1;
  tx1[20]=alarmFlag;	                            //������Ϣ			
  tx1[21]=CRC_check(tx1,3,21);                    //У����
}	    

//������ݴ���53�ֽ�
void dataProcess(void)
{
	//�������ݰ�
	if(dataCbuff[9]==0x57)                      						//�յ� transfer data
  {																												//������ݰ�
		//System_On=dataCbuff[11];                     
		De_On=dataCbuff[12];
		DE_Level=dataCbuff[13]*100+dataCbuff[14];             //��ʪҺλ
		SS_Level=dataCbuff[15]*100+dataCbuff[16];             //ǿ��ҺҺλ
		tf_flag=dataCbuff[17];                                //��Һ��־λ
		Concentration=dataCbuff[19]*100+dataCbuff[20];        //��ʪŨ��
  }
	
	System_On=digitalIn[REMOTEONFF];                        //��ȡDI������Ϣ                      
	
	//��ȡ���������ݷ���ֵ  sensor data return
  APortCIn(TempanalogIn,rangeIn);                         //��ȡģ��������Ϣ��
  DPortCIn(digitalIn);                                    //��ȡ����������Ϣ��
		
	analogIn[0]=TempanalogIn[0]/10;                             //inlet temperature
	TX1[11]=(u8)(analogIn[0]/100);	
  TX1[12]=(u8)(((u16)analogIn[0])%100);
  TX1[13]=(u8)(((u32)(analogIn[0]*100))%100);
	
	analogIn[1]=TempanalogIn[1]/10;                             //inlet humidity
	TX1[14]=(u8)(analogIn[1]/100);	
  TX1[15]=(u8)(((u16)analogIn[1])%100);
  TX1[16]=(u8)(((u32)(analogIn[1]*100))%100);
	
	analogIn[2]=TempanalogIn[2]/10;                             //outlet temperature
	TX1[17]=(u8)(analogIn[2]/100);	
  TX1[18]=(u8)(((u16)analogIn[2])%100);
  TX1[19]=(u8)(((u32)(analogIn[2]*100))%100);
	
	RHout=analogIn[RHOUT];
	
	analogIn[3]=TempanalogIn[3]/10;                             //outlet humidity
	TX1[20]=(u8)(analogIn[3]/100);	
  TX1[21]=(u8)(((u16)analogIn[3])%100);
  TX1[22]=(u8)(((u32)(analogIn[3]*100))%100);
	
	analogIn[4]=(TempanalogIn[4]/50-4)/16*48;                  //RE level
	TX1[23]=(u8)(analogIn[4]/100);	
  TX1[24]=(u8)(((u16)analogIn[4])%100);
  TX1[25]=(u8)(((u32)(analogIn[4]*100))%100);
	
	analogIn[5]=(TempanalogIn[5]/50-4)/16*60+60;              // weak solution level
	TX1[26]=(u8)(analogIn[5]/100);	
  TX1[27]=(u8)(((u16)analogIn[5])%100);
  TX1[28]=(u8)(((u32)(analogIn[5]*100))%100);    
	
	analogIn[6]=TempanalogIn[6]/10;
	TX1[29]=(u8)(analogIn[6]/100);	
  TX1[30]=(u8)(((u16)analogIn[6])%100);
  TX1[31]=(u8)(((u32)(analogIn[6]*100))%100);	
		
	analogIn[7]=TempanalogIn[7]/8;
	TX1[32]=(u8)(analogIn[7]/100);	
  TX1[33]=(u8)(((u16)analogIn[7])%100);
  TX1[34]=(u8)(((u32)(analogIn[7]*100))%100);
	
	analogIn[8]=AbOutHum;                             //���ھ���ʪ��
	TX2[11]=(u8)(analogIn[8]/100);	
  TX2[12]=(u8)(((u16)analogIn[8])%100);
  TX2[13]=(u8)(((u32)(analogIn[8]*100))%100);
	
	analogIn[9]=AbInHum;                             //��ھ���ʪ��
	TX2[14]=(u8)(analogIn[9]/100);	
  TX2[15]=(u8)(((u16)analogIn[9])%100);
  TX2[16]=(u8)(((u32)(analogIn[9]*100))%100);
	
	analogIn[10]=AbdeltaHum;                             //����ھ���ʪ�Ȳ�
	TX2[17]=(u8)(analogIn[10]/100);	
  TX2[18]=(u8)(((u16)analogIn[10])%100);
  TX2[19]=(u8)(((u32)(analogIn[10]*100))%100);
	
	//TX1��TX2�ֱ������ű���Ϣ��TX1��analogIn[0]---analogIn[7]   TX2:analogIn[8]---analogIn[15]	
	analogIn[11]=AbDelta;                             //�����Ũ����Ϣ
	TX2[20]=(u8)(analogIn[11]/100);	
  TX2[21]=(u8)(((u16)analogIn[11])%100);
  TX2[22]=(u8)(((u32)(analogIn[11]*100))%100);
	
	analogIn[12]=TempanalogIn[12]/100;                      //solution inlet temperature
	TX2[23]=(u8)(analogIn[12]/100);	
  TX2[24]=(u8)(((u16)analogIn[12])%100);
  TX2[25]=(u8)(((u32)(analogIn[12]*100))%100);
		
	analogIn[13]=TempanalogIn[13]/100;                    //solution outlet temperature
	TX2[26]=(u8)(analogIn[13]/100);	
  TX2[27]=(u8)(((u16)analogIn[13])%100);
  TX2[28]=(u8)(((u32)(analogIn[13]*100))%100);	
	
	analogIn[14]=TempanalogIn[14]/100;                    //hot water inlet temperature
	TX2[29]=(u8)(analogIn[14]/100);	
  TX2[30]=(u8)(((u16)analogIn[14])%100);
  TX2[31]=(u8)(((u32)(analogIn[14]*100))%100);	
	
	analogIn[15]=TempanalogIn[15]/100;                    //hot water outlet temperature
	TX2[32]=(u8)(analogIn[15]/100);	
  TX2[33]=(u8)(((u16)analogIn[15])%100);
  TX2[34]=(u8)(((u32)(analogIn[15]*100))%100);		
    
	TX1[37]=(u8)(((u16)analogOut[0])/100);                //hot water valve
  TX1[38]=(u8)(((u32)(analogOut[0]*100))%100);
  TX1[39]=(u8)(((u32)(analogOut[0]*10000))%100);
 		
  TX1[35]=Digital_handle(digitalIn ,1);                 //���DI��Ϣ
  TX1[36]=Digital_handle(digitalOut,1);                 //���DO��Ϣ
  
	TX2[35]=Digital_handle(digitalIn ,2);                 //���DI��Ϣ
  TX2[36]=Digital_handle(digitalOut,2);                 //���DO��Ϣ
  
	TX1[50]=CRC_check(TX1,0,50);                          //У��λ��Ϣ
  TX2[50]=CRC_check(TX2,0,50);                          //У��λ��Ϣ
	
	//TX9���transfer data������DE��REϵͳ֮�����ݽ���
	//TX9[12]=(u8)deviceRun|localControl;
	TX9[11]=System_On;
	TX9[12]=runStatus;                                         //ϵͳ����״̬
	TX9[13]=(u8)(analogIn[RSLEVEL]/100);                       //����Һλ
	TX9[14]=(u8)(((u16)analogIn[RSLEVEL])%100);    
	TX9[15]=(u8)(analogIn[WSLEVEL]/100);                       //weak solution Һλ
	TX9[16]=(u8)(((u16)analogIn[WSLEVEL])%100);
	TX9[19]=(u8)(analogIn[11]/100);                            //Ũ����Ϣ
	TX9[20]=(u8)(((u16)analogIn[11])%100);
	
	//��ȡҺλ��Ϣ
	getlevel(analogIn[RSLEVEL],analogIn[WSLEVEL],analogIn[13],analogIn[6],analogIn[TOUT]); 
		
	//��ʪϵͳ��SS tankҺλ��Ϣ
  //��ȡAI�˿ڣ�AI7��DEϵͳSS tankҺλ��Ϣ
	DE_Levelsingal=analogIn[DE_LEVEL];
	
	//��Һ����¶�
	InletSolutemp=analogIn[TSIN];                    //ԭʼ����
	//InletSoluTemp=AverageFilter(InletSolutemp);      //�˲�����
	//InletSoluTemp=recursive_average_filter(InletSolutemp);
	
	AbOutHum = RH2HR(analogIn[TOUT], analogIn[RHOUT]);
	AbInHum = RH2HR(analogIn[TIN], analogIn[RHIN]);
	
	//���Ⱥ�ѭ���ÿ�������£��ſ�ʼ����Ũ�ȼ���
	if((digitalOut[CPUMP]==1)&&(digitalOut[REFAN]==1)&&(InletSolutemp>67.0))
	{
		StatusFlag=1;
	}
	else
	{
		StatusFlag=0;
	}
	
	//Ũ�ȼ��㣬���ȿ�����״̬�£�ϵͳ��������
	if(StatusFlag==1)
	{
		AbDelta=AbOutHum-AbInHum;
		//AbdeltaHum=AverageFilter(AbDelta);
		AbdeltaHum=recursive_average_filter(AbDelta);
	}
	else if(StatusFlag==0)
	{
		//AbdeltaHum=100;
		AbDelta=100;
	}	
		
}

//�����ض��壬���������ӡ��Ϣ
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}
