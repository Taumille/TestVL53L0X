
#ifndef TOF_H
#define	TOF_H

#define I2C_TOF_ADDR 0x29

void TOF_I2C_Write(uint8_t, uint8_t, uint8_t[]);
void TOF_I2C_Init (void);

void TOF_Random(void);

#endif	/* TOF_H */

