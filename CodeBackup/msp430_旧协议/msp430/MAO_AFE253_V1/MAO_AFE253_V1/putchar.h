#ifdef   PUTCHAR_GLOBALS
#define  PUTCHAR_EXT
#else
#define  PUTCHAR_EXT  extern
#endif



// set up hardware (baud rate ...)
unsigned char RS232RXBufferCount (void); // count of chars in
// receive buffer
char RS232GetChar (char *ch); // read char from receive buffer
void RS232TXChar (char cByte); // write a char to send buffer
// (and send it)

int rs232_send_bytes(unsigned char *bytes,int len);  
int rs232_send_string(char *string);


void InitUART(unsigned long baud);

