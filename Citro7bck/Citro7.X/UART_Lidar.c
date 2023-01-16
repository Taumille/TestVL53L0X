

#include "main.h"

#ifdef ENABLE_LIDAR


volatile u8 TX_Lidar_Buff[UART_LIDAR_SIZE_TX_BUFF];
volatile u16 i_TX_Lidar_Buff_TODO = 0;
         u16 i_TX_Lidar_Buff_DONE = 0;
		 
volatile u8 RX_Lidar_Buff[UART_LIDAR_SIZE_RX_BUFF];
volatile u16 i_RX_Lidar_Buff_TODO = 0;
         u16 i_RX_Lidar_Buff_DONE = 0;
		 
		 
void UART_Lidar_Init(void)
{
    u8 toto;
    
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;
    
    i_TX_Lidar_Buff_TODO = 0;
    i_TX_Lidar_Buff_DONE = 0;
    i_RX_Lidar_Buff_TODO = 0;
    i_RX_Lidar_Buff_DONE = 0;

    
    //Remapage uart 2
    _U2RXR = UART_LIDAR_RX_PIN_NB;
    UART_LIDAR_TX_PIN_REG = _RPOUT_U2TX;

    
    
    U2STAbits.UTXISEL1 = 1;
    U2STAbits.UTXISEL0 = 0;     // une interruption quand le buffer est vide
    U2STAbits.URXISEL = 0;      // IT en RX des la 1ere reception
    
    U2MODEbits.UARTEN = 1;      // va par defaut du registre OK (mode 8bit)
    U2STAbits.UTXEN = 1;        // enable TX  (apres UARTEN, sinon marche pas)
    U2BRG = BRGVAL_UART_LIDAR;


    // purge buffer récepetion
    IFS1bits.U2RXIF = 0;
    toto = U2RXREG;
    toto = U2RXREG;
    toto = U2RXREG;
    toto = U2RXREG;

    // vu qu'on peut gerer 4 transmits à la fois, c'est plus une IT super urgente..

    IPC7bits.U2RXIP = 5;
    IPC7bits.U2TXIP = 1;
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    
    IFS1bits.U2TXIF = 1; // init le flag 

}


void __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void) {
    // cette IT déclenche quand le buffer (FIFO de 4 places) devient vide
    // par contre, le shift register (ce qui est en train de transmètre), n'est pas forcément vide
    // on rajoute des choses dans la FIFO tant qu'elle n'est pas pleine, et tant que l'on a qqchose à envoyer
    
    while ((i_TX_Lidar_Buff_DONE != i_TX_Lidar_Buff_TODO) && (!U2STAbits.UTXBF)) {
        IFS1bits.U2TXIF = 0;
        U2TXREG = TX_Lidar_Buff[i_TX_Lidar_Buff_DONE];
        i_TX_Lidar_Buff_DONE++;
        if (i_TX_Lidar_Buff_DONE >= UART_LIDAR_SIZE_TX_BUFF)
            i_TX_Lidar_Buff_DONE = 0;
    }

    if (i_TX_Lidar_Buff_DONE == i_TX_Lidar_Buff_TODO) // si on a tout transmit, on s'arrete 
        IEC1bits.U2TXIE = 0;
}

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void) {
    u16 i = i_RX_Lidar_Buff_TODO;
    IFS1bits.U2RXIF = 0;
    while (U2STAbits.URXDA) { // tant que la FIFO de réception n'est pas vide
        RX_Lidar_Buff[i] = U2RXREG;
        i++;
        if (i == UART_LIDAR_SIZE_RX_BUFF)
            i = 0;
    }
    i_RX_Lidar_Buff_TODO = i;
    if (i_RX_Lidar_Buff_TODO == i_RX_Lidar_Buff_DONE) {
        printf("Error Uart LidarRX\n");
    }
} 


void Send_Buff_Uart_Lidar(u8 Buff[], u8 Len) {
	u8 j;
    u16 i = i_TX_Lidar_Buff_TODO;
	for (j = 0; j < Len; j++) {
		TX_Lidar_Buff[i] = Buff[j];
		i++;
		if (i >= UART_LIDAR_SIZE_TX_BUFF) {
			i = 0;
		}
	}
    i_TX_Lidar_Buff_TODO = i;
    IEC1bits.U2TXIE = 1;
}

u8 Get_Uart_Lidar(u8 *c) {
    if (i_RX_Lidar_Buff_DONE != i_RX_Lidar_Buff_TODO) { // si il y a qq chose dans le buffer
        *c = RX_Lidar_Buff[i_RX_Lidar_Buff_DONE];
        i_RX_Lidar_Buff_DONE++;
        if (i_RX_Lidar_Buff_DONE == UART_LIDAR_SIZE_RX_BUFF)
            i_RX_Lidar_Buff_DONE = 0;
        return 1;
    } else {
        return 0;
    }
}

u8 Lidar_Uart_RX_Is_Empty (void) {
    return (i_RX_Lidar_Buff_DONE == i_RX_Lidar_Buff_TODO);
}
        


#endif