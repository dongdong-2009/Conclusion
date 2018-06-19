#include "Modbus_m.h"
#include "usart.h"

void RecBufferClear(void)
{
	for(u8 i=0;i<BufferSize;i++)
	{
		ReceBuffer[i]=0;
	}
}

void SendBufferClear(void)
{
	for(u8 i=0;i<BufferSize;i++)
	{
		SendBuffer[i]=0;
	}
}

void MasterService(u8 funcode)
{
	u8 ModbusADUSize=0;
	u8 ByteNum;
	u16 crcRec;
	u8 i;
	
	//�����������
	ModbusADU[ModbusADUSize++]=SlaveID;
	ModbusADU[ModbusADUSize++]=FunCode;
	
	//������
	switch(funcode)
	{
		case ku8MBReadCoils :
			ModbusADU[ModbusADUSize++]=highByte(ReadAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(ReadAddr);
      ModbusADU[ModbusADUSize++] = highByte(RegReadNum);
      ModbusADU[ModbusADUSize++] = lowByte(RegReadNum);
			break;
		
		case ku8MBReadDiscreteInputs:
			ModbusADU[ModbusADUSize++]=highByte(ReadAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(ReadAddr);
      ModbusADU[ModbusADUSize++] = highByte(RegReadNum);
      ModbusADU[ModbusADUSize++] = lowByte(RegReadNum);
			break;
		
		case ku8MBReadInputRegisters:
			ModbusADU[ModbusADUSize++]=highByte(ReadAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(ReadAddr);
      ModbusADU[ModbusADUSize++] = highByte(RegReadNum);
      ModbusADU[ModbusADUSize++] = lowByte(RegReadNum);
			break;
		
		case ku8MBReadHoldingRegisters:
			ModbusADU[ModbusADUSize++]=highByte(ReadAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(ReadAddr);
      ModbusADU[ModbusADUSize++] = highByte(RegReadNum);
      ModbusADU[ModbusADUSize++] = lowByte(RegReadNum);
			break;
		
		case ku8MBReadWriteMultipleRegisters:
			ModbusADU[ModbusADUSize++]=highByte(ReadAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(ReadAddr);
      ModbusADU[ModbusADUSize++] = highByte(RegReadNum);
      ModbusADU[ModbusADUSize++] = lowByte(RegReadNum);
			break;		
	}
	
	//д����---��ַ
	switch(funcode)
	{
		case ku8MBWriteSingleCoil:
			ModbusADU[ModbusADUSize++]=highByte(WriteAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(WriteAddr);
			break;		
		
		case ku8MBMaskWriteRegister:
			ModbusADU[ModbusADUSize++]=highByte(WriteAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(WriteAddr);
			break;
		
		case ku8MBWriteMultipleCoils:
			ModbusADU[ModbusADUSize++]=highByte(WriteAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(WriteAddr);
			break;

		case ku8MBWriteSingleRegister:
			ModbusADU[ModbusADUSize++]=highByte(WriteAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(WriteAddr);
			break;

		case ku8MBWriteMultipleRegisters:
			ModbusADU[ModbusADUSize++]=highByte(WriteAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(WriteAddr);
			break;

		case ku8MBReadWriteMultipleRegisters:
			ModbusADU[ModbusADUSize++]=highByte(WriteAddr);
		  ModbusADU[ModbusADUSize++] = lowByte(WriteAddr);
			break;
	}
	
	//д����---����
	switch(funcode)
	{
		case ku8MBWriteSingleCoil:
			ModbusADU[ModbusADUSize++]=highByte(RegWriteNum);
		  ModbusADU[ModbusADUSize++] = lowByte(RegWriteNum);
			break;		

		case ku8MBWriteSingleRegister:
			ModbusADU[ModbusADUSize++]=highByte(SendBuffer[0]);
		  ModbusADU[ModbusADUSize++] = lowByte(SendBuffer[0]);
			break;	

		case ku8MBWriteMultipleCoils:
			ModbusADU[ModbusADUSize++]=highByte(RegWriteNum);
		  ModbusADU[ModbusADUSize++] = lowByte(RegWriteNum);
			ByteNum = (RegWriteNum % 8) ? ((RegWriteNum >> 3) + 1) : (RegWriteNum >> 3);  //�ж�����Ҫ���ֽ���
			ModbusADU[ModbusADUSize++] = ByteNum;	
			for(i=0;i<ByteNum;i++)
			{
				switch(i%2)
				{
					case 0:                                    //ż��
						ModbusADU[ModbusADUSize++]=lowByte(SendBuffer[i>>1]);
						break;
					
					case 1:                                    //ż��
						ModbusADU[ModbusADUSize++]=highByte(SendBuffer[i>>1]);
						break;
				}
			}
		break;	

		case ku8MBWriteMultipleRegisters:
			ModbusADU[ModbusADUSize++]=highByte(RegWriteNum);
		  ModbusADU[ModbusADUSize++] = lowByte(RegWriteNum);
			ModbusADU[ModbusADUSize++] = lowByte(RegWriteNum <<1);  //д���ֽ�����=�Ĵ�������*2
			for (i = 0; i < lowByte(RegWriteNum); i++)
      {
        ModbusADU[ModbusADUSize++] = highByte(SendBuffer[i]);
        ModbusADU[ModbusADUSize++] = lowByte(SendBuffer[i]);
      }
			break;		

		case ku8MBReadWriteMultipleRegisters:
			ModbusADU[ModbusADUSize++]=highByte(RegWriteNum);
		  ModbusADU[ModbusADUSize++] = lowByte(RegWriteNum);
			ModbusADU[ModbusADUSize++] = lowByte(RegWriteNum <<1);  //д���ֽ�����=�Ĵ�������*2
			for (i = 0; i < lowByte(RegWriteNum); i++)
      {
        ModbusADU[ModbusADUSize++] = highByte(SendBuffer[i]);
        ModbusADU[ModbusADUSize++] = lowByte(SendBuffer[i]);
      }
			break;	

		case ku8MBMaskWriteRegister:
			ModbusADU[ModbusADUSize++]=highByte(SendBuffer[0]);
		  ModbusADU[ModbusADUSize++] = lowByte(SendBuffer[0]);
			ModbusADU[ModbusADUSize++]=highByte(SendBuffer[1]);
		  ModbusADU[ModbusADUSize++] = lowByte(SendBuffer[1]);
			break;		
	}
	
	//����У����
	crcRec=0xFFFF;
	for(i=0;i<ModbusADUSize;i++)
	{
		crcRec=crc16_update(crcRec, ModbusADU[i]);
	}
	ModbusADU[ModbusADUSize++] = highByte(crcRec);    //CRCУ��λ��λ
  ModbusADU[ModbusADUSize++] = lowByte(crcRec);     //CRCУ��λ��λ
	
	//��ս��ջ���
	RecBufferClear();
	UsartSendData(ModbusADUSize,(char*)ModbusADU);
}

void MasterReceive(void)
{
	
}