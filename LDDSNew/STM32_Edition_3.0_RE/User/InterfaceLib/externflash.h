#ifndef EXTERNFLASH_H_
#define EXTERNFLASH_H_

void Flash_Configuration(void);
char FlashByteRead(unsigned int addr);
void FlashByteWrite(unsigned int addr,char data);
void FlashPageWrite(unsigned int addr,char* data,int num);
void FlashPageRead(unsigned int addr, char* data,int num);
#endif /* EXTERNFLASH_H_ */

