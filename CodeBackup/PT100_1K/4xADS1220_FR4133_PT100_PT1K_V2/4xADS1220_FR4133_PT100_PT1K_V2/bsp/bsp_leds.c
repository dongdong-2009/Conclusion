

/* ------------------------------------------------------------------------------------------------
 *                                            Includes
 * ------------------------------------------------------------------------------------------------
 */

#include "api.h"



/* ------------------------------------------------------------------------------------------------
 *                                             Macros
 * ------------------------------------------------------------------------------------------------
 */
#define BSP_CONFIG_LED1()    __bsp_LED1_CONFIG__()
#define BSP_CONFIG_LED2()    __bsp_LED2_CONFIG__()
#define BSP_CONFIG_LED3()    __bsp_LED3_CONFIG__()
#define BSP_CONFIG_LED4()    __bsp_LED4_CONFIG__()
#define BSP_CONFIG_LED5()    __bsp_LED5_CONFIG__()
#define BSP_CONFIG_LED6()    __bsp_LED6_CONFIG__()
#define BSP_CONFIG_LED7()    __bsp_LED7_CONFIG__()
#define BSP_CONFIG_LED8()    __bsp_LED8_CONFIG__()

#ifdef __bsp_LED_EXTENDED_CONFIG__
#define BSP_LED_EXTENDED_CONFIG()  __bsp_LED_EXTENDED_CONFIG__()
#else
#define BSP_LED_EXTENDED_CONFIG()
#endif


/**************************************************************************************************
 * @fn          BSP_InitLeds
 *
 * @brief       Initialize LED hardware and driver.
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
void BSP_InitLeds(void)
{
  /* configure LEDs */
  BSP_CONFIG_LED1();
  BSP_CONFIG_LED2();
  BSP_CONFIG_LED3();
  BSP_CONFIG_LED4();
  BSP_CONFIG_LED5();
  BSP_CONFIG_LED6();
  BSP_CONFIG_LED7();
  BSP_CONFIG_LED8();

  /* peform extended configuration if needed */
  BSP_LED_EXTENDED_CONFIG();

  /* turn all LEDs off as power-up default */
  BSP_TURN_OFF_LED1();
  BSP_TURN_OFF_LED2();
  BSP_TURN_OFF_LED3();
  BSP_TURN_OFF_LED4();
  BSP_TURN_OFF_LED5();
  BSP_TURN_OFF_LED6();
  BSP_TURN_OFF_LED7();
  BSP_TURN_OFF_LED8();
}


/**************************************************************************************************
*/

   
   
