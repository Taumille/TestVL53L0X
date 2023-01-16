

#include "main.h"

#ifdef ENABLE_COM_UART


volatile u8 TX_CMD_Buff[UART_CMD_SIZE_BUFF];
volatile u16 i_TX_CMD_Buff_TODO = 0;
         u16 i_TX_CMD_Buff_DONE = 0;
		 
volatile u8 RX_CMD_Buff[UART_CMD_SIZE_BUFF] = { 0x02, 0x01, 0x5, 'h', 'e', 'l', 'p', '\n'};
volatile u16 i_RX_CMD_Buff_TODO = 0;
         u16 i_RX_CMD_Buff_DONE = 0;
		 
		 
void UART_Cmd_Init(void)
{
    u8 toto;
    
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
    
    i_TX_CMD_Buff_TODO = 0;
    i_TX_CMD_Buff_DONE = 0;
    i_RX_CMD_Buff_TODO = 0;
    i_RX_CMD_Buff_DONE = 0;

    
    //Remapage uart 1
    _U1RXR = UART_RX_PIN_NB;
    UART_TX_PIN_REG = _RPOUT_U1TX; // RP = U1TX (p.167)

    U1STAbits.UTXISEL1 = 1;
    U1STAbits.UTXISEL0 = 0;     // une interruption quand le buffer est vide
    U1STAbits.URXISEL = 0;      // IT en RX des la 1ere reception
    
    U1MODEbits.BRGH = 1;
    
    U1MODEbits.UARTEN = 1;      // va par defaut du registre OK (mode 8bit)
    U1STAbits.UTXEN = 1;        // enable TX  (apres UARTEN, sinon marche pas)
    U1BRG = BRGVAL_UART_CMD;


    // purge buffer récepetion
    IFS0bits.U1RXIF = 0;
    toto = U1RXREG;
    toto = U1RXREG;
    toto = U1RXREG;
    toto = U1RXREG;

    // vu qu'on peut gerer 4 transmits à la fois, c'est plus une IT super urgente..

    IPC2bits.U1RXIP = 2;
    IPC3bits.U1TXIP = 2;
    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 0;
    
    IFS0bits.U1TXIF = 1; // init le flag 


}

void __attribute__((interrupt, auto_psv)) _U1TXInterrupt(void) {
    // cette IT déclenche quand le buffer (FIFO de 4 places) devient vide
    // par contre, le shift register (ce qui est en train de transmètre), n'est pas forcément vide
    // on rajoute des choses dans la FIFO tant qu'elle n'est pas pleine, et tant que l'on a qqchose à envoyer
    
    while ((i_TX_CMD_Buff_DONE != i_TX_CMD_Buff_TODO) && (!U1STAbits.UTXBF)) {
        IFS0bits.U1TXIF = 0;
        U1TXREG = TX_CMD_Buff[i_TX_CMD_Buff_DONE];
        i_TX_CMD_Buff_DONE++;
        if (i_TX_CMD_Buff_DONE >= UART_CMD_SIZE_BUFF)
            i_TX_CMD_Buff_DONE = 0;
    }

    if (i_TX_CMD_Buff_DONE == i_TX_CMD_Buff_TODO) // si on a tout transmit, on s'arrete 
        IEC0bits.U1TXIE = 0;
}

void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void) {
    u16 i = i_RX_CMD_Buff_TODO;
    IFS0bits.U1RXIF = 0;
    while (U1STAbits.URXDA) { // tant que la FIFO de réception n'est pas vide
        RX_CMD_Buff[i] = U1RXREG;
        i++;
        if (i == UART_CMD_SIZE_BUFF)
            i = 0;
    }
    i_RX_CMD_Buff_TODO = i;
}

u16 Place_In_Uart_Cmd(void) {
    u16 In_Buff = (UART_CMD_SIZE_BUFF + i_TX_CMD_Buff_TODO - i_TX_CMD_Buff_DONE) % UART_CMD_SIZE_BUFF;
    return (UART_CMD_SIZE_BUFF-1) - In_Buff;
}

u8 Uart_Cmd_Is_Empty(void)
{
    return (i_TX_CMD_Buff_TODO == i_TX_CMD_Buff_DONE);
}

void Send_Uart_Cmd(u8 symbol) {
    u16 i = i_TX_CMD_Buff_TODO;
    TX_CMD_Buff[i] = symbol;
    i++;
    if (i >= UART_CMD_SIZE_BUFF) {
        i = 0;
    }
    i_TX_CMD_Buff_TODO = i;
    
    IEC0bits.U1TXIE = 1;
}

void Send_Buff_Uart_Cmd(u8 Buff[], u8 Len) {
	u8 j;
    u16 i = i_TX_CMD_Buff_TODO;
	for (j = 0; j < Len; j++) {
		TX_CMD_Buff[i] = Buff[j];
		i++;
		if (i >= UART_CMD_SIZE_BUFF) {
			i = 0;
		}
	}
    i_TX_CMD_Buff_TODO = i;
    IEC0bits.U1TXIE = 1;
}

u8 Get_Uart_Cmd(u8 *c) {
    if (i_RX_CMD_Buff_DONE != i_RX_CMD_Buff_TODO) { // si il y a qq chose dans le buffer
        *c = RX_CMD_Buff[i_RX_CMD_Buff_DONE];
        i_RX_CMD_Buff_DONE++;
        if (i_RX_CMD_Buff_DONE == UART_CMD_SIZE_BUFF)
            i_RX_CMD_Buff_DONE = 0;
        return 1;
    } else {
        return 0;
    }
}

#endif