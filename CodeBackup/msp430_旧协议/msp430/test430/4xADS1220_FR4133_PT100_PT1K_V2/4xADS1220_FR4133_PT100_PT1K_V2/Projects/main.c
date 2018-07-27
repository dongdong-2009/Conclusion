
#include "api.h"
#define SAMPLES       20
//const float MeasuredGainCodeValue = 7868944.1883;   // for 380 Ohm resistor
const float MeasuredGainCodeValue_Pt100_150R = 6100805.09090909; // for 150 Ohm resistor
//const float MeasuredGainCodeValue_Pt1000_1K5 = 6710886.0;      // for 1500 Ohm resistor
const float MeasuredGainCodeValue_Pt1000_1K5 = 7381974.6;      // for 1650 Ohm resistor
                                                               //new value = 1k5 value * (newref/1k5)
const float Rref_Pt100  = 3300.0;                          // reference resistor value on the board is 3.24k Ohm
const float Rref_Pt1000 = 15000.0;
unsigned long dacValueForTemp_uA = 0;
unsigned char calibrateCount = 0;

static unsigned char tempData_1[3];
static unsigned char tempData_2[3];
static unsigned char tempData_3[3];
static unsigned char tempData_4[3];

long temperature_1;
long temperature_2;
long temperature_3;
long temperature_4;

long code_1;
long code_2;
long code_3;
long code_4;

float avgTemp_1;
float avgTemp_2;
float avgTemp_3;
float avgTemp_4;

float avgRaw_1;
float avgRaw_2;
float avgRaw_3;
float avgRaw_4;

unsigned char avgCount_1 = 0;
unsigned char avgCount_2 = 0;
unsigned char avgCount_3 = 0;
unsigned char avgCount_4 = 0;

unsigned char ReadConversionData_1 = 0;
unsigned char ReadConversionData_2 = 0;
unsigned char ReadConversionData_3 = 0;
unsigned char ReadConversionData_4 = 0;

unsigned char GainCal_1 = 0;
unsigned char GainCal_2 = 0;
unsigned char GainCal_3 = 0;
unsigned char GainCal_4 = 0;

extern long rawData_1;
extern long rawData_2;
extern long rawData_3;
extern long rawData_4;

extern float PgaGainLevel_1;
extern float PgaGainLevel_2;
extern float PgaGainLevel_3;
extern float PgaGainLevel_4;

