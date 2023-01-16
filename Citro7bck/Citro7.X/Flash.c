#include "main.h"

#ifdef FLASH_HANDLER


u8 Dummy_DONE;


//-----------------------RdSr
u8 Flash_rdsr(void)   //lecture status.
{
    volatile u8 Fash_RD_Status_RETURN = 0;
    volatile u8 Fash_RD_Status_DONE = 0;
    while (!Place_In_DMA_Flash_Requests()) {
		Flash_Handler_Loop();
		SPI_Low_Handler_Loop();
	}
    Fash_RD_Status_DONE = 0;
    ADD_DMA_Flash_Request(DMA_SPI_FLASH_STATUS, 1, 0, ((u8*)(&Fash_RD_Status_RETURN)), ((u8*)(&Fash_RD_Status_DONE)));
    while (!Fash_RD_Status_DONE) {
		Flash_Handler_Loop();
		SPI_Low_Handler_Loop();
	}
    return Fash_RD_Status_RETURN;
}

//-----------------------Wr
u32 Flash_wr(u32 nbr_data, u32 addr, void * ptr_on_data )
{
    u8 *Ptr_on_u8 = (u8*)(ptr_on_data);
    volatile u8 Flash_WR_DONE = 1;
    u32 val32;
    while (nbr_data != 0) {
        while (!Place_In_DMA_Flash_Requests()) {
			Flash_Handler_Loop();
			SPI_Low_Handler_Loop();
		}
        if ( ( (addr % FL_PAGE_BYTES) + nbr_data) > FL_PAGE_BYTES) {   // si addr+nbr data passe à la page d'après on écrit tout ce que l'on peut
            val32 =  (FL_PAGE_BYTES -(addr%FL_PAGE_BYTES));
            ADD_DMA_Flash_Request(DMA_SPI_FLASH_WR, addr, val32 , Ptr_on_u8, &Dummy_DONE);
            nbr_data -= val32;
            Ptr_on_u8 =  &Ptr_on_u8[val32];
            addr += val32;
        } else {    // sinon, on est à la fin de l'écriture
            Flash_WR_DONE = 0;
            ADD_DMA_Flash_Request(DMA_SPI_FLASH_WR, addr, nbr_data , ptr_on_data, ((u8*)(&Flash_WR_DONE)));
            addr += nbr_data;
            nbr_data = 0;
        }
    }
    while (!Flash_WR_DONE) {
		Flash_Handler_Loop();
		SPI_Low_Handler_Loop();
	} // attente fin du dernier transfert
	
    return  addr;
}


//-----------------------Wr avec un Done Externe
u32 Flash_wr_Ext_Done(u32 nbr_data, u32 addr, void *ptr_on_data, volatile void *ptr_On_Done )
{
    u32 val32;
    u8 *Ptr_on_u8 = (u8*)(ptr_on_data);
    if (nbr_data != 0) {
        while (nbr_data != 0) {
            while (!Place_In_DMA_Flash_Requests()) {
				Flash_Handler_Loop();
				SPI_Low_Handler_Loop();
			}
            if ( ( (addr % FL_PAGE_BYTES) + nbr_data) > FL_PAGE_BYTES) {   // si addr+nbr data passe à la page d'après on écrit tout ce que l'on peut
                val32 =  (FL_PAGE_BYTES -(addr%FL_PAGE_BYTES));
                ADD_DMA_Flash_Request(DMA_SPI_FLASH_WR, addr, val32 , Ptr_on_u8, &Dummy_DONE);
                nbr_data -= val32;
                Ptr_on_u8 =  &Ptr_on_u8[val32];
                addr += val32;
            } else {    // sinon, on est à la fin de l'écriture
                ADD_DMA_Flash_Request(DMA_SPI_FLASH_WR, addr, nbr_data , ptr_on_data, ptr_On_Done);
                addr += nbr_data;
                nbr_data = 0;
            }
        }
    } else {
        *((volatile u8*)(ptr_On_Done)) = 1;
    }
    return  addr;
}

//--------------------------Rd
u32 Flash_rd(u32 nbr_data, u32 addr, void * ptr_on_data )
{
    volatile u8 Flash_RD_DONE = 1;
    u8 *Ptr_on_u8 = (u8*)(ptr_on_data);
    // lit par bouts de FL_PAGE_BYTES dans la flash..., pas besoin d'être alligné avec les pages de la flash
    while (nbr_data != 0) {
        while (!Place_In_DMA_Flash_Requests()) {
			Flash_Handler_Loop();
			SPI_Low_Handler_Loop();
		}
        if (nbr_data > FL_PAGE_BYTES) {
            ADD_DMA_Flash_Request(DMA_SPI_FLASH_RD, addr, FL_PAGE_BYTES, Ptr_on_u8, &Dummy_DONE);
            addr += FL_PAGE_BYTES;
            Ptr_on_u8 =  &Ptr_on_u8[FL_PAGE_BYTES];
            nbr_data -= FL_PAGE_BYTES;
        } else {
            Flash_RD_DONE = 0;
            ADD_DMA_Flash_Request(DMA_SPI_FLASH_RD, addr, nbr_data, Ptr_on_u8, ((u8*)(&Flash_RD_DONE)));
            addr += nbr_data;
            nbr_data = 0;
        }
    }
    while (!Flash_RD_DONE) {
		Flash_Handler_Loop();
		SPI_Low_Handler_Loop();
	}
    return  addr;
} 

