#ifndef __MB_REG_H
#define __MB_REG_H

/* Private define ------------------------------------------------------------*/
//输入寄存器起始地址
#define REG_INPUT_START       0x0000
//输入寄存器数量
#define REG_INPUT_NREGS       16
//保持寄存器起始地址
#define REG_HOLDING_START     0x0001
//保持寄存器数量
#define REG_HOLDING_NREGS     16

//线圈起始地址
#define REG_COILS_START       0x0000
//线圈数量
#define REG_COILS_SIZE        16

//开关寄存器起始地址
#define REG_DISCRETE_START    0x0000
//开关寄存器数量
#define REG_DISCRETE_SIZE     16

/* Private variables ---------------------------------------------------------*/
//输入寄存器内容
extern uint16_t usRegInputBuf[REG_INPUT_NREGS];
//输入寄存器起始地址
extern uint16_t usRegInputStart;

//保持寄存器内容
extern uint16_t *usRegHoldingBuf[REG_HOLDING_NREGS];
//保存寄存器地址
extern uint16_t usRegHoldingStart;

//线圈状态
extern uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8];
//开关输入量
extern uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8];

#endif
