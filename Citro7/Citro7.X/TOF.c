#include "main.h"

u16 TOF_State;
u16 TOF_I2C_Done;
u16 TOF_Timer;
u8 TOF_I2C_Write_Buff[20];

void TOF_I2C_Init (void)
{
	TOF_State = 0;
	TOF_I2C_Done = 1;
	TOF_Timer = Timer_ms1;
	
}

void TOF_I2C_Write(uint8_t Nb)
{
	TOF_I2C_Done = 0;
	TOF_Timer = Timer_ms1;
	Add_I2C_command(I2C_TOF_ADDR, Nb, 0, &TOF_I2C_Write_Buff[0], NULL, &TOF_I2C_Done);
}

void TOF_Random(void)
{
    TOF_I2C_Write_Buff[0] = 0x38;
    TOF_I2C_Write(1);
}