//--------------------------Rd avec un Done externe
u32 Flash_rd_Ext_Done(u32 nbr_data, u32 addr, void *ptr_on_data, volatile void *ptr_On_Done )
{
    // lit par bouts de FL_PAGE_BYTES dans la flash..., pas besoin d'être alligné avec les pages de la flash
    u8 *Ptr_on_u8 = (u8*)(ptr_on_data);
    if (nbr_data != 0) {
        while (nbr_data != 0) {
            while (!Place_In_DMA_Flash_Requests()) {
				Flash_Handler_Loop();
				SPI_Low_Handler_Loop();
			}
            if (nbr_data > FL_PAGE_BYTES) {
                ADD_DMA_Flash_Request(DMA_SPI_FLASH_RD, addr, FL_PAGE_BYTES, Ptr_on_u8, &Dummy_DONE);
                addr += FL_PAGE_BYTES;
                Ptr_on_u8 =  &Ptr_on_u8[FL_PAGE_BYTES];
                nbr_data -= FL_PAGE_BYTES;
            } else {
                ADD_DMA_Flash_Request(DMA_SPI_FLASH_RD, addr, nbr_data, Ptr_on_u8, ptr_On_Done);
                addr += nbr_data;
                nbr_data = 0;
            }
        }
    } else {
        *((volatile u8*)(ptr_On_Done)) = 1;
    }
    return  addr;
} 


// ----------------------- Erase sector
//volatile u8 Flash_ER_DONE = 0;

void Flash_sectorerase(u32 num_sector)
{
    u32 addr = FL_SECTOR_BYTES * num_sector;
    //volatile u8 Flash_ER_DONE = 0;
    
    while (!Place_In_DMA_Flash_Requests()) {
		Flash_Handler_Loop();
		SPI_Low_Handler_Loop();
	}
    //Flash_ER_DONE = 0;
    ADD_DMA_Flash_Request(DMA_SPI_FLASH_ER, addr, 1, 0, &Dummy_DONE);
    //ADD_DMA_Flash_Request(DMA_SPI_FLASH_ER, addr, 1, 0, ((u8*)(&Flash_ER_DONE)));
    //while (!Flash_ER_DONE);
    // on se moque de quand c'est fini
}

u8 Flash_Sector_is_Full_FF(u32 num_sector)
{
    u8 will_return = 1;
    u32 addr = num_sector*FL_SECTOR_BYTES;
    u32 last_addr = addr + FL_SECTOR_BYTES;
    u32 i;
    u8 big_buff[FL_PAGE_BYTES] = {0};
    
    while ( (addr < last_addr) && (will_return) ) {
        addr = Flash_rd(FL_PAGE_BYTES, addr, &big_buff[0]);
        for (i = 0; i < FL_PAGE_BYTES; i++) {
            if (big_buff[i] != 0xFF)
                will_return = 0;
        }
    }
    return will_return;
}

inline u8 Flash_isnotready(void)
{   
	return Get_DMA_Is_Busy();		// =1 si DMA n'est pas au repos
}   

// pour savoir combien on peut écrire jusq'à la fin de la page
// plutot simple, mais permetra de garde les algos si on change de flash
inline u32 Flash_Get_Max_Chunk_Size (u32 addr)
{
    return FL_PAGE_BYTES - (addr % FL_PAGE_BYTES);   
}


// Commandes terminales :
// ***********************
/*
unsigned short FlashId_Func(unsigned short Type)
{
  return inQueuel("0x%X",Flash_rdid());
}
*/
u8 FlashStatus_Func(void)
{
    printf("0x%X\n",Flash_rdsr());
	return 0;
}

u8 FlashRd_Func(void)
{
    u32 add;
    u32 val32;
    if(Get_Param_x32(&add))  return PARAM_ERROR_CODE;
	Flash_rd(4,add,&val32);
	printf("0x%lX\n",val32);
    return 0;
}

u8 FlashWr_Func(void)
{
    u32 add;
    u32 val32;
    if(Get_Param_x32(&add))  return PARAM_ERROR_CODE;
	if(Get_Param_x32(&val32))  return PARAM_ERROR_CODE;
	Flash_wr(4,add,&val32);
    return 0;
}

u8 FlashEr_Func(void)
{
    u32 val;
    if(Get_Param_x32(&val))  return PARAM_ERROR_CODE;
    if (val >= FL_NB_SECTOR)  return PARAM_OUT_OF_RANGE_ERROR_CODE;
	
    printf("Erase sector 0x%lX..", val);
    Flash_sectorerase(val);
    printf(" Ok!\r\n");
    return 0;
}

u8 FlashRawSector_Rd_Func(void)  // pas vraiment un secteur entier...
{
    u32 add,i;
    u8 buff[512];
    if(Get_Param_x32(&add))  return PARAM_ERROR_CODE;
    
    printf("Reading address 0x%08lX:\r\n", add);
    
    Flash_rd(512,add,&buff[0]);
    
    for (i = 0; i < 512; i++) {
        printf("%02X", buff[i]);
        if ((i&0x1F) == 0x1F ) printf("\r\n");
    }
    return 0;
}



#endif