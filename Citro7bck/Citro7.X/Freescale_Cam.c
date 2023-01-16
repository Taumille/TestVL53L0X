

#include "main.h"

#ifdef CAM_HANDLER

uint16_t Cam_State = 0;
uint16_t Cam_Val_Tab[128];
uint16_t Last_Cam_Timer = 0;
uint8_t Cam_Print_State = 0;

extern uint16_t Cam_ADC_Val;    // dans l'ADC
extern uint16_t Vin_Val[NB_VAL_ADC_MOY];
extern uint16_t Vmot_ADC_Val;

void Freescale_Cam_Init(void)
{
    CLK_CAM_TRIS = 0;
    TRIG_CAM_TRIS = 0;
    
    T2CONbits.TON = 1;
    T2CONbits.TCKPS = 1;    // prescaler 1/8
    T2CONbits.TCS = 0;      // prends l'horloge interne
    // freq d'entree = 40MHz (80/2), prescaler à 1/8, donc entree timer = 5Mz
    PR2 = 400;  // => 5Mhz => 12.5kHz => 6.25k utile
    T2CONbits.TON = 1;
    
    IEC0bits.T2IE = 1;
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    uint8_t Clk = CLK_CAM;
    if (Clk) {  // on va generer un fallingedge
        if (!Cam_State) {
            if ((Timer_ms1 - Last_Cam_Timer) > 60) {
                Last_Cam_Timer += 60;
                Cam_State ++;
                TRIG_CAM = 1;
            }
        } else {
            TRIG_CAM = 0;
        }
    } else {    // on va generer un rising_edge
        if (Cam_State) {
            if (Cam_State >= 2) {
                Cam_Val_Tab[Cam_State - 2] = Cam_ADC_Val;
            }
            if (Cam_State < 129) {
                Cam_State ++;   // max fait = 129, le dernier sera stocké en 127
            } else {
                Cam_State = 0;
                Cam_Print_State = 1;
            }
        }
    }
    CLK_CAM = !Clk;
}

void Freescale_Cam_Loop(void)
{   
    if (Cam_Print_State) {
        if (Is_Std_Out_Empty()) {
            if (Cam_Print_State == 1) {
                printf("Start");
            }
            printf(",%u", Cam_Val_Tab[Cam_Print_State - 1]);
            if (Cam_Print_State >= 128) {
                printf("\n");
                Cam_Print_State = 0;
            } else {
                Cam_Print_State ++;
            }
        }
    }
    
}

#endif