
#include "main.h"

/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/

void ConfigureOscillator(void) {
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBDbits.PLLDIV = 150; // M=152
    CLKDIVbits.PLLPRE = 5; // N1=7
    CLKDIVbits.PLLPOST = 0; // N2=2
    //CLKDIVbits.PLLPOST = 1; // N2=4
    /* Fosc = M/(N1.N2)*Fin
     * Fin : 7.37MHz (quartz interne)
     * Fosc à 80 MHZ (ne doit pas dépasser 80 MHZ)
     * la solution la plus proche est 152*7.37/(7*2) = 80.017
     * attention, cela entraine donc une FCY et une FPériphériques à 40 MHZ
     */
    
    __builtin_write_OSCCONH(0x01);  // demande que next soit FRC avec PLL
    __builtin_write_OSCCONL(0x01);  // demande switch (et garde LPRC actif)
    
    while (OSCCONbits.OSWEN);   // attente de la fin du switch
    while (!OSCCONbits.LOCK);   // attente que la PLL soit lockée sur se nouvelle configuration.
    
    
}


// initialize all things

void Init_All(void) {
    /* Configure the oscillator for the device */
    
    ConfigureOscillator();
    /* Initialize IO ports and peripherals */

    
    AD1PCFGL = 0xFFFF; //Pins analogiques en num�rique pour que ATP marche !!
    
    
    ADC_Init();
    Timers_Init();
    Gestion_IO_Init();
    
    #ifdef ENABLE_COM_UART
        UART_Cmd_Init();
    #endif
    #ifdef ENABLE_LIDAR
        UART_Lidar_Init();
    #endif

    #ifdef FLASH_HANDLER
        SPI_Low_Handler_Init();
        Flash_LogFile_Init();
    #endif

    #ifdef CAM_HANDLER
        Freescale_Cam_Init();
    #endif

    #ifdef MOTOR_HANDLER
        Motor_Out_Init();
    #endif
    #ifdef SERVO_HANDLER
        Gestion_Servos_Init();
    #endif

        
        
    Std_Com_Init();
    
    Init_I2C();

    //SPI_Low_Handler_Init();
    //ExpIO_Handler_Init();
    //Inter_Handler_Init();
    
    LED_SPI_Handler_Init();
    //Flash_LogFile_Init();
    
}
