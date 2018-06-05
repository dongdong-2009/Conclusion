#ifndef __DEHUMIDIFIER_H
#define __DEHUMIDIFIER_H

#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"
#include "stm32f10_timer.h"


#define DELIQCHAN    1 //除湿罐液位端口
#define DELIQMAX    1//除湿罐液位最大值
#define DELIQMIN   1 //除湿罐液位最小值

#define DECPUMPCHAN 1//除湿循环泵端口
#define DECPUMPFBCHAN 1//除湿循环泵反馈端口
#define DECPUMPDEF  1//除湿循环泵默认值

#define DEWFLOWCHAN 1//除湿罐流量端口
#define DEWFLOWMIN  1//除湿罐流量最小值
                   
#define DESTEMPCHAN 1//除湿罐溶液温度端口
#define DESTEMPMAX  1//除湿罐溶液温度上限
#define DESTEMPMIN  1//除湿罐溶液温度下限
#define DEWTIM      1//除湿罐等待最大时间

#define DEFANCHAN   1//除湿罐风扇端口
#define DEFANFBCHAN 1//除湿罐风扇反馈端口
#define DEFANDEF    1//除湿罐风扇默认值





u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8]);




#endif
