#include "main.h"

#ifdef FLASH_HANDLER

DMA_Flash_Request SPI_DMA_Flash_Requests[MAX_DMA_FLASH_REQUESTS];



volatile u8 Indice_SPI_DMA_Flash_Requests_TODO = 0, Indice_SPI_DMA_Flash_Requests_DONE = 0;


// déclaration de pointeurs en u8 sur les tableaux ci-dessus
u8 Flash_SPI_TX_Tab[TAILLE_BUFFERS_DMA_SPI];
u8 Flash_SPI_RX_Tab[TAILLE_BUFFERS_DMA_SPI];
u8 Flash_SPI_Transfert_Done = 2;	// 0 = en cours, 1 = fait, 2 = données traités


volatile u8 DMA_Is_Busy = 0;


void Flash_Handler_Loop (void)
{
    static u16 Flash_Is_Ready = 0;      // possible de lancer une action sur la flash?
    
    u16 Flash_Wr_En = 0;
    
    static u16 Last_Request_Action = 0;
    static u16 Last_Request_Nb_Bytes = 0;
    static u8* Last_Request_Ptr_On_Data;
    static volatile u8* Last_Request_Ptr_On_Done;
    
    u16 i, i_max;
    u16 Request;
    u8 Done;
    
    
    u8* Pointer_On_U8;
	if (Flash_SPI_Transfert_Done == 1) {
		Flash_SPI_Transfert_Done = 2;
		//_puts ("Flash : ");
		if (Last_Request_Action == DMA_SPI_AUTO_FLASH_STATUS) {        // si dernier acces était demande automatique de status
			//_puts ("was Auto Status ");
			//printf("Got 0x%02X\r\n", Flash_SPI_RX_Tab[TAILLE_BUFFERS_DMA_SPI-1]);
			if ( !(Flash_SPI_RX_Tab[TAILLE_BUFFERS_DMA_SPI-1] & 0x01) ) {      // si bit "opération en cours" du dernier status lu == 0
				Flash_Is_Ready = 1;                 // c'est que la flash est dispo
			}
		} else if (Last_Request_Action == DMA_SPI_AUTO_FLASH_WR_EN) {
			//_puts ("was Auto Wr En\r\n");
			Flash_Wr_En = 1;
		} else if ((Last_Request_Action == DMA_SPI_FLASH_WR ) || (Last_Request_Action == DMA_SPI_FLASH_ER)) {
			// si ce qu'il vient de se passer est une opération d'écriture ou d'effacement
			// elle est donc finie, et pas besoin de copier les résultats vers un autre buffer => on dit "done"
			//_puts ("was Wr or Er\r\n");
			*Last_Request_Ptr_On_Done = 1;
			Flash_Is_Ready = 0;     // et la flash perd son statut "ready"
		} else if (Last_Request_Action == DMA_SPI_FLASH_RD) {  // si la derniere opération était une lecture
			//_puts ("was Rd ");
			// il faut copier ce qui a été lu vers l'emplacement mémoire prévu pour
			i_max = Last_Request_Nb_Bytes;     // le nombre de données qui ont étés lues
			if (i_max > FL_PAGE_BYTES) {
				i_max = FL_PAGE_BYTES;
			}
			//printf("Send %d datas to 0x%08X\r\n", i_max, Last_Request_Ptr_On_Data);
			Pointer_On_U8 = &Flash_SPI_RX_Tab[4];
			for (i = 0; i < i_max; i++) {        // copie en elle même
				Last_Request_Ptr_On_Data[i] = Pointer_On_U8[i];
			}
			// puis prevenir que c'est "pret" : Done = 1
			*Last_Request_Ptr_On_Done = 1;
		} else if (Last_Request_Action == DMA_SPI_FLASH_STATUS) {      // si la derniere action était une lecture de statut demandée
			//_puts ("was Status\r\n");
			// il faut copier l'octet lu vers l'emplacement indiqué
			*Last_Request_Ptr_On_Data = Flash_SPI_RX_Tab[1];
			// puis prevenir que c'est "pret" : Done = 1
			*Last_Request_Ptr_On_Done = 1;
		} else if (Last_Request_Action == DMA_SPI_FLASH_STATUS_SECOURS) {
			//_puts ("was Auto Status secours\r\n");
			// truc de secours en cas de pb lors des envois, ne rien faire
		}
	}
    
	
    // une fois la récupération des données dues, on passe à l'envoit des suivantes si nécessaire : 
    // suivi par la flash
        // dabord flash ready   si besoin
        // puis commande
    if (Flash_SPI_Transfert_Done == 2) {
		
		if (!Flash_Is_Ready) {		// si la flash n'est pas prete et que c'est pas au millieu d'une commande d'écriture/effacement

			Last_Request_Action = DMA_SPI_AUTO_FLASH_STATUS;
			Flash_SPI_TX_Tab[0] = FLASH_OP_RDSR;     // premier octet = commande status
			// 260 transferts = 1 commande pour status, puis pleins de lectures 
			// histoire de patienter un peu (c'est lent du coté flash, histoire de pas déclencher le code trop de fois)
			Flash_SPI_Transfert_Done = 0;
			Add_SPI_Transtion (SPI_FLASH_CONFIG, TAILLE_BUFFERS_DMA_SPI, &Flash_SPI_TX_Tab[0], &Flash_SPI_RX_Tab[0], &Flash_SPI_Transfert_Done);
			
			
		} else if (Indice_SPI_DMA_Flash_Requests_TODO != Indice_SPI_DMA_Flash_Requests_DONE) {
			DMA_Is_Busy = 1;

			Done = Indice_SPI_DMA_Flash_Requests_DONE;
			u16 Nb_Flash_SPI_Transferts_TODO = 0;
			
			Request = SPI_DMA_Flash_Requests[Done].Flash_Action;
			if ((!Flash_Wr_En) && ( (Request == DMA_SPI_FLASH_WR) || (Request == DMA_SPI_FLASH_ER) ) ) {
				// si la prochaine commande est une commande de Write ou erase et que l'on a pas envoyé Wr_Enable
				Last_Request_Action = DMA_SPI_AUTO_FLASH_WR_EN;
				Flash_SPI_TX_Tab[0] = FLASH_OP_WREN;
				Nb_Flash_SPI_Transferts_TODO = 1;     // seulement 1 transfert
			} else {
				Flash_SPI_TX_Tab[1] = (u8)((SPI_DMA_Flash_Requests[Done].Flash_Addr >> 16) & 0xFF);
				Flash_SPI_TX_Tab[2] = (u8)((SPI_DMA_Flash_Requests[Done].Flash_Addr >> 8)  & 0xFF);
				Flash_SPI_TX_Tab[3] = (u8)((SPI_DMA_Flash_Requests[Done].Flash_Addr     )  & 0xFF);
				////printf ("addr 0x%06X : 0x%02X 0x%02X 0x%02X\r\n", SPI_DMA_Flash_Requests[Done].Flash_Addr, Flash_SPI_TX_Tab[1], Flash_SPI_TX_Tab[2], Flash_SPI_TX_Tab[3]);
				i_max = (u16)(SPI_DMA_Flash_Requests[Done].Nb_Bytes);
				if (i_max > FL_PAGE_BYTES) {
					i_max = FL_PAGE_BYTES;
				}
				
				if (Request == DMA_SPI_FLASH_WR) {
					Last_Request_Action = DMA_SPI_FLASH_WR;
					Flash_SPI_TX_Tab[0] = FLASH_OP_PPG;
					
					Pointer_On_U8 = &Flash_SPI_TX_Tab[4];
					for (i = 0; i < i_max; i++) {        // copie en elle même
						Pointer_On_U8[i] = SPI_DMA_Flash_Requests[Done].Ptr_On_Data[i];
					}
					//Mem_Copy(SPI_DMA_Flash_Requests[Done].Ptr_On_Data, &Flash_SPI_TX_Tab[4], i_max);     // copie
					Nb_Flash_SPI_Transferts_TODO = 4 + i_max;
				} else if (Request == DMA_SPI_FLASH_ER) {
					Last_Request_Action = DMA_SPI_FLASH_ER;
					Flash_SPI_TX_Tab[0] = FLASH_OP_SE;
					Nb_Flash_SPI_Transferts_TODO = 4;
				} else if (Request == DMA_SPI_FLASH_RD) {
					Last_Request_Action = DMA_SPI_FLASH_RD;
					Flash_SPI_TX_Tab[0] = FLASH_OP_READ;
					Nb_Flash_SPI_Transferts_TODO = 4 + i_max;
				} else if (Request == DMA_SPI_FLASH_STATUS) {
					Last_Request_Action = DMA_SPI_FLASH_STATUS;
					Flash_SPI_TX_Tab[0] = FLASH_OP_RDSR;
					Nb_Flash_SPI_Transferts_TODO = 2;
				} else {
					Last_Request_Action = DMA_SPI_FLASH_STATUS_SECOURS;
					Flash_SPI_TX_Tab[0] = FLASH_OP_RDSR;
					Nb_Flash_SPI_Transferts_TODO = 2;
				}
				Last_Request_Nb_Bytes = i_max;
				Last_Request_Ptr_On_Data = SPI_DMA_Flash_Requests[Done].Ptr_On_Data;
				Last_Request_Ptr_On_Done = SPI_DMA_Flash_Requests[Done].Ptr_On_Done;
				// maintenant que l'on a récupéré les caracteristiques du transfert,
				// on peut libérer la case dans le tableau des request
				Done ++;
				if (Done >= MAX_DMA_FLASH_REQUESTS) {
					Done = 0;
				}
				Indice_SPI_DMA_Flash_Requests_DONE = Done;
			}

			Flash_SPI_Transfert_Done = 0;
			Add_SPI_Transtion (SPI_FLASH_CONFIG, Nb_Flash_SPI_Transferts_TODO, &Flash_SPI_TX_Tab[0], &Flash_SPI_RX_Tab[0], &Flash_SPI_Transfert_Done);

			
		} else {    // si plus rien à faire
			Last_Request_Action = 0;    // rien
			DMA_Is_Busy = 0;
		}
	}
}


