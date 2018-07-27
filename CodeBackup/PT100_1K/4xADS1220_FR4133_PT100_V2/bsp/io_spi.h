

#ifndef JL_12864
#define JL_12864

#define st(x)      do { x } while (__LINE__ == -1)
#ifndef BV
#define BV(n)      (1 << (n))
#endif


/* CSn Pin Configuration */
#define __IO_SPI_CSN_1_GPIO_BIT__             2
#define IO_SPI_CONFIG_CSN_1_PIN_AS_OUTPUT()   st( P6DIR |=  BV(__IO_SPI_CSN_1_GPIO_BIT__); )
#define IO_SPI_DRIVE_CSN_1_HIGH()             st( P6OUT |=  BV(__IO_SPI_CSN_1_GPIO_BIT__); ) 
#define IO_SPI_DRIVE_CSN_1_LOW()              st( P6OUT &= ~BV(__IO_SPI_CSN_1_GPIO_BIT__); ) 
     
#define __IO_SPI_CSN_2_GPIO_BIT__             3
#define IO_SPI_CONFIG_CSN_2_PIN_AS_OUTPUT()   st( P6DIR |=  BV(__IO_SPI_CSN_2_GPIO_BIT__); )
#define IO_SPI_DRIVE_CSN_2_HIGH()             st( P6OUT |=  BV(__IO_SPI_CSN_2_GPIO_BIT__); ) 
#define IO_SPI_DRIVE_CSN_2_LOW()              st( P6OUT &= ~BV(__IO_SPI_CSN_2_GPIO_BIT__); ) 

#define __IO_SPI_CSN_3_GPIO_BIT__             4
#define IO_SPI_CONFIG_CSN_3_PIN_AS_OUTPUT()   st( P6DIR |=  BV(__IO_SPI_CSN_3_GPIO_BIT__); )
#define IO_SPI_DRIVE_CSN_3_HIGH()             st( P6OUT |=  BV(__IO_SPI_CSN_3_GPIO_BIT__); ) 
#define IO_SPI_DRIVE_CSN_3_LOW()              st( P6OUT &= ~BV(__IO_SPI_CSN_3_GPIO_BIT__); ) 

#define __IO_SPI_CSN_4_GPIO_BIT__             5
#define IO_SPI_CONFIG_CSN_4_PIN_AS_OUTPUT()   st( P6DIR |=  BV(__IO_SPI_CSN_4_GPIO_BIT__); )
#define IO_SPI_DRIVE_CSN_4_HIGH()             st( P6OUT |=  BV(__IO_SPI_CSN_4_GPIO_BIT__); ) 
#define IO_SPI_DRIVE_CSN_4_LOW()              st( P6OUT &= ~BV(__IO_SPI_CSN_4_GPIO_BIT__); ) 

/* SCLK Pin Configuration */
#define __IO_SPI_SCLK_GPIO_BIT__            1
#define IO_SPI_CONFIG_SCLK_PIN_AS_OUTPUT()  st( P6DIR |=  BV(__IO_SPI_SCLK_GPIO_BIT__); )
#define IO_SPI_DRIVE_SCLK_HIGH()            st( P6OUT |=  BV(__IO_SPI_SCLK_GPIO_BIT__); )
#define IO_SPI_DRIVE_SCLK_LOW()             st( P6OUT &= ~BV(__IO_SPI_SCLK_GPIO_BIT__); )

/* SI Pin Configuration */
#define __IO_SPI_SI_GPIO_BIT__              0
#define IO_SPI_CONFIG_SI_PIN_AS_OUTPUT()    st( P6DIR |=  BV(__IO_SPI_SI_GPIO_BIT__); )
#define IO_SPI_DRIVE_SI_HIGH()              st( P6OUT |=  BV(__IO_SPI_SI_GPIO_BIT__); )
#define IO_SPI_DRIVE_SI_LOW()               st( P6OUT &= ~BV(__IO_SPI_SI_GPIO_BIT__); )

/* SO Pin Configuration */
#define __IO_SPI_SO_GPIO_BIT__              7
#define IO_SPI_CONFIG_SO_PIN_AS_INPUT()     st( P3DIR &=  ~BV(__IO_SPI_SO_GPIO_BIT__); )
#define IO_SPI_SO_IS_HIGH()                 ( P3IN & BV(__IO_SPI_SO_GPIO_BIT__) )



void IO_SpiInit(void);
uint8_t IO_SPI_read_write_data(uint8_t data);



#endif
