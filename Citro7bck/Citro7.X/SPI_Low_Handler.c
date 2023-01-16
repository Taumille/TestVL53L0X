

#include "main.h"
#ifdef FLASH_HANDLER

SPI_Transaction SPI_Transaction_Tab[MAX_SPI_TRANSAC];

u16 SPI_Transaction_Tab_TODO = 0, SPI_Transaction_Tab_DONE = 0;
u16 SPI_Low_Handler_State = 0;

volatile u16 SPI_Tx_Count = 0;
volatile u16 SPI_Rx_Count = 0;

volatile SPI_Transaction Current_SPI_Transaction;
    
// use SPI1

void Add_SPI_Transtion (u8 Config, u16 NB_Transferts, u8 *ptr_to_send, u8 *ptr_to_get, u8 *ptr_on_done)
{
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].Config = Config;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].NB_Transferts = NB_Transferts;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].ptr_to_send = ptr_to_send;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].ptr_to_get = ptr_to_get;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].ptr_on_done = ptr_on_done;
	
	SPI_Transaction_Tab_TODO ++;
	if (SPI_Transaction_Tab_TODO >= MAX_SPI_TRANSAC)
		SPI_Transaction_Tab_TODO = 0;
    
}

void SPI_Low_Handler_Init(void)
{
	SPI_Low_Handler_State = 0;
	SPI_Transaction_Tab_TODO = 0;
	SPI_Transaction_Tab_DONE = 0;
	
	// init SPI
    SPI1CON1bits.SMP = 1;       // 1 = sample a la fin du bit, 0 = au milieu (STD)
    SPI1CON1bits.MODE16 = 0;    // 8 bits
    SPI1CON1bits.MSTEN = 1;     // Master
    
    SPI1CON1bits.SPRE = 0;      // de 0 à 7, 0 = 1/8, 7 = 1/1
    SPI1CON1bits.PPRE = 2;      // de 0 à 3, 0 = 1/64, 1 = 1/16, 2 = 1/4, 3 = 1/1
    // ne supporte pas que les 2 soient à 1/1 (3 et 7)
    
	// vu que FCY est à 40MHz
	// en divisant par 16, ça donne 2.5MHz, soit 0.4µs de période de bit, idéal pourr les Leds WSB
    
    
    IPC2bits.SPI1IP = 5;
    IFS0bits.SPI1IF = 0;
    IEC0bits.SPI1IE = 1;
}



void SPI_Low_Handler_Loop(void)
{
	
	switch (SPI_Low_Handler_State) {
		case 0:
			if (SPI_Transaction_Tab_DONE != SPI_Transaction_Tab_TODO) {
                SPI_Low_Handler_State ++;
            }
			break;
		case 1:
			SPI_Tx_Count = 1;
			SPI_Rx_Count = 0;
			Current_SPI_Transaction = SPI_Transaction_Tab[SPI_Transaction_Tab_DONE];
			SPI_Transaction_Tab_DONE ++;
			if (SPI_Transaction_Tab_DONE >= MAX_SPI_TRANSAC)
				SPI_Transaction_Tab_DONE = 0;
			Param_SPI_Transac(Current_SPI_Transaction.Config);
            SPI1STATbits.SPIEN = 1;
			SPI_Low_Handler_State ++;
            break;
		case 2:
            Start_End_SPI_Transac(Current_SPI_Transaction.Config, 0);
            SPI1BUF = Current_SPI_Transaction.ptr_to_send[0];
            //printf("S : %02X\n", Current_SPI_Transaction.ptr_to_send[SPI_Tx_Count]);
            //SPI_Tx_Count ++; dejà mis à 1 au début
            SPI_Low_Handler_State ++;
            break;
        case 3:
			
            /*if (SPI1STATbits.SPIRBF) {
				Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count] = SPI1BUF;
                //printf("G : %02X\n", Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count]);
				SPI_Rx_Count ++;
                // si on a tout recu, on sort, sinon on envoit l'octet suivant
				if (SPI_Rx_Count == Current_SPI_Transaction.NB_Transferts) {
					SPI_Low_Handler_State ++;
                } else {
                    SPI1BUF = Current_SPI_Transaction.ptr_to_send[SPI_Tx_Count];
                    //printf("S : %02X\n", Current_SPI_Transaction.ptr_to_send[SPI_Tx_Count]);
                    SPI_Tx_Count ++;
                }
			}*/
			break;
		case 4:
			Start_End_SPI_Transac(Current_SPI_Transaction.Config, 1);
			*(Current_SPI_Transaction.ptr_on_done) = 1;
			SPI_Low_Handler_State = 0;
            SPI1STATbits.SPIEN = 0;
            //SPI_EIO1_Test_Func();
            break;
		default:
			break;
	}
}



void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void)
{
    IFS0bits.SPI1IF = 0;        // clear flag
    if (SPI1STATbits.SPIRBF) {  // si qqchose à recevoir
        Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count] = SPI1BUF;
        //printf("G : %02X\n", Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count]);
        SPI_Rx_Count ++;
        // si on a tout recu, on sort, sinon on envoit l'octet suivant
        if (SPI_Rx_Count == Current_SPI_Transaction.NB_Transferts) {
            SPI_Low_Handler_State ++;
        }
    }
    // s'il me reste à envoyer, et qu'il reste de la place
    if (SPI_Tx_Count < Current_SPI_Transaction.NB_Transferts) {
        if (!SPI1STATbits.SPITBF) {
            SPI1BUF = Current_SPI_Transaction.ptr_to_send[SPI_Tx_Count];
            SPI_Tx_Count ++;
        }
    }
    
}

/*
 * CKE: SPIx Clock Edge Select bit
 * 1 = Serial output data changes on transition from active clock state to Idle clock state (see bit 6)
 * 0 = Serial output data changes on transition from Idle clock state to active clock state (see bit 6)
 * bit 6 CKP: Clock Polarity Select bit    
 * 1 = Idle state for clock is a high level; active state is a low level
 * 0 = Idle state for clock is a low level; active state is a high level
 *
 * CKE = not CPHA
 * CKP = CPOL
*/

void Param_SPI_Transac (u8 Config)
{
	switch (Config) {
		case SPI_FLASH_CONFIG:
			// config SPI + Pins pour flash
            
            //Modes PIN FLASH = 00 ou 11
            // choix 00
            SPI1CON1bits.CKE = 1;
            SPI1CON1bits.CKP = 0;
            
            _SDI1R = CON1_SPI_MISO_PIN_NB;
            CON1_SPI_MOSI_PIN_REG = _RPOUT_SDO1;
            CON1_SPI_SCLK_PIN_REG = _RPOUT_SCK1OUT;
            CON1_SPI_MISO_TRIS = 1;
            CON1_SPI_MOSI_TRIS = 0;
            CON1_SPI_SCLK_TRIS = 0;
            
            FLASH_CS = 1;
            FLASH_CS_TRIS = 0;
			break;
		default :
			break;
	}
    
}

void Start_End_SPI_Transac (u8 Config, u8 CS_Val)
{
	switch (Config) {
		case SPI_FLASH_CONFIG:
			FLASH_CS = CS_Val;
			break;
            
		default :
			break;
	}
}


#endif