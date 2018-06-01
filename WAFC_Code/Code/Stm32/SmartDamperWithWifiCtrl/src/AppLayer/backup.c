#include "backup.h"
#include "bsp_systimer.h"
#include "modbus_app.h"
#include "wifi_server.h"

// for each 255 bytes, pair with (4096-256)/2=1920 errata
//+--------data-----------+
//|0x00..                 +
//|0x01..                 +
//|0x02..                 +
//|...                    +
//|0xFE...                +
//+-------empty-----------+
//|0xFF... 0b11111000 loc +  //val:loc 0xFF:0x0100, 0xFE:0x02AA, 0xFC:0x0454, 0xF8:0x05FE, 0xF0:0x07A8, 0xE0:0x0952, 0xC0:0x0AFC, 0x80:0x0CA6, 0x00:0x0E50,  
//+-------erata-----------+
//|0x0100(Addr)..         +
//|0x0101(Val)..          +
//|0x0102(Addr)..         +
//|0x0103(Val)..          +
//|...                    +
//|0x0FFF...              +
//+--end of section-------+


extern WifiCfg wifiCfg;

BackupTable BackupDataTbl[]=
{
	{(uint8_t *)wifiCfg.remoteSsid,0,16},
	{(uint8_t *)wifiCfg.remotePswd,16,16},
	
	{(uint8_t *)&gModuleData.Sys.Version, 32, 2},
	{(uint8_t *)&gModuleData.Sys.SubVersion, 34, 2},
	
	{(uint8_t *)&gModuleData.Flow.MeasureSrc, 68, 2},
	{(uint8_t *)&gModuleData.Flow.SetPoint, 70, 4},
	{(uint8_t *)&gModuleData.Flow.SetPointSrc, 74, 2},
	
	{(uint8_t *)&gModuleData.Damper.SetPoint, 100, 4},
	{(uint8_t *)&gModuleData.Damper.SetPointSrc, 104, 2},
	{(uint8_t *)&gModuleData.Damper.Mode, 126, 2},
	
	{(uint8_t *)&gModuleData.Servo.PWM_Angle_0, 134, 2},
	{(uint8_t *)&gModuleData.Servo.PWM_Angle_90, 136, 2},
	{(uint8_t *)&gModuleData.Servo.Mode, 158, 2},
	
	{(uint8_t *)&gModuleData.Pitot.AmpCoeff, 164, 4},
	{(uint8_t *)&gModuleData.Pitot.SizeCoeff, 168, 4},
	{(uint8_t *)&gModuleData.Pitot.TempCoeff, 172, 4},
	{(uint8_t *)&gModuleData.Pitot.PressureBias, 176, 4},
	
	{(uint8_t *)&gModuleData.CO2.MeasureSrc, 194, 2},
	{(uint8_t *)&gModuleData.CO2.Bias, 196, 2},
	{(uint8_t *)&gModuleData.CO2.Limit, 198, 2},
	
	{(uint8_t *)&gModuleData.VentCtrl.Mode, 208, 2},
	{(uint8_t *)&gModuleData.VentCtrl.Kp_FlowSP, 210, 4},	
	{(uint8_t *)&gModuleData.VentCtrl.MinFlow, 214, 4},	
	
	{(uint8_t *)&gModuleData.PIDCtrl.LB, 228, 4},
	{(uint8_t *)&gModuleData.PIDCtrl.UB, 232, 4},
	{(uint8_t *)&gModuleData.PIDCtrl.Kp, 236, 4},
	{(uint8_t *)&gModuleData.PIDCtrl.Ki, 240, 4},
	{(uint8_t *)&gModuleData.PIDCtrl.G0, 244, 4},
	{(uint8_t *)&gModuleData.PIDCtrl.G1, 248, 4},
	{(uint8_t *)&gModuleData.PIDCtrl.FbSrc, 252, 2},
};

HDTimer _Backup_Timer;

#undef __BACKUP_DEBUG__
//#define __BACKUP_DEBUG__
#ifdef __BACKUP_DEBUG__
	u8 DEBUG_SEC_BUF[BACKUP_SEC_SIZE];
#endif

void Backup_Init(void)
{
	int i;
	u8 version;
	
	SPI_Flash_Init();
	
	Backup_Load(&version,BackupDataTbl[3].dataSize,BackupDataTbl[3].BackupAddr);
	if (version < 0xFF)
	{
		for(i=0;i<sizeof(BackupDataTbl)/sizeof(BackupTable);i++) // load all data from flash and write to working variables
		{
			Backup_Load(BackupDataTbl[i].pData,BackupDataTbl[i].dataSize,BackupDataTbl[i].BackupAddr);
		}
	}
	_Backup_Timer = HDTimer_add_s(GetTimeHD(),20);
}

