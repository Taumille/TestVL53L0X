/* 
 * File:   UART.h
 * Author: thomas
 *
 * Created on 23 novembre 2022, 09:03
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"  

#define UART_CMD_SIZE_BUFF 300
    
    
void UART_Cmd_Init(void);
void Send_Uart_Cmd(uint8_t);
void printu(char *);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

