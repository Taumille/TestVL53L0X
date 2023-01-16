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

int main(void)
{
    ConfigureOscillator();
    ConfigureUart();
    Timers_Init();
    Init_I2C();
    
    
    uint32_t i=0;
    u16 d;
    u8 t;
    
    TOF_I2C_Init();
    for (i=0;i<1000;i++){Transmit_I2C_Loop();}
    TOF_I2C_Start_Continuous(0x00);
    for (i=0;i<1000;i++){Transmit_I2C_Loop();}
    i=0;

    while(1){
        i++;
        Transmit_I2C_Loop();
        //TOF_Get_Measure_Loop(&d);
        if (i==10000){TOF_I2C_Read(RESULT_INTERRUPT_STATUS, 1, &t); i=0;}
        
    }
}
