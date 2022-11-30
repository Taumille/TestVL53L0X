
#include "xc.h"

#include "main.h"



/******************************************************************************/
/* Configuration                                                             */
/******************************************************************************/

// Select Oscillator and switching.
// FOSCSEL
//#pragma config FNOSC = FRCPLL           // Oscillator Mode (Internal Fast RC (FRC) w/ PLL)


void ConfigureOscillator(void) {
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBDbits.PLLDIV = 150; // M=152
    CLKDIVbits.PLLPRE = 5; // N1=7
    CLKDIVbits.PLLPOST = 0; // N2=2
    /* Fosc = M/(N1.N2)*Fin
     * Fin : 7.37MHz (quartz interne)
     * Fosc � 80 MHZ (ne doit pas d�passer 80 MHZ)
     * la solution la plus proche est 152*7.37/(7*2) = 80.017
     * attention, cela entraine donc une FCY et une FP�riph�riques � 40 MHZ
     */
    
    __builtin_write_OSCCONH(0x01);  // demande que next soit FRC avec PLL
    __builtin_write_OSCCONL(0x01);  // demande switch (et garde LPRC actif)
    
    while (OSCCONbits.OSWEN);   // attente de la fin du switch
    while (!OSCCONbits.LOCK);   // attente que la PLL soit lock�e sur se nouvelle configuration.
    
    
}

void ConfigureUart(void){
    U1MODEbits.STSEL = 0; // 1-Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud disabled
    U1MODEbits.BRGH = 0; // Standard-Speed mode
    U1BRG = BRGVAL_UART_CMD; // Baud Rate setting for 9600
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;
    
    _U1RXR = UART_RX_PIN_NB;
    UART_TX_PIN_REG = _RPOUT_U1TX;
    
    IEC0bits.U1TXIE = 1; // Enable UART TX interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    /* Wait at least 105 microseconds (1/9600) before sending first char */
    
    TRISCbits.TRISC2 = 0;

}

int main(void)
{
    ConfigureOscillator();
    ConfigureUart();
    Timers_Init();
    Init_I2C();
    
    
    uint32_t i=0;
    u8 d[2];
    
    TOF_I2C_Init();
    for (i=0;i<1000;i++){Transmit_I2C_Loop();}
    TOF_I2C_Start_Continuous(0x00);
    printu("sc");
    for (i=0;i<1000;i++){Transmit_I2C_Loop();}
    i=0;

    while(1){
        i++;
        Transmit_I2C_Loop();
        if (i==100){
            TOF_I2C_Read((RESULT_RANGE_STATUS+0x0A), 2, &d);
            i=0;
            printu(d[0]);
            printu(d[1]);
        }
        
        
    }
}
