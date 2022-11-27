#include "main.h"

volatile uint8_t state_i2c = 0;

uint32_t I2C_timer; //stockage du temps
uint8_t I2C_Maxtimed = 0;

uint8_t I2C_i = 0;

I2C_command Liste_I2C_Command[I2C_CMD_LIST_SIZE];
I2C_command Current_I2C_Cmd;

uint8_t cmd_I2C_DONE = 0;
uint8_t cmd_I2C_TODO = 0;

void Init_I2C(void){
    //setting baud rate:
    uint16_t Fscl = 20000;
    uint16_t BRG = (((1/Fscl))*FCY/2)-2;
    I2C1BRG = BRG;
    
    I2C1CONbits.IPMIEN = 0;
    
    IEC1bits.MI2C1IE = 1; //I2C Master Events interupt enable
    IPC4bits.MI2C1IP = 0b001; //priority 1
    
    I2C1CONbits.I2CEN = 1; //enable I2C
}

void Add_I2C_command(uint8_t i2c_addr, uint8_t nbr_byte_send, uint8_t nbr_byte_read, uint8_t data_send[], uint8_t data_read[], void *Done){
    Liste_I2C_Command[cmd_I2C_TODO].nbr_byte_send = nbr_byte_send;
    Liste_I2C_Command[cmd_I2C_TODO].nbr_byte_read = nbr_byte_read;
    Liste_I2C_Command[cmd_I2C_TODO].data_read = data_read;
    Liste_I2C_Command[cmd_I2C_TODO].data_send = data_send;
    Liste_I2C_Command[cmd_I2C_TODO].i2c_addr = i2c_addr;
    Liste_I2C_Command[cmd_I2C_TODO].Done = Done;
    cmd_I2C_TODO++;
    if(cmd_I2C_TODO == I2C_CMD_LIST_SIZE)
        cmd_I2C_TODO = 0;
}

void Transmit_I2C_Loop(void){
    switch (state_i2c){
        case 0:
            if(cmd_I2C_TODO != cmd_I2C_DONE){
                IFS1bits.MI2C1IF = 0;
                I2C1CONbits.I2CEN = 1;
                Current_I2C_Cmd = Liste_I2C_Command[cmd_I2C_DONE];
                state_i2c++;
            }
            break;
            
        case 1: //start event
            I2C1CONbits.SEN = 1; // Initiates the Start condition on the SDAx and SCLx pins
            I2C_i=0;
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 2://if (!I2C1CONbits.SEN)
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 3: //send device addr
            if (Current_I2C_Cmd.nbr_byte_send != 0){
                I2C1TRN = (Current_I2C_Cmd.i2c_addr << 1) + 0; // 7bits addr + R/W bit
                I2C_timer = Timer_ms1;
                state_i2c++;
            }else{
                state_i2c = 11;
            }
            break;
        case 4:
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 5: //acknoledge status bit 
            if (I2C1STATbits.ACKSTAT == 0) {
                state_i2c++;
            }else{
                state_i2c = 30;
            }
            break;     
        /////////////////////////////SEND///////////////////////////////////////    
        case 6:
            I2C1TRN = Current_I2C_Cmd.data_send[I2C_i];
            I2C_timer = Timer_ms1;
            I2C_i++;
            state_i2c++;
            break;
        case 7:
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 8:
            if (I2C1STATbits.ACKSTAT == 0) {
                if(I2C_i == Current_I2C_Cmd.nbr_byte_send){
                    state_i2c++;
                }else{
                    state_i2c = 6;
                }
            } else{
                state_i2c = 30;
            }
            break;  
        case 9:
            if (Current_I2C_Cmd.nbr_byte_read != 0){
                I2C_i=0;
                I2C1CONbits.RSEN = 1; // ReStart
                I2C_timer = Timer_ms1;
                state_i2c++;
            }else{
                state_i2c = 19;
            }
            break;
        case 10://if (!I2C1CONbits.RSEN)
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;   
        case 11:
            I2C1TRN = (Current_I2C_Cmd.i2c_addr << 1) + 1; // 7bits addr + R/W bit
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 12: 
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 13:
            if (I2C1STATbits.ACKSTAT == 0) {
                state_i2c++;
            }else{
                state_i2c = 30;
            }
            break;     
        //////////////////////////READ//////////////////////////////////////////    
        case 14:
            I2C1CONbits.RCEN = 1; //allow the master to receive data 
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 15://if (I2C1STAT.RBF == 1)
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 16:
            Current_I2C_Cmd.data_read[I2C_i] = I2C1RCV;
            I2C_i++;
            if(I2C_i == Current_I2C_Cmd.nbr_byte_read){
                I2C1CONbits.ACKDT = 1; //nack
                I2C1CONbits.ACKEN = 1;
            }else{
                I2C1CONbits.ACKDT = 0; //ack
                I2C1CONbits.ACKEN = 1; 
            }
            I2C_timer = Timer_ms1; 
            state_i2c++;
            break;
        case 17: //if (I2C1CONbits.ACKEN == 0) {
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 18:
            if(I2C_i == Current_I2C_Cmd.nbr_byte_read){
                state_i2c++;
            }else{
                state_i2c = 14;
            }
            break;
        case 19:
            I2C1CONbits.PEN = 1;
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 20:
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 21: // if (I2C1CONbits.PEN == 0)
            state_i2c = 30;
            break;
        case 30:
            // previent qu'on a fini :
            *((uint8_t*)Current_I2C_Cmd.Done) = 1;
            cmd_I2C_DONE++;
            if (cmd_I2C_DONE >= I2C_CMD_LIST_SIZE){
                cmd_I2C_DONE = 0;  
            }
            I2C1CONbits.I2CEN = 0;
            if (I2C_Maxtimed) {
                I2C_Maxtimed = 0;
                state_i2c = 31;
            } else {
                state_i2c = 0;
            }
            break;
        case 31:
            I2C_timer = Timer_ms1;
            I2C_SCL_PIN = 0;
            I2C_SCL_TRIS = 0;   // fabrique un coup d'horloge sur l'I2C
            state_i2c ++;
            break;
        case 32:
            if ((Timer_ms1 - I2C_timer) > 1) {
                I2C_SCL_PIN = 1;
                I2C_SCL_TRIS = 1;   // relache l'I2C
                state_i2c = 0;
            }
            break;
        default:
            break;
    }
}

void __attribute__((interrupt,auto_psv)) _MI2C1Interrupt (void){
    IFS1bits.MI2C1IF = 0;
    state_i2c ++;
}
