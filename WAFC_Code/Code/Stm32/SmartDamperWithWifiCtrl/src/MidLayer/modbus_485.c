#include "modbus_485.h"

Mb485_Server mb485;

void Mb485_Init(void)
{
}

void Mb485_Task(void)
{
	switch (mb485.TaskState)
	{
		case MB485_STATE_RECV:
			if (Mb485_ReceiveFrame())
			{
			}
			break;
		case MB485_STATE_SEND:
			break;
		default:
			break;
	}
}

/**
  * @brief  get frame receive status
  * @param  none
  * @retval 0:;1:fail
  */
unsigned char Mb485_ReceiveFrame(void)
{
	return 0;
}


