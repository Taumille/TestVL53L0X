/* 
 * File:   main.h
 * Author: thomas
 *
 * Created on 22 novembre 2022, 20:50
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "UART.h"
#include "I2C.h"
#include "TOF.h"
#include "reg_VL53L0X.h"
#include "Timers.h"
#include <stddef.h>

#define SYS_FREQ        80000000UL
#define FCY             SYS_FREQ/2
#define FOSC            FCY
    
#define FP 40000000UL
#define BAUDRATE 9600
#define BRGVAL_UART_CMD ((FP/BAUDRATE)/16)-1

#define UART_RX_PIN_NB 12
#define UART_TX_PIN_REG _RP13R
    

#define I2C_SCL_PIN     _RB8
#define I2C_SCL_TRIS    _TRISB8
#define I2C_SDA_PIN     _RB9
#define I2C_SDA_TRIS    _TRISB9
    
    
    
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;    

void ConfigureOscillator(void);
int main();


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */
