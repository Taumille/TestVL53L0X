

#ifndef __MOTOR_OUT_H
#define __MOTOR_OUT_H

#ifdef MOTOR_HANDLER


#define H_BRIDGE_DIR_PIN DRV2_PIN
#define MOTOR_PWM_MAX 50
#define MOTOR_PWM_GAIN 0.3

void Motor_Out_Init(void);
void Set_Motor_PWM(float PWM);// prend un nombre en -100 a +100
void Motor_Protec_Loop (void);

#endif
#endif

