

#include "main.h"


u8 SPI_Test_Tx_Buff[30];
u8 SPI_Test_Rx_Buff[30];
u8 SPI_Test_Done = 0;

/*
u8 SPI_Flash_Test_Func (void) 
{
    //printf("Last Done : %d\r\n", SPI_Test_Done);
    SPI_Test_Done = 0;
    SPI_Test_Tx_Buff[0] = 0x90;
    SPI_Test_Tx_Buff[1] = 0;
    SPI_Test_Tx_Buff[2] = 0;
    SPI_Test_Tx_Buff[3] = 0;
    SPI_Test_Tx_Buff[4] = 0;
    SPI_Test_Tx_Buff[5] = 0;
    
    Add_SPI_Transtion(SPI_FLASH_CONFIG, 6, &SPI_Test_Tx_Buff[0], &SPI_Test_Rx_Buff[0], &SPI_Test_Done);
    
    
    return 0;
}


u8 SPI_EIO1_Test_Func (void) 
{
    Set_ExpIO (0, SPI_EXPIO_CON2_CONFIG, 4, 0xF0C0, 0x0000);
    
    return 0;
}

u16 val_test_EIO = 1;

u8 SPI_EIO2_Test_Func (void) 
{
    u16 val16 = 1 << (val_test_EIO % 16);
    val_test_EIO ++;
    
    Set_ExpIO_Lat(0, val16);
    
    return 0;
}

 */



u8 Test_Timer_Func (void)
{
    printf("Day %d\r\n", My_Time.Day);
    printf("H   %d\r\n", My_Time.Hour);
    printf("Min %d\r\n", My_Time.Min);
    printf("Sec %d\r\n", My_Time.Sec);
    
    return 0;
    
}


uint8_t done;
    
uint8_t data_r[2] = {};
uint8_t data_s[2] = {0b00000111,0b11111111};

uint8_t Command_I2C_Func(void){
    #ifdef I2C_MASTER
        uint32_t val32;

        if (Get_Param_u32(&val32))
            return PARAM_ERROR_CODE;
        val32 = val32 << 3;
        data_s[0] = val32 | 7;
        Add_I2C_command(0b00100000, 2, 2, &data_s[0], &data_r[0], &done);
    #endif
    return 0;
}

/*
u8 Print_I2C_result (void)
{ 
    uint8_t a;
    if (cmd_I2C_DONE == 0){
        a = I2C_CMD_LIST_SIZE - 1;
    }else{
        a = cmd_I2C_DONE - 1;
    }
    printf("Read %d\r\n", Liste_I2C_Command[a].data_read[1]);
    printf("Send %d\r\n", Liste_I2C_Command[a].data_send[0]);
    return 0;
}*/
