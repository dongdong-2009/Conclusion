

#pragma vector=USART0TX_VECTOR
__interrupt void SPI0_tx (void)
{
    TXBUF0 = adc_result.byte[tx_index];  
    tx_index++;    
    if(tx_index >= 6)
    tx_index = 0;
}

#pragma vector= PORT2_VECTOR
__interrupt void port2 (void)
{
    P2IFG = 0;
    tx_index = 0;
    ///*
    //ME1 &= ~USPIE0;                             // Module enable
    U0CTL |= SWRST;              // 8-bit, SPI, Slave
    ME1 |= USPIE0;                             // Module enable
    U0CTL &= ~SWRST;                          // SPI enable
    IE1 |= UTXIE0;    
    //*/
    P1OUT ^=BIT0;
}