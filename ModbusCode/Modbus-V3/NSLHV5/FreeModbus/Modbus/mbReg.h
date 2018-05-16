#ifndef __MB_REG_H
#define __MB_REG_H

/* Private define ------------------------------------------------------------*/
//����Ĵ�����ʼ��ַ
#define REG_INPUT_START       0x0000
//����Ĵ�������
#define REG_INPUT_NREGS       16
//���ּĴ�����ʼ��ַ
#define REG_HOLDING_START     0x0001
//���ּĴ�������
#define REG_HOLDING_NREGS     16

//��Ȧ��ʼ��ַ
#define REG_COILS_START       0x0000
//��Ȧ����
#define REG_COILS_SIZE        16

//���ؼĴ�����ʼ��ַ
#define REG_DISCRETE_START    0x0000
//���ؼĴ�������
#define REG_DISCRETE_SIZE     16

/* Private variables ---------------------------------------------------------*/
//����Ĵ�������
extern uint16_t usRegInputBuf[REG_INPUT_NREGS];
//����Ĵ�����ʼ��ַ
extern uint16_t usRegInputStart;

//���ּĴ�������
extern uint16_t *usRegHoldingBuf[REG_HOLDING_NREGS];
//����Ĵ�����ַ
extern uint16_t usRegHoldingStart;

//��Ȧ״̬
extern uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8];
//����������
extern uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8];

#endif