extern RESULT send_result;
RESULT adc_result = {
    .flag = 0xaa55,
    .temp_1  = 25000,
    .temp_2  = 25000,
    .temp_3  = 25000,
    .temp_4  = 25000,
};
void Setup_IO (void);
void rtd_process_1(void);
void rtd_process_2(void);
void rtd_process_3(void);
void rtd_process_4(void);
void main (void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer  
    __gie_disable();
    BSP_InitBoard();  
    BSP_InitLeds();
    GpioInit();
    BSP_TURN_ON_LED1();
    BSP_TURN_ON_LED2();
    BSP_TURN_ON_LED3();
    BSP_TURN_ON_LED4();
    
    IO_SpiInit();
    send_result = adc_result;
    spi_slave_init();
    GetSavedData();
//----------------------------------------------------------------------------------------------------------------------------------------   
    Setup_ADS1220 (ADS1220_MUX_SHORTED, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_SINGLE_SHOT, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA, //pt100 32, pt1000 16 
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 1); //pt100 250ua, pt1000 50ua
    Setup_ADS1220 (ADS1220_MUX_SHORTED, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_SINGLE_SHOT, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 2);//pt100 250ua, pt1000 50ua
    Setup_ADS1220 (ADS1220_MUX_SHORTED, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_SINGLE_SHOT, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 3);//pt100 250ua, pt1000 50ua
    Setup_ADS1220 (ADS1220_MUX_SHORTED, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_SINGLE_SHOT, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 4);//pt100 250ua, pt1000 50ua
    calibrateCount = 0;
    BSP_DELAY_USECS(10000);
    Setup_IO();
    __gie_enable();
    
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
            BSP_DELAY_USECS(10000);
            ADS1220_Start (1);
        }
    }
    BSP_TURN_OFF_LED1();
    
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
            BSP_DELAY_USECS(10000);
            ADS1220_Start (2);
        }
    }
    BSP_TURN_OFF_LED2();

    calibrateCount = 0;
    ADS1220_Start (3);
    while (calibrateCount < 10)
    {
        while (!ReadConversionData_3);   // Wait for Data Ready interrupt
        ReadConversionData_3 = 0;
        ADS1220_Get_Conversion_Data ((unsigned char *)tempData_3, 3);   // Get the raw data
        ADS1220_Offset_Calibrate_Data ((unsigned char *)tempData_3, 3);        // Send results to calibration function
        calibrateCount++;
        
        // Start next calibration reading?
        if (calibrateCount < 10){
            BSP_DELAY_USECS(10000);
            ADS1220_Start (3);
        }
    }
    BSP_TURN_OFF_LED3();
    
    calibrateCount = 0;
    ADS1220_Start (4);
    while (calibrateCount < 10)
    {
        while (!ReadConversionData_4);   // Wait for Data Ready interrupt
        ReadConversionData_4 = 0;
        ADS1220_Get_Conversion_Data ((unsigned char *)tempData_4, 4);   // Get the raw data
        ADS1220_Offset_Calibrate_Data ((unsigned char *)tempData_4, 4);        // Send results to calibration function
        calibrateCount++;
        
        // Start next calibration reading?
        if (calibrateCount < 10){
            BSP_DELAY_USECS(10000);
            ADS1220_Start (4);
        }
    }
    BSP_TURN_OFF_LED4();
 //-----------------------------------------------------------------------------------------------------------------------------------   
    Setup_ADS1220 (ADS1220_MUX_AIN0_AIN1, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_CONTINUOUS, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA, //pt100 32 pt1000 16
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 1); // pt100 250 pt1000 50
    Setup_ADS1220 (ADS1220_MUX_AIN0_AIN1, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_CONTINUOUS, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 2); // pt100 250 pt1000 50
    Setup_ADS1220 (ADS1220_MUX_AIN0_AIN1, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_CONTINUOUS, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 3); // pt100 250 pt1000 50
    Setup_ADS1220 (ADS1220_MUX_AIN0_AIN1, ADS1220_OP_MODE_NORMAL,
                   ADS1220_CONVERSION_CONTINUOUS, ADS1220_DATA_RATE_20SPS, ADS1220_GAIN_16, ADS1220_USE_PGA,
                   ADS1220_IDAC1_AIN3, ADS1220_IDAC2_AIN2, ADS1220_IDAC_CURRENT_50_UA, 4); // pt100 250 pt1000 50
    
    ReadConversionData_1 = 0;
    ReadConversionData_2 = 0;
    ReadConversionData_3 = 0;
    ReadConversionData_4 = 0;
    ADS1220_Start (1);      // Only one start needed for Continuous Mode
    ADS1220_Start (2);      // Only one start needed for Continuous Mode
    ADS1220_Start (3);      // Only one start needed for Continuous Mode
    ADS1220_Start (4);      // Only one start needed for Continuous Mode
    while(1)
    {
        rtd_process_1();
        rtd_process_2();
        rtd_process_3();
        rtd_process_4();
        __no_operation();
    }
}

void Setup_IO (void)
{
    P2DIR &= ~(ADS_DRDY_N_1 | ADS_DRDY_N_2 | ADS_DRDY_N_3 | ADS_DRDY_N_4);   // Input Pins
    P2IES |=  (ADS_DRDY_N_1 | ADS_DRDY_N_2 | ADS_DRDY_N_3 | ADS_DRDY_N_4);   // High to Low Edge
    P2IFG = 0;                                            // Clear any pending interrupts
    P2IE  |=  (ADS_DRDY_N_1 | ADS_DRDY_N_2 | ADS_DRDY_N_3 | ADS_DRDY_N_4);  
    
}

