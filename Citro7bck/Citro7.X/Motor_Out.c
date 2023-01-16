
#include "main.h"

#ifdef MOTOR_HANDLER

uint16_t Last_Timer_Motor_Order = 0;

void Motor_Out_Init (void) {
    
    PIC_DAC_TRIS = 0;
    PIC_DAC_PIN = 1;    // coupe la limite de courant pour l'instant
    
    DRV_NSLEEP_TRIS = 0;
    DRV_NSLEEP = 1;
    
    // DRV Mode � 0 : mode sens + PWM
    DRV_MODE_PIN = 0;
    DRV_MODE_TRIS = 0;
    
    
    DRV1_PIN = 0;   // EN
    DRV1_TRIS = 0;
    
    DRV2_PIN = 0;   // PH
    DRV2_TRIS = 0;
    
    
    
    // P1TCON
    P1TCONbits.PTEN = 1; // enable module PWM
    P1TCONbits.PTCKPS = 0; // Clk input of the PWM module is TCY (no prescale)
    P1TCONbits.PTMOD = 0; // free-runnig mode

    /*
     * la période des PWM (temps entre 2 fronts montants)
     * est fixée à 1500 cycles de 40MHz
     * ça donne une periode de sortie de 37.5 µs soit 26.66 kHz
     * RMQ : les registres de rapport cycliques ayant une précision double
     * leur valeur max sera 3000
     */
    P1TPER = 1500;

    //PWM1CON1
    PWM1CON1bits.PMOD1 = 1; // sorties independantes  (H et L))
    PWM1CON1bits.PMOD2 = 1;
    PWM1CON1bits.PMOD3 = 1;
    // desactivation de toutes les sorties
    // à réactiver une fois le pinout trouvé ;)

    // sorties High du pwm
    // remapage au fil, on oublie la pin 2H (seem really dead, even in GPIO)
    PWM1CON1bits.PEN1H = 1; // sortie pwm
    PWM1CON1bits.PEN2H = 0; // IO simple
    PWM1CON1bits.PEN3H = 0; // IO simple

    // sorties Low (opposé du High, on ne l'utilise pas)
    PWM1CON1bits.PEN1L = 0;
    PWM1CON1bits.PEN2L = 0;
    PWM1CON1bits.PEN3L = 0;

    P1TPER = 1500;

    P1DC1 = 0; // réglage des rapports cycliques, pour l'instant on mets 0 lors de l'initialisation
    
}
float Last_PWM_Req = 0;
// prend un nombre en -100 a +100
void Set_Motor_PWM (float PWM) {
    Last_PWM_Req = PWM;
    if (PWM >= 0) {
        H_BRIDGE_DIR_PIN = 0;
    } else {
        H_BRIDGE_DIR_PIN = 1;
        PWM = -PWM;
    }
    PWM = PWM * MOTOR_PWM_GAIN;
    
    // limitation des Duty-Cycle
    if (PWM > MOTOR_PWM_MAX)
        PWM = MOTOR_PWM_MAX;
    
    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC1 = (int) (30 * PWM);
    
    Last_Timer_Motor_Order = Timer_ms1;
    
}

void Motor_Protec_Loop (void) {
    if ((Timer_ms1 - Last_Timer_Motor_Order) > 2000) {
//        Set_Motor_PWM(0);   // si �a fait + de 2 secondes sans ordre, on coupe solo
    }
}

#endif