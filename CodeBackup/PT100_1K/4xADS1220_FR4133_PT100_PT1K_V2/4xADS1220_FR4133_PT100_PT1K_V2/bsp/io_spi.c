


#include "api.h"



/**********************************/
/*      Interface Define          */
/**********************************/

/* ------------------------------------------------------------------------------------------------
 *                                      SPI Configuration
 * ------------------------------------------------------------------------------------------------
 */




uint8_t   IO_SPI_read_write_data(uint8_t data);



/**********************************/
/*      Time Delay                */
/**********************************/
void JL_Delay(unsigned long i)
{
  while(i!=0)
        {
	      i--;
              __delay_cycles(1000);
        }
}

void IO_SpiInit(void)
{
  /* set CSn to default high level */
  IO_SPI_DRIVE_CSN_1_HIGH();
  IO_SPI_DRIVE_CSN_2_HIGH();
  IO_SPI_DRIVE_CSN_3_HIGH();
  IO_SPI_DRIVE_CSN_4_HIGH();
    /* configure all SPI related pins */
    
  IO_SPI_CONFIG_CSN_1_PIN_AS_OUTPUT();
  IO_SPI_CONFIG_CSN_2_PIN_AS_OUTPUT();
  IO_SPI_CONFIG_CSN_3_PIN_AS_OUTPUT();
  IO_SPI_CONFIG_CSN_4_PIN_AS_OUTPUT();
  IO_SPI_CONFIG_SCLK_PIN_AS_OUTPUT();
  IO_SPI_CONFIG_SI_PIN_AS_OUTPUT();
  IO_SPI_CONFIG_SO_PIN_AS_INPUT();
  IO_SPI_DRIVE_SCLK_LOW();
  
} 





uint8_t IO_SPI_read_write_data(uint8_t data)
{
  int i,j;
  j = 0x80;
  uint8_t data_in = 0;
  for(i=0;i<8;i++)
     {
          
        IO_SPI_DRIVE_SCLK_HIGH();
        if(data&j){
            IO_SPI_DRIVE_SI_HIGH();  
        }else {
            IO_SPI_DRIVE_SI_LOW();  
        }
        IO_SPI_DRIVE_SCLK_LOW();  
        data_in <<= 1;
        if(IO_SPI_SO_IS_HIGH()){
            data_in |= 0x01;
        }
        j = j>>1;
     }
  return data_in;
}

