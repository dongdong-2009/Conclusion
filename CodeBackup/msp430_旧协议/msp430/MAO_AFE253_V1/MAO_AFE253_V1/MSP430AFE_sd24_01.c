//*****************************************************************************
//  MSP430AFE25x Demo - SD24, Continuous Conversion on a Group of 3 Channels
//
//  Description: This program uses the SD24 module to perform continuous
//  conversions on a group of channels (0, 1 and 2). A SD24 interrupt occurs
//  whenever the conversions have completed. Test by applying voltages to the
//  3 input channels and setting a breakpoint at the line indicated
//  below. Run program until it reaches the breakpoint, then use
//  the debugger's watch window to view the conversion results. Results
//  (upper 16 bits only) are stored in three arrays, one for each channel.
//  ACLK = n/a, MCLK = SMCLK = DCO =  ~ 1.1MHz
//  //* For minimum Vcc required for SD24 module - see datasheet       *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//                MSP430AFE25x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 
//          --|RST          XOUT|-
//            |                 |
//   Vin1+ -->|A0.0+            |
//   Vin1- -->|A0.0-            |
//   Vin2+ -->|A1.0+            |
//   Vin2- -->|A1.0-            |
//   Vin3+ -->|A2.0+            |
//   Vin3- -->|A2.0-            |
//            |            VREF |---+
//            |                 |   |
//            |                 |  -+- 100nF
//            |                 |  -+-
//            |                 |   |
//            |            AVss |---+
//            |                 |
//
//  Naveen Kala
//  Texas Instruments, Inc
//  March 2011
//  Built with IAR Embedded Workbench Version: 5.20.1
//*****************************************************************************
#include "device.h"
#include "JL12864.h"
#include "sd24.h"
#include "guihz.h"
#define   Num_of_Results   8

/* Arrays to store SD24 conversion results */
unsigned int Ch0results[Num_of_Results];
unsigned int Ch1results[Num_of_Results];
unsigned int Ch2results[Num_of_Results];
unsigned int Ch0results_l[Num_of_Results];
unsigned int Ch1results_l[Num_of_Results];
unsigned int Ch2results_l[Num_of_Results];

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 &= ~XT2OFF;                       // Activate XT2 high freq xtal
    BCSCTL3 |= XT2S_2+LFXT1S_2;               // 3 ?16MHz crystal or resonator
    do
    {
      IFG1 &= ~OFIFG;                         // Clear OSCFault flag
      for (i = 0xFFF; i > 0; i--);            // Time for flag to set
    }
    while (IFG1 & OFIFG);                     // OSCFault flag still set?
    BCSCTL2 |= SELS+SELM_2;                   // MCLK = XT2 HF XTAL (safe)
    
  P1DIR |= BIT0;                       // Set P1.0 to output
  InitAnalogFrontEnd();
  __enable_interrupt();
  jl12864_poweron();
  jl12864lcd_clr();
  GUI_PutStringHZ(0,10,"Hang Zhou Dong Mu!");
  start_sd24(); 
  while(1)
  {
    
  }
}
