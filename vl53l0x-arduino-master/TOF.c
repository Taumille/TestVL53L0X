#include "main.h"
#include "reg_VL53L0X.h"

u16 TOF_State;
u16 TOF_I2C_Done;
u16 TOF_Timer;
u8 stop_variable;

void TOF_I2C_Init (void)
{
	TOF_State = 0;
	TOF_I2C_Done = 1;
	TOF_Timer = Timer_ms1;
	
}

void TOF_I2C_Write(uint8_t reg, uint8_t Nb, uint8_t data_send[])
{
  while(!TOF_I2C_Done)
    TOF_I2C_Done = 0;
    uint8_t data[Nb+1];
    data[0] = reg;
    for(int i=1; i<Nb+1; i++)
    {
      data[i] = data_send[i-1];
    }
    Add_I2C_command(I2C_TOF_ADDR, Nb, 0, &data, 0, 0);
}

void TOF_I2C_Read(uint8_t reg, uint8_t Nb, uint8_t data_read[])
{
  while(!TOF_I2C_Done)
    TOF_I2C_Done = 0;
    Add_I2C_command(I2C_TOF_ADDR, 1, Nb, &reg, &data_read, 0);
}

void TOF_I2C_init(void)
{
  TOF_I2C_Read(0x91, 1, &stop_variable);
}

void TOF_I2C_Start_Continuous(uint32_t period_ms){
  TOF_I2C_Write(POWER_MANAGEMENT_GO1_POWER_FORCE, 1, 0x01);
  TOF_I2C_Write(0xFF, 1, 0x01);
  TOF_I2C_Write(SYSRANGE_START, 1, 0x00);
  TOF_I2C_Write(0x91, 1, stop_variable);
  TOF_I2C_Write(SYSRANGE_START, 1, 0x01);
  TOF_I2C_Write(0xFF, 1, 0x00);
  TOF_I2C_Write(POWER_MANAGEMENT_GO1_POWER_FORCE, 1, 0x00);

  if (period_ms != 0)
  {
    // continuous timed mode

    // VL53L0X_SetInterMeasurementPeriodMilliSeconds() begin

    uint16_t osc_calibrate_val = readReg16Bit(OSC_CALIBRATE_VAL);

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

    TOF_I2C_Write(SYSRANGE_START, 1, 0x04); // VL53L0X_REG_SYSRANGE_MODE_TIMED
  }
  else
  {
    // continuous back-to-back mode
    TOF_I2C_Write(SYSRANGE_START, 1, 0x02); // VL53L0X_REG_SYSRANGE_MODE_BACKTOBACK
  }
}