/****************************************************************************************
*                                                                                       *
*                       M25P64                                                          *
*                       ------                                                          *
*****************************************************************************************/


u8 Place_In_DMA_Flash_Requests(void)
{   
    u16 used = (MAX_DMA_FLASH_REQUESTS + Indice_SPI_DMA_Flash_Requests_TODO - Indice_SPI_DMA_Flash_Requests_DONE) % MAX_DMA_FLASH_REQUESTS;
    u16 Place = (MAX_DMA_FLASH_REQUESTS-1) - used;
    
    Place = Max_Ternaire(Place, 2);
    return Place - 2;
}


u8 ADD_DMA_Flash_Request(u16 Action, u32 Flash_Addr, u16 nb_data, void *ptr_on_data, volatile void *ptr_On_Done)
{
    u8 val8;
    
    val8 = Indice_SPI_DMA_Flash_Requests_TODO;
    
    if (nb_data != 0) {
        SPI_DMA_Flash_Requests[val8].Flash_Action = Action;
        SPI_DMA_Flash_Requests[val8].Flash_Addr = Flash_Addr;
        SPI_DMA_Flash_Requests[val8].Nb_Bytes = nb_data;
        SPI_DMA_Flash_Requests[val8].Ptr_On_Data = ptr_on_data;
        SPI_DMA_Flash_Requests[val8].Ptr_On_Done = (volatile u8*)(ptr_On_Done);
        val8++;
        if (val8 == MAX_DMA_FLASH_REQUESTS) {
            val8 = 0;
        }
        Indice_SPI_DMA_Flash_Requests_TODO = val8;
    } else {
        *((volatile u8*)(ptr_On_Done)) = 1;
    }
    
    return 0;
}

inline u8 Get_DMA_Is_Busy (void)
{
    return DMA_Is_Busy;
}



#endif


