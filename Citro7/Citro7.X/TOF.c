#include "main.h"

u16 TOF_State;
u16 TOF_I2C_Done;
u16 TOF_Timer;
u8 TOF_I2C_Write_Buff[20]= {0x5};
u8 TOF_I2C_Read_Buff[20]= {0x03};
uint8_t data[20];
u8 TOF_I2C_Read_Reg;
u8 stop_variable=0x17;

u8 TOF_Addr = 0x29;

void TOF_I2C_Init (void)
{
	TOF_State = 0;
	TOF_I2C_Done = 1;
	TOF_Timer = Timer_ms1;
    TOF_I2C_Read(0x91, 1, &stop_variable);
	
}

void TOF_I2C_Write(uint8_t reg, uint8_t nb, uint8_t data_send[])
{
    TOF_I2C_Done = 0;
    data[0] = reg;
    for(uint8_t i=1; i<nb+1; i++)
    {
      data[i] = data_send[i-1];
    }
    Add_I2C_command(TOF_Addr, nb+1, 0, &data[0], NULL, &TOF_I2C_Done);
}

void TOF_Change_Addr(uint8_t new_addr){
    uint8_t correct_addr = new_addr & 0x7F;
    TOF_I2C_Write(I2C_SLAVE_DEVICE_ADDRESS, 1, &correct_addr);
    TOF_Addr = correct_addr;
}

void TOF_I2C_Read(uint8_t reg, uint8_t Nb, uint8_t data_read[])
{
    TOF_I2C_Done = 0;
    TOF_I2C_Read_Reg = reg;
    Add_I2C_command(TOF_Addr, 1, Nb, &TOF_I2C_Read_Reg, data_read, &TOF_I2C_Done);
}

void TOF_I2C_Start_Continuous(uint32_t period_ms){
  uint8_t liste_value[7] = {0x01, 0x01, 0x00, stop_variable, 0x01, 0x00, 0x00};  
  uint8_t timing;
  
  TOF_I2C_Write(POWER_MANAGEMENT_GO1_POWER_FORCE, 1, &liste_value[0]);
  TOF_I2C_Write(0xFF, 1, &liste_value[1]);
  TOF_I2C_Write(SYSRANGE_START, 1, &liste_value[2]);
  TOF_I2C_Write(0x91, 1, &liste_value[3]);
  TOF_I2C_Write(SYSRANGE_START, 1, &liste_value[4]);
  TOF_I2C_Write(0xFF, 1, &liste_value[5]);
  TOF_I2C_Write(POWER_MANAGEMENT_GO1_POWER_FORCE, 1, &liste_value[6]);

  if (period_ms != 0)
  {
    // continuous timed mode

    // VL53L0X_SetInterMeasurementPeriodMilliSeconds() begin

    uint16_t osc_calibrate_val;
    TOF_I2C_Read(OSC_CALIBRATE_VAL, 2, (uint8_t*)&osc_calibrate_val);

    if (osc_calibrate_val != 0)
    {
      period_ms *= osc_calibrate_val;
    }

    uint8_t data[4];
    data[0] = period_ms >> 24;
    data[1] = period_ms >> 16;
    data[2] = period_ms >> 8;
    data[3] = period_ms;

    TOF_I2C_Write(SYSTEM_INTERMEASUREMENT_PERIOD, 4, data);

    // VL53L0X_SetInterMeasurementPeriodMilliSeconds() end
    
    timing = 0x04;
    
    TOF_I2C_Write(SYSRANGE_START, 1, &timing); // VL53L0X_REG_SYSRANGE_MODE_TIMED
  }
  else
  {
      timing = 0x02;
    // continuous back-to-back mode
    TOF_I2C_Write(SYSRANGE_START, 1, &timing); // VL53L0X_REG_SYSRANGE_MODE_BACKTOBACK
  }
}