// compute the sec number which addr belongs to
u16 Addr2Sec (u32 addr)
{
	return (u16)(addr/BACKUP_SEC_DATA_SIZE);
}

u8 AddrModSec (u32 addr)
{
	return (u8)(addr%BACKUP_SEC_DATA_SIZE);
}

// compute the initial addr for section
u32 SecAddrOffset (u16 sec)
{
	return (u32)sec*BACKUP_SEC_SIZE;
}

u16 Backup_Mark2Pos(u8 mark)
{
	//mark:loc 0xFF:0x0100, 0xFE:0x02AA, 0xFC:0x0454, 0xF8:0x05FE, 0xF0:0x07A8, 0xE0:0x0952, 0xC0:0x0AFC, 0x80:0x0CA6, 0x00:0x0E50,  
	if (mark == 0xFF) return 0x0100;
	if (mark == 0xFE) return 0x02AA;
	if (mark == 0xFC) return 0x0454;
	if (mark == 0xF8) return 0x05FE;
	if (mark == 0xF0) return 0x07A8;
	if (mark == 0xE0) return 0x0952;
	if (mark == 0xC0) return 0x0AFC;
	if (mark == 0x80) return 0x0CA6;
	if (mark == 0x00) return 0x0E50;
	return 0x0000;
}

u8 Backup_Pos2Mark(u16 pos)
{
	//mark:loc 0xFF:0x0100, 0xFE:0x02AA, 0xFC:0x0454, 0xF8:0x05FE, 0xF0:0x07A8, 0xE0:0x0952, 0xC0:0x0AFC, 0x80:0x0CA6, 0x00:0x0E50,  
	if (pos<0x02AA) return 0xFF;
	if (pos<0x0454) return 0xFE;
	if (pos<0x05FE) return 0xFC;
	if (pos<0x07A8) return 0xF8;
	if (pos<0x0952) return 0xF0;
	if (pos<0x0AFC) return 0xE0;
	if (pos<0x0CA6) return 0xC0;
	if (pos<0x0E50) return 0x80;
	else return 0x00;
}

// obtain the errata position for a new errata for a given section, scan errata loc mark and then scan from the first errata and see if the Addr is 0xFF.
u16 Backup_GetErrataPos(u16 sec)
{
	u16  pos;
	u8   addr;
	
	SPI_Flash_Read(&addr,SecAddrOffset(sec)+BACKUP_SEC_DATA_SIZE,1);
	for (pos = Backup_Mark2Pos(addr);pos<BACKUP_SEC_SIZE;pos+=2)
	{
		SPI_Flash_Read(&addr,SecAddrOffset(sec)+pos,1);
		if (addr == 0xFF) break;
	}
	
	return pos;
}

// load one sector to specific buf with correction by errata, loc < BACKUP_SEC_DATA_SIZE, loc + num <= BACKUP_SEC_DATA_SIZE
void Backup_Load_Sec(u8 *buf, u16 sec, u8 loc, u8 num)
{
	u16 i;
	ErrataItem erratum;
	
	// read original record in data section
	SPI_Flash_Read(buf,SecAddrOffset(sec)+loc,num);
	
	// correct by errata
	for (i=0;i<BACKUP_SEC_ERRATA_SIZE;i++)
	{
		SPI_Flash_Read((u8 *)&erratum,SecAddrOffset(sec)+BACKUP_SEC_ERRATA_ADDR(i),2);
		if (erratum.Addr == 0xFF) break; //reach the end of errata list
		if (erratum.Addr >= loc && erratum.Addr < loc + num) // the errata is within range between [loc,loc+num)
			buf[erratum.Addr-loc]=erratum.Val;
	}
	
	#ifdef __BACKUP_DEBUG__
	SPI_Flash_Read(DEBUG_SEC_BUF,SecAddrOffset(sec),BACKUP_SEC_DATA_SIZE);
	#endif
}

