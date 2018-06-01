#include "encode.h"
#include "string.h"
#include "stdlib.h"

static const char encodingTable [64] = {
  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
  'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
  'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
  'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'
};

/**
  * @brief  base64 encode
  * @param  
  * @retval None
  */
int encode_Base64(char *buf, int size, const char *user, const char *pwd)
{
  unsigned char inbuf[3];
  char *out = buf;
  int i, sep = 0, fill = 0, bytes = 0;

  while(*user || *pwd)
  {
    i = 0;
    while(i < 3 && *user) inbuf[i++] = *(user++);
    if(i < 3 && !sep)    {inbuf[i++] = ':'; ++sep; }
    while(i < 3 && *pwd)  inbuf[i++] = *(pwd++);
    while(i < 3)         {inbuf[i++] = 0; ++fill; }
    if(out-buf < size-1)
      *(out++) = encodingTable[(inbuf [0] & 0xFC) >> 2];
    if(out-buf < size-1)
      *(out++) = encodingTable[((inbuf [0] & 0x03) << 4)
               | ((inbuf [1] & 0xF0) >> 4)];
    if(out-buf < size-1)
    {
      if(fill == 2)
        *(out++) = '=';
      else
        *(out++) = encodingTable[((inbuf [1] & 0x0F) << 2)
                 | ((inbuf [2] & 0xC0) >> 6)];
    }
    if(out-buf < size-1)
    {
      if(fill >= 1)
        *(out++) = '=';
      else
        *(out++) = encodingTable[inbuf [2] & 0x3F];
    }
    bytes += 4;
  }
  if(out-buf < size)
    *out = 0;
  return bytes;
}

/**
  * @brief  convert a char from hexadecimal a decimal.
  * @param  h - Character hexadecimal.
  * @retval decimal
  */
unsigned char charHToI(unsigned char h)
{
	if ((h >= '0') && (h <= '9'))
		return (h - '0');
	else if ((h >= 'A') && (h <= 'F'))
		return (h - 'A' + 10);
	else
		return 0;
}

/**
  * @brief  网络地址转换
  * @param  ipaddr
  * @retval decimal
  */
unsigned int inet_addr_ty(char *ipaddr)
{
	char ipBytes[4]={0};  
	unsigned int i;  
	
	for( i=0; i<4; i++, ipaddr++ )
	{  
		ipBytes[(3-i)] = (char)atoi(ipaddr);
		
		ipaddr = strchr( ipaddr, '.' );
		
		if(ipaddr == NULL)
		{ 
			break; 
		}  
	}  

	return *((unsigned int *)ipBytes); 
}

/**
  * @brief  对字符串进行解析
  * @param  str:输入的类似于json字符串;out:格式化后的字符串
  * @retval 0:ok;1:fail
  */
int ParaseString(char *str,char *out)
{
	char *ptr = (str); 
	char *ptr2 = out; 

	while (*ptr != '\"' && *ptr)
		ptr++;

	ptr++;
		
	while (*ptr != '\"' && *ptr)
	{
		if (*ptr != '\\') 
			*ptr2++ = *ptr++;
		else
		{
			ptr++;
			switch (*ptr)
			{
				case 'b': 
					*ptr2++ = '\b';	
					break;
				case 'f': 
					*ptr2++ = '\f';	
					break;
				case 'n': 
					*ptr2++ = '\n';	
					break;
				case 'r': 
					*ptr2++ = '\r';	
					break;
				case 't': 
					*ptr2++ = '\t';	
					break;
				default:  
					*ptr2++ = *ptr; 
					break;
			}
			ptr++;
		}
	}

	*ptr2 = 0;
	
	if (*ptr == '\"') 
		ptr++;
	
	return 0;
}