void rtd_process_1(void)
{
    if (ReadConversionData_1)
    {
        BSP_TURN_ON_LED1();
        //StartConversion = 1;             // Start next conversion immediately
        ADS1220_Get_Conversion_Data_Calibrated ((unsigned char *)tempData_1, 1);   // Get the temperature data with the calibration value subtracted
        
        code_1 = (((long)tempData_1[0] << 16) + ((long)tempData_1[1] << 8) + (long)tempData_1[2]);   // take 3 bytes of voltage returned and place in word
        // In case we extend the time between samples in the future, we will still need to keep the DAC
        // from timing out by sending a NOP command every time the loop is processed.
 //--------------------------------------------------------------------------------------------------------------------------------------------------------------       
        temperature_1 = (long)(interpolateTemperatureValue (code_1, PgaGainLevel_1, PT1000) * 1000.0);    // Get the temperature and convert into millidegrees C
                                                                                                          // pt100 when using
        ReadConversionData_1 = 0;                        // Clear flag so next conversion is read again.
        
        // Collect the measured values for SAMPLES_PER_DAC_ADJUSTMENT(16) measurements to average
        if (avgCount_1 == 0)
        {
            // Erase all previous value, as this is the first measurement for this average block
            avgTemp_1 = (float)temperature_1;
            avgRaw_1 = (float)rawData_1;
        }
        else
        {
            // Add values from this measurement into the average block
            avgTemp_1 += (float)temperature_1;
            avgRaw_1 += (float)rawData_1;
            
        }
        avgCount_1 ++;
        
        // If this is the last measurement, calculate the averages and set the system to print
        if (avgCount_1 == SAMPLES)
        {
            avgCount_1 = 0;
            temperature_1 = (long)(avgTemp_1 / SAMPLES);
            if(temperature_1>200000)temperature_1=0;
            rawData_1 = (long)(avgRaw_1 / SAMPLES);
            __gie_disable();
            adc_result.temp_1 = temperature_1;
            __gie_enable();
            //CalVoltage = (long)(avgOffset / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainVoltage = (long)(avgGain / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainCalibrateValue = (long)(avgGainCal / SAMPLES_PER_DAC_ADJUSTMENT);
            
            // Perform Gain Calibration when the user pushes the button on the top of the device.
            // The user MUST have modified the code to place the expected results into the MeasuredGainCodeValue
            //  variable at the top of main.c. The user is expected to place a known resistor value in place of the
            //  RTD and perform gain calibration to determine the system level gain correction. This value will be
            //  stored into flash memory for future use.
            //if (GainCal_1)
            if(!(P1IN & BIT2))
            {
                GainCal_1 = 0;
                BSP_TURN_ON_LED1();
                //-------------------------------------------------------------------------------------------------
                ConfigAndSaved.ADS1220GainCorrection_1 = MeasuredGainCodeValue_Pt1000_1K5 / rawData_1; // MeasuredGainCodeValue_Pt100_150R or MeasuredGainCodeValue_Pt1000_1K5
                SaveData();
                while(!(P1IN & BIT2));
                BSP_TURN_OFF_LED1();
            }
        }
        BSP_TURN_OFF_LED1();
    }
}

