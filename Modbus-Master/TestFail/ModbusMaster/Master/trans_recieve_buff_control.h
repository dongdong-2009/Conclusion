/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TANS_RECEIEVE_BUFF_CONTROL_H
#define __TANS_RECEIEVE_BUFF_CONTROL_H
  /* Includes ------------------------------------------------------------------*/
//�������йص�ͷ�ļ�
#include "stm32f10x.h"
/* USER CODE BEGIN Includes */
//modbus���������ʹ�õ���ͷ�ļ�

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

typedef enum 
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

uint8_t Modbus_Master_RB_Initialize(void);
uint8_t Modbus_Master_Rece_Flush(void);
uint8_t Modbus_Master_Rece_Available(void);
uint8_t Modbus_Master_GetByte(uint8_t  *getbyte);
uint8_t Modbus_Master_Rece_Handler(void);
uint8_t Modbus_Master_Read(void);
uint8_t Modbus_Master_Write(uint8_t *buf,uint8_t length);
uint32_t Modbus_Master_Millis(void);
#endif 
/********END OF FILE****/
