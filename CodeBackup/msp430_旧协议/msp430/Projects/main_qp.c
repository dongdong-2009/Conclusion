/*----------------------------------------------------------------------------
*  Demo Application for SimpliciTI 
* 
*  L. Friedman 
*  Texas Instruments, Inc.
*---------------------------------------------------------------------------- */

/********************************************************************************************
Copyright 2007-2009 Texas Instruments Incorporated. All rights reserved.

IMPORTANT: Your use of this Software is limited to those specific rights granted under
the terms of a software license agreement between the user who downloaded the software,
his/her employer (which must be your employer) and Texas Instruments Incorporated (the
"License"). You may not use this Software unless you agree to abide by the terms of the
License. The License limits your use, and you acknowledge, that the Software may not be
modified, copied or distributed unless embedded on a Texas Instruments microcontroller
or used solely and exclusively in conjunction with a Texas Instruments radio frequency
transceiver, which is integrated into your product. Other than for the foregoing purpose,
you may not use, reproduce, copy, prepare derivative works of, modify, distribute,
perform, display or sell this Software and/or its documentation for any purpose.

YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS”
WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE
THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY
INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY
THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

Should you have any questions regarding your right to use this Software,
contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/


#include "api.h"



/*..........................................................................*/
//Ã¿Ôö¼Ó»ò¼õÉÙÒ»¸ö×´Ì¬»úÒªÔÚ´Ë½øÐÐÏûÏ¢¶ÓÁÐµÄÐÞ¸Ä

static QEvent l_BmqMode_Queue[8];
static QEvent l_WorkMode_Queue[16];

/* QF_active[] array defines all active object control blocks --------------*/
//Ã¿Ôö¼Ó»ò¼õÉÙÒ»¸ö×´Ì¬»úÒªÔÚ´Ë½øÐÐ×´Ì¬»úÊôÐÔÐÞ¸Ä

#define AO_DEFINE(name) (QActive *)&AO_##name, l_##name##_Queue, Q_DIM(l_##name##_Queue)
QActiveCB const Q_ROM Q_ROM_VAR QF_active[] = {
    { (QActive *) 0, (QEvent *) 0, 0 }, 
    {(QActive *) &AO_WorkMode, (QEvent *) l_WorkMode_Queue, Q_DIM(l_WorkMode_Queue) }, 
    {(QActive *) &AO_BmqMode, (QEvent *) l_BmqMode_Queue, Q_DIM(l_BmqMode_Queue) }, 
};


//´Ëº¯Êý¸ù¾Ý×´Ì¬»ú¸öÊý½øÐÐ×´Ì¬»ú¹¹Ôìº¯ÊýÐÞ¸Ä
#define QF_ctor(name)   QF_##name##_ctor()
void QF_State_ctor(void) {
    QF_ctor(BmqMode);
    QF_ctor(WorkMode);
}

/* make sure that the QF_active[] array matches QF_MAX_ACTIVE in qpn_port.h */
Q_ASSERT_COMPILE(QF_MAX_ACTIVE == Q_DIM(QF_active) - 1);

//QFÖÐÊ¼ÖÕÖ´ÐÐµÄ¹³×Óº¯Êý
void QF_onHook(void) {
    
}
void QF_onStartup(void) {

}

//QF¿ÕÏÐÊ±µÄ¹³×Óº¯Êý
void QF_onIdle(void) {
    __low_power_mode_0();
}

void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
    (void) file; /* avoid compiler warning */
    (void) line; /* avoid compiler warning */
    for (;;) {
        
    }
}

void MRFI_RxCompleteISR()
{
    qmsg_push2RFWorkMode(Q_RF_RX_PACKET_SIG);
}

void main (void)
{
    BSP_InitBoard();  
    BSP_InitLeds();
    unuse_ping_Init();
    
    BSP_TURN_ON_LED1();
    BSP_TURN_ON_LED2();
    timer_a1_init();
    key_init();
    
    
    
    
    QF_init(); //QF³õÊ¼»¯
    qmsg_init();
    QF_State_ctor(); //QF×´Ì¬»ú³õÊ¼»¯
    copy_addr_2INFO_D((uint8_t *)&MY_ADDR_DEFAULT);
    
    __enable_interrupt();
    
    QF_run(); //QF×´Ì¬»úÔËÐÐ
    
    while(1)
    {
        __low_power_mode_3();
    }
}

