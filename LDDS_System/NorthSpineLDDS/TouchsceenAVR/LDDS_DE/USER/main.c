
#include "stm32f10x_config.h"


 
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)


/*******************************************************************************
  * @brief  Main program.
  * @param  None
  * @retval None
  ******************************************************************************/
int aset=0;
int eevcount=0;	
int main(void)



{
	
    RCC_Configuration(); //ϵͳʱ������
    Usart_Configuration(); //��������
    port_Configuration(); //�˿�����
    analog_in_init(); //������ѹ����ģ���ʼ��
	rtd_init();	//�¶�ģ���ʼ��
    dac_init();	//������ѹ�����ʼ��
    Time_Configuration();  //��ʱ������
	UsartST();//��������1�ж�
	UartST(); //��������2�ж�
    Tim3ST(); //����ʱ��3�����ݴ����ж�

    while(1)
    {
		while(!panelControl&&(!panelCStatus))
		{
			panelControl=DPortIn(0);
			if(panelControl)
			{
			 	panelCStatus=1;	
			}
		}
		if(!panelControl)
		{
			deClever(analogOut,digitalOut);
			panelCStatus=0;
		}
		if((deviceRun|localControl)&&(!runStatus)&&panelControl)
		{
		 	alarmFlag=dehStart(digitalIn, digitalOut,analogIn,rangeIn,analogOut,rangeOut,panelControl);
			de_alarm=(enum _alarm)alarmFlag;
			runStatus=1;
		}
		if((!deviceRun)&&(!localControl)&&runStatus&&panelControl)
		{
		 	alarmFlag=dehStop(rangeIn, rangeOut,digitalOut);
			de_alarm=(enum _alarm)alarmFlag;
			deClever(analogOut,digitalOut);
			runStatus=0;
		}
		while(runStatus&&panelControl&&((remoteControl&deviceRun)|localControl))
		if(runStatus)
		{
		 deh_algorithm(analogIn,rangeIn);
		 deh_transfer();
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
	ErrorStatus HSEStartUpStatus; //�����ⲿ���پ�������״̬ö�ٱ�����
	RCC_DeInit();//��λRCC�Ĵ�����Ĭ��ֵ��
	RCC_HSEConfig(RCC_HSE_ON);//���ⲿ�ĸ��پ��� 
	HSEStartUpStatus = RCC_WaitForHSEStartUp();//�ȴ��ⲿ����ʱ��׼����
	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//����AHB
		RCC_PCLK2Config(RCC_HCLK_Div1);//����APB2 
		RCC_PCLK1Config(RCC_HCLK_Div2);//����APB1 
		//RCC_ADCCLKConfig(RCC_PCLK2_Div4);	      
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//PLL=8M*9=72M
		RCC_PLLCmd(ENABLE);//ʱ��PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);//�ȴ�PLL����	      
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);// ����ϵͳʱ��=PLL	  
		while(RCC_GetSYSCLKSource() != 0x08);//���PLLʱ���Ƿ���Ϊϵͳʱ��	       
	}
}

void dataResponseLocal(void)
{
	u16 setpointint=0;
	
	if(dataUbuff[2]==0x02)
    {   
		SetpointValueL[0]= dataUbuff[3];         
	   	SetpointValueL[1]=((float)dataUbuff[7]*100+(float)dataUbuff[8])/10;
    }
	APortCIn(analogIn,rangeIn);
    DPortCIn(digitalIn);
	setpointint = SetpointValueL[1]; 
	tx1[3]  =(u8)((u16)analogIn[RHOUT]/100);	
    tx1[4]  =(u8)((u16)analogIn[RHOUT]%100);
	tx1[5]  =(u8)(setpointint/100);	
    tx1[6]  =(u8)(setpointint%100);
	tx1[7]  =(u8)((u16)analogIn[RHIN]/100);	
    tx1[8]  =(u8)((u16)analogIn[RHIN]%100);
	tx1[9]  =(u8)deviceRun|localControl;	
    tx1[10] =(u8)((u16)analogIn[TIN]%100);
	tx1[11] =(u8)((u16)analogIn[TOUT]/100);
    tx1[12] =(u8)((u16)analogIn[TOUT]%100);
	tx1[19] =1;
    tx1[20] =alarmFlag;
					
    tx1[21]=CRC_check(tx1,3,21);	  
    }	   


void dataProcess(void)
{
    u8 i;

    if(dataCbuff[9]==0x57)
    {
		Re_On=dataCbuff[12];
		RE_Level=dataCbuff[13]*100+dataCbuff[14];
		WS_Level=dataCbuff[15]*100+dataCbuff[16];
    }

    APortCIn(analogIn,rangeIn);
    DPortCIn(digitalIn);
	analogIn[0]=analogIn[0]/10;
	analogIn[1]=analogIn[1]/10;
	analogIn[2]=analogIn[2]/10;
	analogIn[3]=analogIn[3]/10;
	analogIn[4]=analogIn[4]/10;
	analogIn[5]=analogIn[5]/10;
	analogIn[6]=analogIn[6]/10;
	analogIn[7]=analogIn[7]/10;
	analogIn[8]=(analogIn[8]/50-4)/16*48;
	analogIn[9]=(analogIn[9]/50-4)/16*92+28;
	analogIn[12]=analogIn[12]/100;
	analogIn[13]=analogIn[13]/100;
	analogIn[14]=analogIn[14]/100;
	analogIn[15]=analogIn[15]/100;

	getlevel(analogIn[8],analogIn[9],analogIn[12],analogIn[3]);

	TX9[11]=System_On;
	TX9[12]=(u8)deviceRun|localControl;
	TX9[13]=(u8)(analogIn[DSLEVEL]/100);
	TX9[14]=(u8)(((u16)analogIn[DSLEVEL])%100);
	TX9[15]=(u8)(analogIn[SSLEVEL]/100);
	TX9[16]=(u8)(((u16)analogIn[SSLEVEL])%100);
	TX9[17]= tf_flag;

    for(i=0;i<8;i++)
    {
        TX1[i*3+11]=(u8)(analogIn[i]/100);	
        TX1[i*3+12]=(u8)(((u16)analogIn[i])%100);
        TX1[i*3+13]=(u8)(((u32)(analogIn[i]*100))%100);
        
        TX2[i*3+11]=(u8)(analogIn[i+8]/100);	
        TX2[i*3+12]=(u8)(((u16)analogIn[i+8])%100);
        TX2[i*3+13]=(u8)(((u32)(analogIn[i+8]*100))%100);				   
    }			
    
    for(i=0;i<4;i++)
    {
        TX1[i*3+37]=(u8)(((u16)analogOut[i])%100);
        TX1[i*3+38]=(u8)(((u32)(analogOut[i]*100))%100);
        TX1[i*3+39]=(u8)(((u32)(analogOut[i]*10000))%100);
	
        TX2[i*3+37]=(u8)(((u16)analogOut[i+4])%100);
        TX2[i*3+38]=(u8)(((u32)(analogOut[i+4]*100))%100);
		TX2[i*3+39]=(u8)(((u32)(analogOut[i+4]*10000))%100);	 			   
    } 		
    TX1[35]=Digital_handle(digitalIn ,1);
    TX1[36]=Digital_handle(digitalOut,1);
    TX2[35]=Digital_handle(digitalIn ,2);
    TX2[36]=Digital_handle(digitalOut,2);
    TX1[50]=CRC_check(TX1,0,50);
    TX2[50]=CRC_check(TX2,0,50);	
}

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return ch;
}
