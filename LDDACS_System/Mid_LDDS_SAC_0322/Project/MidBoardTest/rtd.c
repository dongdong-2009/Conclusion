#include "stm32f10x.h"
#include <stdio.h>
#include "rtd.h"
#include "io_spi.h"
#include "globle.h"
#include "ads1220.h"
#include "RTD_math.h"
#include "delay.h"

void RTD_init(void)
{
	IO_SpiInit();
	LoadFromFlash();
}

void RTD_OffsetCal(void)
{
	unsigned char calibrateCount = 0;
	static unsigned char tempData_1[3];
	static unsigned char tempData_2[3];

	
	Setup_ADS1220 (ADS1220_MUX_SHORTED, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_SINGLE_SHOT, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_32, ADS1220_USE_PGA, //pt100 32, pt1000 16 
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_250_UA, 1); //pt100 250ua, pt1000 50ua
    Setup_ADS1220 (ADS1220_MUX_SHORTED, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_SINGLE_SHOT, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_32, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_250_UA, 2);//pt100 250ua, pt1000 50ua
    calibrateCount = 0;
    delay_ms(10);
		PEout(0)=0;
		PEout(1)=0;
    ADS1220_Start (1);
    while (calibrateCount < 10)
    {
        while (!ReadConversionData_1);   // Wait for Data Ready interrupt
        ReadConversionData_1 = 0;
        ADS1220_Get_Conversion_Data ((unsigned char *)tempData_1, 1);   // Get the raw data
        ADS1220_Offset_Calibrate_Data ((unsigned char *)tempData_1, 1);        // Send results to calibration function
        calibrateCount++;
        
        // Start next calibration reading?
        if (calibrateCount < 10){
            delay_ms(30);
            ADS1220_Start (1);
        }
    }
    PEout(0)=1;
    
    calibrateCount = 0;
    ADS1220_Start (2);
    while (calibrateCount < 10)
    {
        while (!ReadConversionData_2);   // Wait for Data Ready interrupt
        ReadConversionData_2 = 0;
        ADS1220_Get_Conversion_Data ((unsigned char *)tempData_2, 2);   // Get the raw data
        ADS1220_Offset_Calibrate_Data ((unsigned char *)tempData_2, 2);        // Send results to calibration function
        calibrateCount++;
        
        // Start next calibration reading?
        if (calibrateCount < 10){
            delay_ms(30);
            ADS1220_Start (2);
        }
    }
    PEout(0)=1;
}

void RTD_Start(void)
{
		Setup_ADS1220 (ADS1220_MUX_AIN0_AIN1, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_CONTINUOUS, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_32, ADS1220_USE_PGA, //pt100 32 pt1000 16
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_250_UA, 1); // pt100 250 pt1000 50
    Setup_ADS1220 (ADS1220_MUX_AIN0_AIN1, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_CONTINUOUS, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_32, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_250_UA, 2); // pt100 250 pt1000 50
    
    ReadConversionData_1 = 0;
    ReadConversionData_2 = 0;
    ADS1220_Start (1);      // Only one start needed for Continuous Mode
    ADS1220_Start (2);      // Only one start needed for Continuous Mode
}

void SaveToFlash(void)
{
	  u8 temp=0x5a;
		SPI_Flash_Write((u8*)&ADS1220GainCorrection_1,100,sizeof(ADS1220GainCorrection_1));
		SPI_Flash_Write((u8*)&ADS1220GainCorrection_2,200,sizeof(ADS1220GainCorrection_2));
		SPI_Flash_Write((u8*)&temp,300,sizeof(temp));
}
void LoadFromFlash(void)
{
		u8 temp=0x00;
		
		SPI_Flash_Read((u8*)&temp,300,sizeof(temp));
	   
	  if(temp==0x5a)
		{
			SPI_Flash_Read((u8*)&ADS1220GainCorrection_1,100,sizeof(ADS1220GainCorrection_1));
			SPI_Flash_Read((u8*)&ADS1220GainCorrection_2,200,sizeof(ADS1220GainCorrection_2));
		}
		else
		{
			ADS1220GainCorrection_1=1.0;
			ADS1220GainCorrection_2=1.0;
		}
	
}
void rtd_process_1(void)
{

		PEout(1)=0;
		ADS1220_Get_Conversion_Data_Calibrated ((unsigned char *)tempData_1, 1);   // Get the temperature data with the calibration value subtracted

		code_1 = (((long)tempData_1[0] << 16) + ((long)tempData_1[1] << 8) + (long)tempData_1[2]);   // take 3 bytes of voltage returned and place in word
		temperature_1 = (long)(interpolateTemperatureValue (code_1, PgaGainLevel_1, PT100) * 1000.0);    // Get the temperature and convert into millidegrees C
																																																		// pt100 when using
		ReadConversionData_1 = 0;                        // Clear flag so next conversion is read again.

		if (avgCount_1 == 0)
		{
			avgTemp_1 = (float)temperature_1;
			avgRaw_1 = (float)rawData_1;
		}
		else
		{
			avgTemp_1 += (float)temperature_1;
			avgRaw_1 += (float)rawData_1;
			
		}
		avgCount_1 ++;

		if (avgCount_1 == SAMPLES)
		{
			avgCount_1 = 0;
			temperature_1 = (long)(avgTemp_1 / SAMPLES);
			if(temperature_1>200000)temperature_1=0;
			rawData_1 = (long)(avgRaw_1 / SAMPLES);

			if(!PDin(14))
			{
					GainCal_1 = 0;
					 ADS1220GainCorrection_1 = MeasuredGainCodeValue_Pt100_150R / rawData_1; // MeasuredGainCodeValue_Pt100_150R or MeasuredGainCodeValue_Pt1000_1K5
					SaveToFlash();
				while(!PDin(14));
			}
		}
		PEout(1)=1;
}

void rtd_process_2(void)
{

	PEout(0)=0;
	ADS1220_Get_Conversion_Data_Calibrated ((unsigned char *)tempData_2, 2);   // Get the temperature data with the calibration value subtracted

	code_2 = (((long)tempData_2[0] << 16) + ((long)tempData_2[1] << 8) + (long)tempData_2[2]);   // take 3 bytes of voltage returned and place in word

	temperature_2 = (long)(interpolateTemperatureValue (code_2, PgaGainLevel_2, PT100) * 1000.0);    // Get the temperature and convert into millidegrees C

	ReadConversionData_2 = 0;                        // Clear flag so next conversion is read again.

	if (avgCount_2 == 0)
	{
		avgTemp_2 = (float)temperature_2;
		avgRaw_2 = (float)rawData_2;
	}
	else
	{
	 avgTemp_2 += (float)temperature_2;
		avgRaw_2 += (float)rawData_2;
	}
	avgCount_2 ++;

	if (avgCount_2 == SAMPLES)
	{
		avgCount_2 = 0;
		temperature_2 = (long)(avgTemp_2 / SAMPLES);
		if(temperature_2>200000)temperature_2=0;
		rawData_2 = (long)(avgRaw_2 / SAMPLES);
		if(!PDin(15))
		{
				GainCal_2 = 0;
				ADS1220GainCorrection_2 = MeasuredGainCodeValue_Pt100_150R / rawData_2;
				SaveToFlash();
				while(!PDin(15));              
		}
	}
	PEout(0)=1;
    
}

