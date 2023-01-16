

#include "main.h"

#ifdef SERVO_HANDLER

uint16_t Last_Timer_Servo = 0;
uint8_t State_Servo = 0;

uint8_t Val_Servo1 = 50; // entre 0 et 100
uint8_t Val_Servo2 = 50;

int Count_Led_Debug = 0;


void Gestion_Servos_Init(void)
{
	SERVO1_PIN = 0;
	SERVO2_PIN = 0;
	SERVO1_TRIS = 0;
	SERVO2_TRIS = 0;
	
    T2CONbits.TCKPS = 1;    // prescaler 1/8
    T2CONbits.TCS = 0;      // prends l'horloge interne
    // freq d'entree = 40MHz (80/2), prescaler Ã  1/8, donc entree timer = 5Mz
	// 1 coup = 0.2us
    // il faut faire entre 0.5ms et 2.5ms, soit entre 2500 et 12500 coups
	TMR2 = 0;
    T2CONbits.TON = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    SERVO1_PIN = 0;
    SERVO2_PIN = 0;
    LED1 = 1;
	T2CONbits.TON = 0;
	TMR2 = 0;
	State_Servo ++;
}
	
void Gestion_Servos_Loop(void) {
    if (State_Servo == 0) {
		if ((Timer_ms1 - Last_Timer_Servo) > 20) {
			Last_Timer_Servo += 20;
			State_Servo ++;
		}
	} else if (State_Servo == 1) {
		// pin a 1, lancement Timer
		if (Val_Servo1 > 100) {
			Val_Servo1 = 100;
		}
        LED1 = 0;
        TMR2 = 0;
        IFS0bits.T2IF = 0;
		PR2 = 2500 + 100 * Val_Servo1;  // avec val Servo entre 0 et 100, ça donne entre 2500 (0.5ms) et 12500 (2.5ms)
		SERVO1_PIN = 1;
		State_Servo ++;
		T2CONbits.TON = 1;
		
	// } else if (State_Servo == 2) {
		// do nothing : c'est l'IT qui bossera
	} else if (State_Servo == 3) {
		// pin a 1, lancement Timer
		if (Val_Servo2 > 100) {
			Val_Servo2 = 100;
		}
        TMR2 = 0;
        IFS0bits.T2IF = 0;
		PR2 = 2500 + 100 * Val_Servo2;
		SERVO2_PIN = 1;
		State_Servo ++;
		T2CONbits.TON = 1;
	//} else if (State_Servo == 4) {
		// do nothing : c'est l'IT qui bossera
	} else if (State_Servo == 5) {
		State_Servo = 0;
        Count_Led_Debug ++;
        if (Count_Led_Debug >= 50) {
            Count_Led_Debug = 0;
            LED2 = !LED2;
        }
	}
		
}

#endif


#ifdef SERVO_MASTER

uint8_t I2C_Servo_Cmd[2];
uint8_t I2C_Servo_Cmd_Done;

uint8_t Servo_Master_Func(void)
{
    uint32_t Id, valf;
    if (Get_Param_u32(&Id)) return PARAM_ERROR_CODE;
	if (Id != 1 && Id != 2) return PARAM_OUT_OF_RANGE_ERROR_CODE;
    if (Get_Param_u32(&valf)) return PARAM_ERROR_CODE;
	if (valf < 0 || valf > 100) return PARAM_OUT_OF_RANGE_ERROR_CODE;
	
	
    I2C_Servo_Cmd[0] = 30 + Id;
	I2C_Servo_Cmd[1] = valf;

    Add_I2C_command(0x31, 2, 0, &I2C_Servo_Cmd[0], NULL, &I2C_Servo_Cmd_Done);

    return 0;
}


#endif


