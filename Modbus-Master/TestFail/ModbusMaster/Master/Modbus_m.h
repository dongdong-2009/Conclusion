#ifndef __MODBUS_M_H
#define __MODBUS_M_H

#include "stm32f10x.h"
#include "crc16.h"
#include "word.h"

#define BufferSize 64             //size of usart transmit/receive buffer

//Modbus从机状态
static const uint8_t ku8MBSuccess                    = 0x00;
static const uint8_t ku8MBInvalidSlaveID             = 0xE0;
static const uint8_t ku8MBInvalidFunction            = 0xE1;
static const uint8_t ku8MBResponseTimedOut           = 0xE2;
static const uint8_t ku8MBInvalidCRC                 = 0xE3;

//define Modbus Function Code

// Modbus function codes for bit access
static const uint8_t ku8MBReadCoils                  = 0x01; ///< Modbus function 0x01 Read Coils
static const uint8_t ku8MBReadDiscreteInputs         = 0x02; ///< Modbus function 0x02 Read Discrete Inputs
static const uint8_t ku8MBWriteSingleCoil            = 0x05; ///< Modbus function 0x05 Write Single Coil
static const uint8_t ku8MBWriteMultipleCoils         = 0x0F; ///< Modbus function 0x0F Write Multiple Coils

// Modbus function codes for 16 bit access
static const uint8_t ku8MBReadHoldingRegisters       = 0x03; ///< Modbus function 0x03 Read Holding Registers
static const uint8_t ku8MBReadInputRegisters         = 0x04; ///< Modbus function 0x04 Read Input Registers
static const uint8_t ku8MBWriteSingleRegister        = 0x06; ///< Modbus function 0x06 Write Single Register
static const uint8_t ku8MBWriteMultipleRegisters     = 0x10; ///< Modbus function 0x10 Write Multiple Registers
static const uint8_t ku8MBMaskWriteRegister          = 0x16; ///< Modbus function 0x16 Mask Write Register
static const uint8_t ku8MBReadWriteMultipleRegisters = 0x17; ///< Modbus function 0x17 Read Write Multiple Registers

//定义modbus主机相关变量
extern u8 SlaveID;                       //slave ID
extern u8 FunCode;                       //Function Code
extern u16 ReadAddr;                     //Read Address
extern u16 RegReadNum;                   //Read Register Number
extern u16 WriteAddr;                    //Write Address
extern u16 RegWriteNum;                  //Write Register Number
extern u16 SendBuffer[BufferSize];       //Send Buffer 
extern u8 ReceBuffer[BufferSize];       //Receive Buffer
extern u8 ModbusADU[256];


//定义modbus主机相关函数
void Master_Init(void);
void RecBufferClear(void);
void SendBufferClear(void);
void MasterService(u8 funcode);
void MasterReceive(void);
#endif

