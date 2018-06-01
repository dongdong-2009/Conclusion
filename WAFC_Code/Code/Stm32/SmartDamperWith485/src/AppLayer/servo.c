#include "servo.h"

extern u16 _ADC_buf[ADC_BUF_SIZE];
HDTimer _mA_Output_Timer;
HDTimer _servo_Step_Timer;
float Safe_Angle_UB;
float Safe_Angle_LB;
u8 servo_mode;
u8 servo_direction; 

void Servo_Init(void)
{
	Current_ADC_Init();
	_mA_Output_Timer = HDTimer_add_ms(GetTimeHD(),MA_OUTPUT_CLK_MS);
	_servo_Step_Timer = HDTimer_add_ms(GetTimeHD(),SERVO_STEP_CLK_MS);
	PWM_Init();
	Safe_Angle_UB = ANGLE_MAX;
	Safe_Angle_LB = ANGLE_MIN;
	servo_mode = SERVO_MODE_TRACKING;
	servo_direction = SERVO_DIR_INC;
}

void Servo_Position(float angle) // direct adjust 
{
	u16 PWM_open;
	u16 PWM_close;
	u16 PWM_Now;

	//Convert angle to PWM value
	PWM_open = gModuleData.Servo.PWM_Angle_0;
	PWM_close = gModuleData.Servo.PWM_Angle_90;
	if (angle<ANGLE_MIN)
		angle = ANGLE_MIN;
	else if (angle>ANGLE_MAX)
		angle = ANGLE_MAX;
	PWM_Now = PWM_open+(u16)(angle/ANGLE_RANGE*(PWM_close-PWM_open));
	//If considering hysteresis, PWM_Now should be adjusted
	
	
	TIM_SetCompare1(TIM3,PWM_Now);
	gModuleData.Servo.PWM = PWM_Now;
}

float Servo_mA_Mean(void)
{
	unsigned int i;
	unsigned int sum_ADC_buf;
	
	sum_ADC_buf = 0;
	for (i=0;i<ADC_BUF_SIZE;i++)
		sum_ADC_buf += _ADC_buf[i];
	return (float)sum_ADC_buf*0.805664/ADC_BUF_SIZE; //(float)sum_ADC_buf*3.3/4096*1000/ADC_BUF_SIZE;
}

void Servo_Task(void)
{
	float damper_pos;
	float mA;
	
	if (IsTimeExpiredHD(_mA_Output_Timer))
	{
		mA = Servo_mA_Mean();
		if (mA > MA_BLOCK_THRESHOLD) /*******************incomplete***************************************/
		{
			
		}
		gModuleData.Servo.Current = mA;
		_mA_Output_Timer = HDTimer_add_ms(GetTimeHD(),MA_OUTPUT_CLK_MS);
	}
	
	if (IsTimeExpiredHD(_servo_Step_Timer))
	{
		
		switch (servo_mode) /*******************incomplete***************************************/
		{
			case SERVO_MODE_TRACKING:
				damper_pos = gModuleData.Damper.Position;
				if (IN_RANGE(damper_pos,Safe_Angle_LB,Safe_Angle_UB))
				{
					Servo_Position(damper_pos);
				}
				else
				{
					servo_mode = SERVO_MODE_BLOCKED;
				}
				break;
			case SERVO_MODE_BLOCKED:
				if (IN_RANGE(damper_pos,Safe_Angle_LB,Safe_Angle_UB))
				{
					servo_mode = SERVO_MODE_TRACKING;
					Servo_Position(damper_pos);
				}
				break;
			default:
				servo_mode = SERVO_MODE_TRACKING;
				break;
		}
		
		gModuleData.Servo.Mode = (unsigned short)servo_mode;
		_servo_Step_Timer = HDTimer_add_ms(GetTimeHD(),SERVO_STEP_CLK_MS);
	}
		
}
	
