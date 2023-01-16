
#ifndef __FLASH_H
#define __FLASH_H

#ifdef FLASH_HANDLER

u8 Flash_rdsr(void);
u32 Flash_wr(u32 nbr_data, u32 addr, void *ptr_on_data);
u32 Flash_wr_Ext_Done(u32 nbr_data, u32 addr, void *ptr_on_data, volatile void *ptr_On_Done);
u32 Flash_rd(u32 nbr_data, u32 addr, void *ptr_on_data);
u32 Flash_rd_Ext_Done(u32 nbr_data, u32 addr, void *ptr_on_data, volatile void *ptr_On_Done);

void Flash_sectorerase(u32 num_sector);
inline u8 Flash_isnotready(void);
inline u32 Flash_Get_Max_Chunk_Size (u32 addr);

u8 Flash_Sector_is_Full_FF(u32 num_sector);


#define FL_NB_SECTOR    128
#define FL_SECTOR_BYTES 0x010000   // Component Sector/Block size
#define FL_PAGE_BYTES   0x000100



u8 FlashStatus_Func(void);
u8 FlashRd_Func(void);
u8 FlashWr_Func(void);
u8 FlashEr_Func(void);
u8 FlashRawSector_Rd_Func(void);  // pas vraiment un secteur entier...


#endif
#endif




