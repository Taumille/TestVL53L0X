

#ifndef __SERVOS_H
#define __SERVOS_H

#ifdef SERVO_HANDLER

extern uint8_t Val_Servo1; // entre 0 et 100
extern uint8_t Val_Servo2;

void Gestion_Servos_Init(void);
void Gestion_Servos_Loop(void);

#endif

#ifdef SERVO_MASTER
uint8_t Servo_Master_Func(void);
#endif

#endif

