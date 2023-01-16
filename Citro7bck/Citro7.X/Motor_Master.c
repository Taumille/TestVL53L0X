
#include "main.h"

#ifdef MOTOR_MASTER

uint8_t Main_I2C_Done = 0;
uint8_t I2C_Cmd1[3] = {20, 0, 150};
uint8_t I2C_Cmd2[3] = {20, 0, 150};

uint8_t Motor_Master_Func(void)
{
    float valf1, valf2;
    if (Get_Param_Float(&valf1)){
        return 2;
    }
    if (Get_Param_Float(&valf2)){
        return 2;
    }
    
    int16_t toto = valf1*100.0;
    
    I2C_Cmd1[1] = toto >> 8;
    I2C_Cmd1[2] = toto & 0xFF;
    
    toto = valf2*100.0;
    I2C_Cmd2[1] = toto >> 8;
    I2C_Cmd2[2] = toto & 0xFF;
    
    printf("sended %02X %02X, %02X %02X\n", I2C_Cmd1[1], I2C_Cmd1[2], I2C_Cmd2[1], I2C_Cmd2[2]);

    Add_I2C_command(0x30, 3, 0, &I2C_Cmd1[0], NULL, &Main_I2C_Done);
    Add_I2C_command(0x31, 3, 0, &I2C_Cmd2[0], NULL, &Main_I2C_Done);

    return 0;
}

#endif