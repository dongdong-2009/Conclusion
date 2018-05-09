#include "LCD.h"
#include "font.h"
#include "stdlib.h"

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 

void LCD_WR_DATA(u16 data)
{
	LCD->LCD_RAM = data;
}

void LCD_WR_REG(u16 reg)
{
	LCD->LCD_REG = reg;
}

void LCD_WR_REG_DATA(int reg,int data)
{
	LCD->LCD_REG = reg;
	LCD->LCD_RAM = data;
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	//set column��ַ
	LCD_WR_REG(0x002A);
	LCD_WR_DATA(x1>>8);             //����ʼ��ַ��λ
	LCD_WR_DATA(x1&0x00ff);
	LCD_WR_DATA(x2>>8);             //�н�����ַ��λ
	LCD_WR_DATA(x2&0x00ff);
  
	//����page(row)��ַ
	LCD_WR_REG(0x002b);
	LCD_WR_DATA(y1>>8);            //����ʼ��ַ��λ
	LCD_WR_DATA(y1&0x00ff);
	LCD_WR_DATA(y2>>8);            //�н�����ַ��λ
	LCD_WR_DATA(y2&0x00ff);
}

//Write Memory Start
void LCD_WriteRAM_Prepare(void)
{
	//Transfer image information from the host processor interface to the SSD1963 starting at the location provided by Set Column Address
	LCD_WR_REG(0x2c); 
}

void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	LCD_WR_REG(0x002A);	
	LCD_WR_DATA(Xpos>>8);	    
	LCD_WR_DATA(Xpos&0x00ff);
	LCD_WR_DATA(479>>8);	    
	LCD_WR_DATA(479&0x00ff);
	
	LCD_WR_REG(0x002b);	
	LCD_WR_DATA(Ypos>>8);	    
	LCD_WR_DATA(Ypos&0x00ff);
	LCD_WR_DATA(271>>8);	    
	LCD_WR_DATA(271&0x00ff); 
}

//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=LCD_W;
	totalpoint*=LCD_H; 	          //�õ��ܵ���
	LCD_SetCursor(0x00,0x00);	    //���ù��λ�� 
	LCD_WriteRAM_Prepare();       //��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD_WR_DATA(color);
	}
}

u16 LCD_RD_DATA(void)
{
	return LCD->LCD_RAM;
}

//���룺�Ĵ�����ַ
//���������������
u16 LCD_ReadReg(u8 LCD_Reg)
{
	u16 myid=0;
	u8 x=0;
	while(x<5&&((myid==0)||(myid==0xffff)))   //��5��
	{
		LCD_WR_REG_DATA(0x0000,0x0001);
		delay_us(200);
		LCD_WR_REG(LCD_Reg);
		delay_us(5);
		myid=LCD_RD_DATA();
		x++;
	}
	return myid;
}

//����:x,y����
u16 LCD_ReadPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);
	LCD_WriteRAM_Prepare();
	return LCD_RD_DATA();
}

//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA(POINT_COLOR); 
}

void LCD_DrawFastPoint(u16 x,u16 y,u16 color)
{
	LCD_SetCursor(x,y);		  //���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA(color);     //�������ɫ
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	
	//�ж�x������
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	
	//�ж�y������
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	
	
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);                           //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  	LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

//��ָ��λ����ʾһ������(16*16��С)
void showhanzi16(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j,k;
	const unsigned char *temp=hanzi16;    
	temp+=index*32;	
	for(j=0;j<16;j++)
	{
		LCD_SetCursor(x,y+j);
		LCD_WriteRAM_Prepare();	//��ʼд��GRAM
		for(k=0;k<2;k++)
		{
			for(i=0;i<8;i++)
			{ 		     
			 	if((*temp&(1<<i))!=0)
				{
					LCD_WR_DATA(POINT_COLOR);
				} 
				else
				{
					LCD_WR_DATA(BACK_COLOR);
				}   
			}
			temp++;
		}
	 }
}