void rtd_process_2(void)
{
    if (ReadConversionData_2)
    {
        BSP_TURN_ON_LED2();
        //StartConversion = 1;             // Start next conversion immediately
        ADS1220_Get_Conversion_Data_Calibrated ((unsigned char *)tempData_2, 2);   // Get the temperature data with the calibration value subtracted
        
        code_2 = (((long)tempData_2[0] << 16) + ((long)tempData_2[1] << 8) + (long)tempData_2[2]);   // take 3 bytes of voltage returned and place in word
        // In case we extend the time between samples in the future, we will still need to keep the DAC
        // from timing out by sending a NOP command every time the loop is processed.
        
        temperature_2 = (long)(interpolateTemperatureValue (code_2, PgaGainLevel_2, PT1000) * 1000.0);    // Get the temperature and convert into millidegrees C
        
        ReadConversionData_2 = 0;                        // Clear flag so next conversion is read again.

        // Collect the measured values for SAMPLES_PER_DAC_ADJUSTMENT(16) measurements to average
        if (avgCount_2 == 0)
        {
            // Erase all previous value, as this is the first measurement for this average block
            avgTemp_2 = (float)temperature_2;
            avgRaw_2 = (float)rawData_2;
        }
        else
        {
            // Add values from this measurement into the average block
            avgTemp_2 += (float)temperature_2;
            avgRaw_2 += (float)rawData_2;
        }
        avgCount_2 ++;
        
        // If this is the last measurement, calculate the averages and set the system to print
        if (avgCount_2 == SAMPLES)
        {
            avgCount_2 = 0;
            temperature_2 = (long)(avgTemp_2 / SAMPLES);
            if(temperature_2>200000)temperature_2=0;
            rawData_2 = (long)(avgRaw_2 / SAMPLES);
            __gie_disable();
            
            adc_result.temp_2 = temperature_2;
            __gie_enable();
            //CalVoltage = (long)(avgOffset / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainVoltage = (long)(avgGain / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainCalibrateValue = (long)(avgGainCal / SAMPLES_PER_DAC_ADJUSTMENT);
            
            // Perform Gain Calibration when the user pushes the button on the top of the device.
            // The user MUST have modified the code to place the expected results into the MeasuredGainCodeValue
            //  variable at the top of main.c. The user is expected to place a known resistor value in place of the
            //  RTD and perform gain calibration to determine the system level gain correction. This value will be
            //  stored into flash memory for future use.
            //if (GainCal_2)
            if(!(P1IN & BIT3))
            {
                GainCal_2 = 0;
                BSP_TURN_ON_LED2();
                ConfigAndSaved.ADS1220GainCorrection_2 = MeasuredGainCodeValue_Pt1000_1K5 / rawData_2;
                SaveData();
                while(!(P1IN & BIT3));
                BSP_TURN_OFF_LED2();
            }
        }
        BSP_TURN_OFF_LED2();
    }
}

void rtd_process_3(void)
{
    if (ReadConversionData_3)
    {
        BSP_TURN_ON_LED3();
        //StartConversion = 1;             // Start next conversion immediately
        ADS1220_Get_Conversion_Data_Calibrated ((unsigned char *)tempData_3, 3);   // Get the temperature data with the calibration value subtracted
        
        code_3 = (((long)tempData_3[0] << 16) + ((long)tempData_3[1] << 8) + (long)tempData_3[2]);   // take 3 bytes of voltage returned and place in word
        // In case we extend the time between samples in the future, we will still need to keep the DAC
        // from timing out by sending a NOP command every time the loop is processed.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------        
        temperature_3 = (long)(interpolateTemperatureValue (code_3, PgaGainLevel_3, PT1000) * 1000.0);    // Get the temperature and convert into millidegrees C
        
        ReadConversionData_3 = 0;                        // Clear flag so next conversion is read again.

        // Collect the measured values for SAMPLES_PER_DAC_ADJUSTMENT(16) measurements to average
        if (avgCount_3 == 0)
        {
            // Erase all previous value, as this is the first measurement for this average block
            avgTemp_3 = (float)temperature_3;
            avgRaw_3 = (float)rawData_3;
        }
        else
        {
            // Add values from this measurement into the average block
            avgTemp_3 += (float)temperature_3;
            avgRaw_3 += (float)rawData_3;
            
        }
        avgCount_3 ++;
        
        // If this is the last measurement, calculate the averages and set the system to print
        if (avgCount_3 == SAMPLES)
        {
            avgCount_3 = 0;
            temperature_3 = (long)(avgTemp_3 / SAMPLES);
            if(temperature_3>200000)temperature_3=0;
            rawData_3 = (long)(avgRaw_3 / SAMPLES);
            __gie_disable();
            
            adc_result.temp_3 = temperature_3;
            __gie_enable();
            //CalVoltage = (long)(avgOffset / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainVoltage = (long)(avgGain / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainCalibrateValue = (long)(avgGainCal / SAMPLES_PER_DAC_ADJUSTMENT);
            
            // Perform Gain Calibration when the user pushes the button on the top of the device.
            // The user MUST have modified the code to place the expected results into the MeasuredGainCodeValue
            //  variable at the top of main.c. The user is expected to place a known resistor value in place of the
            //  RTD and perform gain calibration to determine the system level gain correction. This value will be
            //  stored into flash memory for future use.
            //if (GainCal_2)
            if(!(P1IN & BIT6))
            {
                GainCal_3 = 0;
                BSP_TURN_ON_LED3();
                //--------------------------------------------------------------------------------------------------------------------------------------------------------------   
                ConfigAndSaved.ADS1220GainCorrection_3 = MeasuredGainCodeValue_Pt1000_1K5 / rawData_3;
                SaveData();
                while(!(P1IN & BIT6));
                BSP_TURN_OFF_LED3();
            }
        }
        BSP_TURN_OFF_LED3();
    }
}

