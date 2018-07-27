
#ifndef  KEY_H
#define  KEY_H
#include "type_def.h"


#define KEY_PRESD 0x01

extern U8 key_scan(void);
// 返回长按的按键
extern U8 Is_key_pressed(void);
#endif
