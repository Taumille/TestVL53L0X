
#ifndef __UART_LIDAR_H
#define __UART_LIDAR_H

#ifdef ENABLE_LIDAR

#define BAUDRATE_UART_LIDAR	128000
#define BRGVAL_UART_LIDAR ((FCY / BAUDRATE_UART_LIDAR / 16) - 1)

#define UART_LIDAR_SIZE_RX_BUFF 200
#define UART_LIDAR_SIZE_TX_BUFF 10

void UART_Lidar_Init(void);


void Send_Buff_Uart_Lidar(u8 Buff[], u8 Len);
u8 Get_Uart_Lidar(u8 *c);
u8 Lidar_Uart_RX_Is_Empty (void);

#endif
#endif
