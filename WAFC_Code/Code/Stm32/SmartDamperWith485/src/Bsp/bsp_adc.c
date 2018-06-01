#include "bsp_adc.h"

u16 _ADC_buf[ADC_BUF_SIZE];
HDTimer _ADC_Refresh_Time;

void Current_ADC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure; 
	DMA_InitTypeDef DMA_Structure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//reset ADC1
	ADC_DeInit(ADC1);
	//set ADC1 runs independently
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 
	//disable ADC scan function to work on one channel
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//setting adc convertion to not use external trigger
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	//setting adc convertion continuous once previous has done
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//setting data alignment to be right aglignment
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//setting number of channels to be convered
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	//set ADC channel 4 as the sampling channel
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);
	
	//enable ADC1
	ADC_Cmd(ADC1, ENABLE);
	//reset calibration 
	ADC_ResetCalibration(ADC1);
	//wait until calibration register is reset
	while(ADC_GetResetCalibrationStatus(ADC1));
	//start to calibrate
	ADC_StartCalibration(ADC1);
	//wait until calibration finished
	while(ADC_GetCalibrationStatus(ADC1));
	//enable ADC conversion
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	//enable adc dma function
	ADC_DMACmd(ADC1,ENABLE);
	//set clock for dma on AHB
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1);
	//select ADC's adress as peripheral address
	DMA_Structure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
	//select argument address as memeory address
	DMA_Structure.DMA_MemoryBaseAddr = (u32)_ADC_buf;
	//select dma direction from peripheral to memory
	DMA_Structure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//select number of items to move in to be as assigned
	DMA_Structure.DMA_BufferSize = ADC_BUF_SIZE;
	//set peripheral as fixed address
	DMA_Structure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//set memory as increasing address
	DMA_Structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//set peripheral data size as u16 halfword
	DMA_Structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//set memory data size as u16 halfword
	DMA_Structure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//set DMA work continuously at the end of one turn
	DMA_Structure.DMA_Mode = DMA_Mode_Circular;
	//set priority of this DMA task to be very high
	DMA_Structure.DMA_Priority = DMA_Priority_VeryHigh;
	//disable memory to memory DMA
	DMA_Structure.DMA_M2M = DMA_M2M_Disable;
	//select DMA1_Channel1 because ADC1 is in this channel
	DMA_Init(DMA1_Channel1,&DMA_Structure);
	//enable DMA
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	//setting DMA interrupt
	DMA_ClearITPendingBit(DMA1_IT_GL1);
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void DMA1_Channel1_IRQHandler(void) //runs for 27.8us
{
	if(DMA_GetITStatus(DMA1_IT_TC1)==SET)
	{
		_ADC_Refresh_Time = GetTimeHD();
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
//	if(DMA_GetITStatus(DMA1_IT_GL1)==SET)
//	{
//		DMA_ClearITPendingBit(DMA1_IT_GL1);
//	}
	if(DMA_GetITStatus(DMA1_IT_HT1)==SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_HT1);
	}
	if(DMA_GetITStatus(DMA1_IT_TE1)==SET)
	{
		DMA_ClearITPendingBit(DMA1_IT_TE1);
	}
}

HDTimer Get_ADC_Refresh_Time(void)
{
	return _ADC_Refresh_Time;
}