//��ָ��λ����ʾһ������(32*32��С)
void showhanzi32(unsigned int x,unsigned int y,unsigned char index)	
{  
	unsigned char i,j,k;
	const unsigned char *temp=hanzi32;    
	temp+=index*128;	
	for(j=0;j<32;j++)
	{
		LCD_SetCursor(x,y+j);
		LCD_WriteRAM_Prepare();	//��ʼд��GRAM
		for(k=0;k<4;k++)
		{
			for(i=0;i<8;i++)
			{ 		     
			 	if((*temp&(1<<i))!=0)
				{
					LCD_WR_DATA(POINT_COLOR);
				} 
				else
				{
					LCD_WR_DATA(BACK_COLOR);
				}   
			}
			temp++;
		}
	 }
}	

void showimage(u16 x,u16 y) //��ʾ40*40ͼƬ
{  
	u16 i,j,k;
	u16 da;
	k=0;
	for(i=0;i<40;i++)
	{	
		LCD_SetCursor(x,y+i);
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
		for(j=0;j<40;j++)
		{
			da=qqimage[k*2+1];
			da<<=8;
			da|=qqimage[k*2];
			LCD_WR_DATA(da);		
			k++;
		}
	}
}

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
  u8 temp,t1,t;
	u16 z=0;
	u16 x0=x;
	u16 colortemp=POINT_COLOR;      
	u16 qyt=0;
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(size==16)
	{ 
		qyt=16;	 		
	}
	else
	{ 
		qyt=64;	
	}
	z=num;
	z*=qyt;  
	//���ô���		   
	
	//�ǵ��ӷ�ʽ
	if(!mode)
	{
		for(t=0;t<qyt;t++)
	  {   
			if(size==16)
			{
				temp=asc1608[z];  //����1608����
			}
			else 
			{
				temp=asc3216[z];		 //����3216���� 	                          
			}
			z++;     
	    for(t1=0;t1<8;t1++)
			{			    
		    if(temp&0x01)
					POINT_COLOR=colortemp;
				else 
					POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp>>=1;
				x++;
				//��������
				if(x>=LCD_W)
				{
					POINT_COLOR=colortemp;
					return;
				}
				if((x-x0)==(size/2))
				{
					x=x0;
					y++;
					if(y>=LCD_H)     //��������
					{
						POINT_COLOR=colortemp;
						return;
					}
					break;
				}
			}  	 
	  }    
	}
	else//���ӷ�ʽ
	{
		for(t=0;t<qyt;t++)
	  {   
			if(size==16)
			{
				temp=asc1608[z];  //����1608����
			}
			else 
			{
				temp=asc3216[z];		 //����3216���� 	                          
			}
			z++;     
	    for(t1=0;t1<8;t1++)
			{
				if(temp&0x01)LCD_DrawPoint(x,y);				
				temp>>=1;
				x++;
				if(x>=LCD_W)//��������
				{
					POINT_COLOR=colortemp;
					return;
				}
				if((x-x0)==(size/2))
				{
					x=x0;
					y++;
					if(y>=LCD_H)//��������
					{
						POINT_COLOR=colortemp;
						return;
					}
					break;
				}
			}  	 
	  }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
} 

//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
    }  
}

//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}
			else 
				enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
}


//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 

//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
	xlen=ex-sx+1;	   
	for(i=sy;i<=ey;i++)
	{									   
	 	LCD_SetCursor(sx,i);      				//���ù��λ�� 
		LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
		for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//���ù��λ�� 	    
	}
} 

//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 		//�õ����Ŀ��
	height=ey-sy+1;		//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//д������ 
	}	  
} 


