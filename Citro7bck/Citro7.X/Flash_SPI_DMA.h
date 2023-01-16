
#ifndef __FLASH_SPI_DMA_H
#define __FLASH_SPI_DMA_H

#ifdef FLASH_HANDLER

void IT_DMA_Handler (void);



#define FLASH_OP_WREN          0x06    // wr enable (before each erase or write cmd)
#define FLASH_OP_RDID          0x9F    // Read memory ident
#define FLASH_OP_RDSR          0x05    // Read Status Register
#define FLASH_OP_READ          0x03    // Normal read command
#define FLASH_OP_PPG           0x02    // Page Programm
#define FLASH_OP_SE            0xD8    // Sector/Block Erase
#define FLASH_OP_WRSR          0x01    // Write status register



#define TAILLE_BUFFERS_DMA_SPI (FL_PAGE_BYTES + 4)      //   + 4 pour commande + 3 adresses

#define MAX_DMA_FLASH_REQUESTS      4


#define DMA_SPI_FLASH_ACCESS        0xFE00

#define DMA_SPI_AUTO_FLASH_STATUS   0x8000
#define DMA_SPI_AUTO_FLASH_WR_EN    0x4000
#define DMA_SPI_FLASH_WR            0x2000
#define DMA_SPI_FLASH_ER            0x1000
#define DMA_SPI_FLASH_RD            0x0800
#define DMA_SPI_FLASH_STATUS        0x0400
#define DMA_SPI_FLASH_STATUS_SECOURS  0x0200


typedef struct {
    u16 Flash_Action;
    u16 Nb_Bytes;
    u32 Flash_Addr;
    u8 *Ptr_On_Data;
    volatile u8 *Ptr_On_Done;
} DMA_Flash_Request;


void Flash_Handler_Loop (void);

u8 Place_In_DMA_Flash_Requests(void);
u8 ADD_DMA_Flash_Request(u16 Action, u32 Flash_Addr, u16 nb_data, void *ptr_on_data, volatile void *ptr_on_done);

inline u8 Get_DMA_Is_Busy (void);



#endif
#endif