// load the entire backup from flash to BackupBuf
void Backup_Load(u8 *buf, u32 Num, u32 Addr)
{
	u16 sec;
	u8 loc;
	u8 count;
	
	loc = AddrModSec(Addr);	
	for (sec = Addr2Sec(Addr); Num>0; sec++)
	{	
		if (Num+loc>BACKUP_SEC_DATA_SIZE) //haven't finished till the end of this section
		{
			count = BACKUP_SEC_DATA_SIZE-loc;
			Backup_Load_Sec(buf,sec,loc,count);
			Num -= count;
			loc = 0;
			buf += count;
		}
		else
		{
			Backup_Load_Sec(buf,sec,loc,Num);
			Num = 0;
		}
	}
}

// update one sector from specific buf with correction by errata, loc < BACKUP_SEC_DATA_SIZE, loc + num <= BACKUP_SEC_DATA_SIZE
void Backup_Update_Sec(u8 *buf, u16 sec, u8 loc, u8 num)
{
	u16 errata_pos;
	ErrataItem erratum;
	u8 temp_buf[BACKUP_SEC_DATA_SIZE];
	u8 i;
	
	//check if the rest of errata space is enough for update
	errata_pos = Backup_GetErrataPos(sec);
	if (errata_pos+num*2 < BACKUP_SEC_SIZE) // enough space, update in errata 
	{
		for (i=0;i<num;i++)
		{
			erratum.Addr = loc + i;
			erratum.Val = buf[i];
			SPI_Flash_Write_NoCheck((u8 *)&erratum,SecAddrOffset(sec)+errata_pos,2);
			errata_pos += 2;
		}
		i = Backup_Pos2Mark(errata_pos);//update errata loc mark;
		SPI_Flash_Write_NoCheck(&i,SecAddrOffset(sec)+BACKUP_SEC_DATA_SIZE,1);
	}
	else // not enough space, erase the sector and rewrite new values
	{
		if (num < BACKUP_SEC_DATA_SIZE) //not entire sector will be updated, need to save unupdated data.
		{
			//load the whole sector to temp_buf
			Backup_Load_Sec(temp_buf,sec,0,BACKUP_SEC_DATA_SIZE);
		}
		//erase the whole sector and rewrite the data
		SPI_Flash_Erase_Sector(sec);
		//overwrite values to temp_buf correspondingly
		for (i=0;i<num;i++) temp_buf[loc+i] = buf[i];
		//write the data back to flash
		SPI_Flash_Write_NoCheck(temp_buf,SecAddrOffset(sec),BACKUP_SEC_DATA_SIZE);
	}
	
	#ifdef __BACKUP_DEBUG__
	SPI_Flash_Read(DEBUG_SEC_BUF,SecAddrOffset(sec),BACKUP_SEC_SIZE);			
	#endif
}
	
void Backup_Update(u8 *buf, u32 Num, u32 Addr)
{
	u16 sec;
	u8 count;
	u8 loc;
	
	#ifdef __BACKUP_DEBUG__
	u8 *DEBUG_buf;
	#endif
	
	loc = AddrModSec(Addr);
	for (sec = Addr2Sec(Addr); Num>0; sec++)
	{
		if (loc + Num > BACKUP_SEC_DATA_SIZE) //haven't finished till the end of this section
		{
			count = BACKUP_SEC_DATA_SIZE-loc;
			Backup_Update_Sec(buf,sec,loc,count);
			Num -= count;
			loc = 0;
			buf += count;
			#ifdef __BACKUP_DEBUG__
			#endif
		}
		else
		{	
			Backup_Update_Sec(buf,sec,loc,Num);
			Num = 0;
		}
	}	
}

void Backup_Task(void)
{
	u16 i;
	u8 j;
	u8 mustUpdated;
	u8 temp_buf[BACKUP_SEC_DATA_SIZE];
	u8 *p;
	
	if (IsTimeExpiredHD(_Backup_Timer))
	{
		// execute backup task on every BACKUP_REFRESH_S
		
		// check if any value in BackupDataTbl is different from BackupBuf
		for(i=0;i<sizeof(BackupDataTbl)/sizeof(BackupTable);i++)
		{
			mustUpdated = 0;
			Backup_Load(temp_buf,BackupDataTbl[i].dataSize,BackupDataTbl[i].BackupAddr);
			for (j=0;j<BackupDataTbl[i].dataSize;j++)
			{
				p = BackupDataTbl[i].pData;
				if (p[j] == temp_buf[j]) continue;
				temp_buf[j] = p[j];
				mustUpdated = 1;
			}
			if (mustUpdated) 
				Backup_Update(temp_buf,BackupDataTbl[i].dataSize,BackupDataTbl[i].BackupAddr);
		}
		
		_Backup_Timer = HDTimer_add_s(GetTimeHD(),BACKUP_REFRESH_S);
	}
}

