
#ifndef TOF_H
#define	TOF_H

void TOF_I2C_Write(uint8_t, uint8_t, uint8_t[]);
void TOF_I2C_Read(uint8_t, uint8_t, uint8_t[]);
void TOF_I2C_Init (void);
void TOF_Change_Addr(uint8_t);

void TOF_Random(void);
void TOF_I2C_Start_Continuous(uint32_t);
void TOF_Get_Measure_Loop(uint16_t*);

#endif	/* TOF_H */

