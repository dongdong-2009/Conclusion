#include <stm32f10x.h>
#include "string.h"
#include "stdio.h"
#include "param.h"

#define PARAM_FLASH_ADDR	((uint32_t)0x0800C000) 		//48KB

/* Define the STM32F10x FLASH Page Size depending on the used STM32 device */
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#else
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif

Param param;

void Read_Param(void)
{
	uint32_t indexs;
	uint32_t i;
	uint32_t *pParam;

	pParam = (uint32_t *)&param;
	indexs = (sizeof(Param)>>2);

	for(i=0;i<indexs;i++)
	{
		*pParam = *((uint32_t *)(PARAM_FLASH_ADDR + (i<<2)));
		pParam++;
	
	}
}

/**
  * @brief  save param
  * @param  None
  * @retval 0;fail;1:ok
  */
uint32_t Save_Param(void)
{
	uint32_t ret = 1;
	uint32_t i = 0;
	uint32_t indexs = 0;
	uint32_t *pParam;
	FLASH_Status FLASHStatus = FLASH_COMPLETE;

	/* Unlock the Flash *********************************************************/
	/* Enable the flash control register access */
	FLASH_Unlock();
	  
	/* Erase the user Flash area ************************************************/
	/* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */
	
	/* Clear pending flags (if any) */	
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	
	FLASHStatus = FLASH_ErasePage(PARAM_FLASH_ADDR);

	if(FLASHStatus == FLASH_COMPLETE)
	{
		pParam = (uint32_t *)&param;
		indexs = (sizeof(Param)>>2);
		
		for(i=0;i<indexs;i++)
		{
			if (FLASH_ProgramWord((PARAM_FLASH_ADDR + (i<<2)), *pParam) != FLASH_COMPLETE)
			{
				ret = 0;
			}
			
			pParam++;
		}
	}
	else
		ret = 0;

	FLASH_Lock();
	
	return ret;
}