//CS---0 Ƭѡ��Ч
//WR---0 RD---1:д����   WR---1 RD---0��������
//RESETһֱΪ�� �����͵���оƬ����
void LCD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;

	//PD7---LCD_CS(NE1)  PD4---LCD_RD(FSMC_NOE)   PD5---LCD_WR(FSMC_NWE)   PD13---LCD_RS(A18)  PC6---LCD_LED  PB1---LCD_RST
	//������ DB0-DB15�� PD14,PD15,PD0,PD1,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,PD8,PD9,PD10
	
  // Enable FSMC, GPIOD, GPIOE, GPIOB clocks
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);

	// Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.07(NE1), PD.08(D13),
  // PD.09(D14), PD.10(D15), PD.13(A18), PD.14(D0), PD.15(D1) as alternate 
  // function push pull 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| 
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
  // PE.14(D11), PE.15(D12) as alternate function push pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                   GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                   GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  //PB1 --> LCD_RST
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
	readWriteTiming.FSMC_AddressSetupTime = 2;	     //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
  readWriteTiming.FSMC_AddressHoldTime = 1;	       //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
  readWriteTiming.FSMC_DataSetupTime = 10;		     // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
  readWriteTiming.FSMC_BusTurnAroundDuration = 1;
  readWriteTiming.FSMC_CLKDivision = 1;
  readWriteTiming.FSMC_DataLatency = 1;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
    

	writeTiming.FSMC_AddressSetupTime = 2;	       //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  
  writeTiming.FSMC_AddressHoldTime = 1;	         //��ַ����ʱ�䣨A		
  writeTiming.FSMC_DataSetupTime = 10;		       //���ݱ���ʱ��Ϊ4��HCLK	
  writeTiming.FSMC_BusTurnAroundDuration =1;
  writeTiming.FSMC_CLKDivision =1;
  writeTiming.FSMC_DataLatency =1;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 

 
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;										       //��������ʹ��NE1,Sector1  HADDR[27,26]=00
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;         // ���������ݵ�ַ
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;                     // FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;           //�洢�����ݿ��Ϊ16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;        // FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	               //�洢��дʹ��
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;                    //��дʹ�ò�ͬ��ʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;                   //��дʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;                           //дʱ��

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����		

  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // ʹ��BANK1 
	
	//lcd�ϵ縴λ
	LCD_REST=0;		 
 	delay_ms(50); // delay 20 ms 
  LCD_REST=1;		 
 	delay_ms(50); // delay 20 ms 	
	
	LCD_WR_REG(0x00E2);	       //PLL multiplier, set PLL clock to 120M ����PLL�ļĴ���
	LCD_WR_DATA(0x002d);	     //N=0x36 for 6.5M, 0x23 for 10M crystal ���ñ�Ƶ��M 
	LCD_WR_DATA(0x0002);       //���÷�Ƶ��N
	LCD_WR_DATA(0x0004);       //ʹ��MN PLL=INCLK*(M+1)/(N+1)
	
	LCD_WR_REG(0x00E0);        // PLL enable   PLLʹ�ܼĴ���
	LCD_WR_DATA(0x0001);       //ʹ��reference clocl as system clock ͬʱʹ��PLL
	delay_ms(1);               //wait 100us  let the PLL stable
	LCD_WR_REG(0x00E0);        //��дPLLʹ�ܼĴ���
	LCD_WR_DATA(0x0003);       //Use PLL as system clock  and Enable PLL
	delay_ms(5);
	
	//The display module performs a software reset only the configuration register will be reset
	LCD_WR_REG(0x0001);        // software reset The host processor must wait 5ms before sending any new coommands to SSD1963 following this command
	delay_ms(5);
	
	//��������ʱ�ӼĴ�������Ҫ3���ֽ������ã���λ��ǰ
	LCD_WR_REG(0x00E6);	       //PLL setting for PCLK(pixel clock), depends on resolution
	LCD_WR_DATA(0x0000);       //PLCK = PLL *((LCDC_FPR+1)/2^20);
	LCD_WR_DATA(0x00ff);       //PLCK = PLL *((0XFFBE+1)/2^20);
	LCD_WR_DATA(0x00be);
	
	//����LCD����ʾģʽ����Ҫ������Ļ��С��LCD�ĵ�·���Ʒ�����ƥ�䣬����ο�datasheet
	LCD_WR_REG(0x00B0);	            //LCD SPECIFICATION  set the LCD pannel mode (RGB TFT and TTL) and pad strength
	LCD_WR_DATA(0x0020);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA((HDP>>8)&0X00FF);   //Set HDP  ˮƽ��С  ˫�ֽڣ���λ��ǰ
	LCD_WR_DATA(HDP&0X00FF);
  LCD_WR_DATA((VDP>>8)&0X00FF);   //Set VDP  ��ֱ��С
	LCD_WR_DATA(VDP&0X00FF);
  LCD_WR_DATA(0x0000);            //����RGB˳����TFT�ӿ�
	delay_ms(5);
	
	//����ˮƽ��ʾʱ�����
	LCD_WR_REG(0x00B4);	                    //HSYNC
	LCD_WR_DATA((HT>>8)&0X00FF);            //Set HT
	LCD_WR_DATA(HT&0X00FF);
	LCD_WR_DATA((HPS>>8)&0X00FF);           //Set HPS
	LCD_WR_DATA(HPS&0X00FF);
	LCD_WR_DATA(HPW);			                  //Set HPW
	LCD_WR_DATA((LPS>>8)&0X00FF);           //SetLPS
	LCD_WR_DATA(LPS&0X00FF);
	LCD_WR_DATA(0x0000);
	
	//���ô�ֱ��ʾʱ�����
	LCD_WR_REG(0x00B6);	                    //VSYNC
	LCD_WR_DATA((VT>>8)&0X00FF);            //Set VT
	LCD_WR_DATA(VT&0X00FF);
	LCD_WR_DATA((VPS>>8)&0X00FF);           //Set VPS
	LCD_WR_DATA(VPS&0X00FF);
	LCD_WR_DATA(VPW);			                  //Set VPW
	LCD_WR_DATA((FPS>>8)&0X00FF);           //Set FPS
	LCD_WR_DATA(FPS&0X00FF);
	
	LCD_WR_REG(0x0036);                     //���ô�������ȡָ��˳�򣬿���ʡ�ԣ��ϵ�Ĭ��Ϊ0
	LCD_WR_DATA(0x0000);                    //A[5]=0 Page/Column order (PDR=0)   Normal Mode
	
	LCD_WR_REG(0x00F0);                     //pixel data interface
	LCD_WR_DATA(0x0003);                    //16-bit
	
	delay_ms(5);
	
	LCD_WR_REG(0x0029);                     //display on Show the image on the display device
	
	//Enter invert mode
	LCD_WR_REG(0x0021);                     //������ɫ��תģʽ      
  
	//show the image post processor
	LCD_WR_REG(0x00BC);                     //����ͼ����ڴ���
  LCD_WR_DATA(0x0080);                    //�Աȶ�
  LCD_WR_DATA(0x0080);                    //����
  LCD_WR_DATA(0x0080);                    //���Ͷ�ֵ
  LCD_WR_DATA(0x0001);                    //���������
	
	LCD_WR_REG(0x00BE);                     //set PWM for B/L
	LCD_WR_DATA(0x0006);                    //Set the PWM frequency in system clock PWM = PLL clock/(256*PWMF[7:0])/256
	LCD_WR_DATA(0x00f0);                    //set the PWM duty cycle PWM duty cycle = PWM[7:0]/256;
	LCD_WR_DATA(0x0001);
	LCD_WR_DATA(0x00f0);
	LCD_WR_DATA(0x0000);
	LCD_WR_DATA(0x0000);
	
	//set the threshold for each level of power saving
	LCD_WR_REG(0xD4);
	//TH1 = display width * display height * 3 * 0.1 /16 
  //480*272 * 3 * 0.1 /16 =990H
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x09); 
  LCD_WR_DATA(0x90);
	
	//TH2 = display width * display height * 3 * 0.25 /16
  //480*272 * 3 * 0.25 /16 =17E8H
  LCD_WR_DATA(0x00); 
  LCD_WR_DATA(0x17);  
  LCD_WR_DATA(0xE8); 
	
	//TH3 = display width * display height * 3 * 0.6 /16 
  //480*272 * 3 * 0.6 /16 =3960H
  LCD_WR_DATA(0x00);  
  LCD_WR_DATA(0x39); 
  LCD_WR_DATA(0x60);
	
	//SET the dynamic backlight control configuration
	LCD_WR_REG(0x00d0); 
	LCD_WR_DATA(0x000d);                   //enable
	
	//----------LCD RESET---GPIO0-------------------//
	//Set GPIO configuration
	LCD_WR_REG(0x00B8);
	LCD_WR_DATA(0x0007);    //GPIO[3]=input GPIO[2:0]=output
	LCD_WR_DATA(0x0001);    //GPIO0 normal

	//set GPIO value for GPIO configuratd as output
	LCD_WR_REG(0x00BA);
	LCD_WR_DATA(0x0000); 
}
