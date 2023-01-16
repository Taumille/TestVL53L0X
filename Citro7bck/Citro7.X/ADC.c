


#include "main.h"


uint16_t Vin_Val[NB_VAL_ADC_MOY];
uint16_t Vin_Val_Ptr;
uint16_t Cam_ADC_Val;
uint16_t Vmot_ADC_Val;

uint8_t ADC_State = 0;

uint32_t Nb_ADC_Conv = 0;
uint16_t Last_Debug_ADC_Timer = 0;

void ADC_Init (void)
{
    AD1CON1bits.AD12B = 1;      // ADC en 12 bits
    AD1CON1bits.SSRC = 0b111;   // switch from sample to convert auto
    //AD1CON1bits.ASAM = 1;       // Auto Sample => devient "manuel" en IT
    
    AD1CON3bits.ADCS = 9;      // 1 cycle ADC = 10 cycles horloge
    //  1 cycle ADC = 117ns MINIMUM
    //  1 cycle horloge = 25ns (fcy = 40MHz, Fosc = 80) => mini = 5 fois (= 4 en registre)
    AD1CON3bits.SAMC = 10;      // sample durant 10 cycles ADC
    
    AD1CHS0bits.CH0NA = 0;      // neg is GND
    AD1PCFGLbits.PCFG0 = 0;     // active AN0 comme entree analogique / desactive le numerique
    AD1PCFGLbits.PCFG4 = 0;     // active AN4 comme entree analogique / desactive le numerique
    #ifdef CAM_HANDLER
    AD1PCFGLbits.PCFG5 = 0;     // active AN5 comme entree analogique / desactive le numerique
    #endif

    AD1CON1bits.ADON = 1;       // allume l'ADC
	IFS0bits.AD1IF = 1;         // demarre le bit interupt => demarre la machine
    IEC0bits.AD1IE = 1;
}

void ADC_Loop (void)
{
    /*
    if (IFS0bits.AD1IF) {
        Vin_Val[Vin_Val_Ptr] = ADC1BUF0;
        Vin_Val_Ptr ++;
        if (Vin_Val_Ptr >= NB_VAL_ADC_MOY)
            Vin_Val_Ptr = 0;
    }*/
    /*if ((Timer_ms1 - Last_Debug_ADC_Timer) > 1000) {
        Last_Debug_ADC_Timer += 1000;
        printf("%lu ADC\n", Nb_ADC_Conv);
        Nb_ADC_Conv = 0;
    }*/
}

u8 Get_Vin_Func (void)
{
    u8 i;
    u32 val = 0;
    for (i = 0; i < NB_VAL_ADC_MOY; i++) {
        val += Vin_Val[i];
    }
    float valf = val * (11.0/NB_VAL_ADC_MOY) * (3.3/4096);
    
    printf("Vin %.2f\r\n", (double)(valf));
    return 0;
}

void __attribute__((interrupt, auto_psv)) _ADC1Interrupt(void) {
    IFS0bits.AD1IF = 0;
    if (ADC_State == 0) {
        Vin_Val[Vin_Val_Ptr] = ADC1BUF0;
        Vin_Val_Ptr ++;
        if (Vin_Val_Ptr >= NB_VAL_ADC_MOY)
            Vin_Val_Ptr = 0;
        
        ADC_State = 1;
        AD1CHS0bits.CH0SA = 5;  // ira mesurer voie 5
    } else if (ADC_State == 1) {
        Cam_ADC_Val = ADC1BUF0;
        ADC_State = 2;
        AD1CHS0bits.CH0SA = 0;  // ira mesurer voie 0
    } else {
        ADC_State = 0;
        Vmot_ADC_Val = ADC1BUF0;
        AD1CHS0bits.CH0SA = 4;  // ira mesurer voie 4
    }
    AD1CON1bits.SAMP = 1;   // demarre une conversion
    //Nb_ADC_Conv ++;
}