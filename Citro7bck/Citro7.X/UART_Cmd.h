
#ifndef __UART_CMD_H
#define __UART_CMD_H

#ifdef ENABLE_COM_UART

//#define BAUDRATECMD 1000000
//#define BAUDRATECMD 500000
//#define BAUDRATECMD 400000
//#define BAUDRATECMD 250000
//#define BAUDRATECMD 200000
//#define BAUDRATECMD 115200
//#define BAUDRATECMD 57600
//#define BAUDRATECMD 38400
//#define BAUDRATECMD 19200
//#define BAUDRATECMD 9600

#define UART_CMD_SIZE_BUFF 200

void UART_Cmd_Init(void);

u16 Place_In_Uart_Cmd(void);
u8 Uart_Cmd_Is_Empty(void);
void Send_Uart_Cmd(u8 symbol);
void Send_Buff_Uart_Cmd(u8 Buff[], u8 Len);
u8 Get_Uart_Cmd(u8 *c);

#endif
#endif