void rtd_process_4(void)
{
    if (ReadConversionData_4)
    {
        BSP_TURN_ON_LED4();
        //StartConversion = 1;             // Start next conversion immediately
        ADS1220_Get_Conversion_Data_Calibrated ((unsigned char *)tempData_4, 4);   // Get the temperature data with the calibration value subtracted
        
        code_4 = (((long)tempData_4[0] << 16) + ((long)tempData_4[1] << 8) + (long)tempData_4[2]);   // take 3 bytes of voltage returned and place in word
        // In case we extend the time between samples in the future, we will still need to keep the DAC
        // from timing out by sending a NOP command every time the loop is processed.
   //--------------------------------------------------------------------------------------------------------------------------------------------------------------        
        temperature_4 = (long)(interpolateTemperatureValue (code_4, PgaGainLevel_4, PT1000) * 1000.0);    // Get the temperature and convert into millidegrees C
        
        ReadConversionData_4 = 0;                        // Clear flag so next conversion is read again.

        // Collect the measured values for SAMPLES_PER_DAC_ADJUSTMENT(16) measurements to average
        if (avgCount_4 == 0)
        {
            // Erase all previous value, as this is the first measurement for this average block
            avgTemp_4 = (float)temperature_4;
            avgRaw_4 = (float)rawData_4;
        }
        else
        {
            // Add values from this measurement into the average block
            avgTemp_4 += (float)temperature_4;
            avgRaw_4 += (float)rawData_4;
            
        }
        avgCount_4 ++;
        
        // If this is the last measurement, calculate the averages and set the system to print
        if (avgCount_4 == SAMPLES)
        {
            avgCount_4 = 0;
            temperature_4 = (long)(avgTemp_4 / SAMPLES);
            if(temperature_4>200000)temperature_4=0;
            rawData_4 = (long)(avgRaw_4 / SAMPLES);
            __gie_disable();
            
            adc_result.temp_4 = temperature_4;
            __gie_enable();
            //CalVoltage = (long)(avgOffset / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainVoltage = (long)(avgGain / SAMPLES_PER_DAC_ADJUSTMENT);
            //GainCalibrateValue = (long)(avgGainCal / SAMPLES_PER_DAC_ADJUSTMENT);
            
            // Perform Gain Calibration when the user pushes the button on the top of the device.
            // The user MUST have modified the code to place the expected results into the MeasuredGainCodeValue
            //  variable at the top of main.c. The user is expected to place a known resistor value in place of the
            //  RTD and perform gain calibration to determine the system level gain correction. This value will be
            //  stored into flash memory for future use.
            //if (GainCal_2)
             if(!(P1IN & BIT7))
            {
                GainCal_4 = 0;
                BSP_TURN_ON_LED4();
                //--------------------------------------------------------------------------------------------------------------------------------------------------------------   
                ConfigAndSaved.ADS1220GainCorrection_4 = MeasuredGainCodeValue_Pt1000_1K5 / rawData_4;
                SaveData();
                while(!(P1IN & BIT7));
                BSP_TURN_OFF_LED4();
            }
        }
        BSP_TURN_OFF_LED4();
    }
}
