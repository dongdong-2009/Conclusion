#ifndef __DEHUMIDIFIER_H
#define __DEHUMIDIFIER_H

#include "analogin.h"
#include "stm32f10_dac.h"
#include "stm32f10_gpio.h"
#include "stm32f10_timer.h"


#define DELIQCHAN    1 //��ʪ��Һλ�˿�
#define DELIQMAX    1//��ʪ��Һλ���ֵ
#define DELIQMIN   1 //��ʪ��Һλ��Сֵ

#define DECPUMPCHAN 1//��ʪѭ���ö˿�
#define DECPUMPFBCHAN 1//��ʪѭ���÷����˿�
#define DECPUMPDEF  1//��ʪѭ����Ĭ��ֵ

#define DEWFLOWCHAN 1//��ʪ�������˿�
#define DEWFLOWMIN  1//��ʪ��������Сֵ
                   
#define DESTEMPCHAN 1//��ʪ����Һ�¶ȶ˿�
#define DESTEMPMAX  1//��ʪ����Һ�¶�����
#define DESTEMPMIN  1//��ʪ����Һ�¶�����
#define DEWTIM      1//��ʪ�޵ȴ����ʱ��

#define DEFANCHAN   1//��ʪ�޷��ȶ˿�
#define DEFANFBCHAN 1//��ʪ�޷��ȷ����˿�
#define DEFANDEF    1//��ʪ�޷���Ĭ��ֵ





u8 dehStart(u8 din[8],u8 dout[8],float ain[16],float arin[12],float aout[8],float arout[8]);




#endif
