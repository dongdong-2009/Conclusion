

#include  "device.h"
#include <in430.h>
#include "key.h"
#include "type_def.h"
#include "key.h"
#define KEY_NO_NEW_DATA  0x00
U8 key_scan(void)
{
  static U8 Old_key, Last_valid_key;
  U8 key;
  //P1DIR = 0;
  key = P1IN;
  key = ~key;
  if(key == KEY_NO_NEW_DATA)
  {
    Old_key = KEY_NO_NEW_DATA;
    Last_valid_key = KEY_NO_NEW_DATA;
    return 0;
  }
  
  // 一个键被按下
  if(key == Old_key)
  {
    if(key != Last_valid_key)
    {
      Last_valid_key = key;
      return key;
    }
  }
  Old_key = key;
  return 0;
}

U8 Is_key_pressed(void)
{
  U8 key;
  key = (~P1IN) & 0xF0;
  
 
  // 一个键被按下
  if(key != KEY_NO_NEW_DATA)
  {
    return key;
  }
  return 0;
}

