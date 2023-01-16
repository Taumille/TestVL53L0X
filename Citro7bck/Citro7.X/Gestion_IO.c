

#include "main.h"


void Gestion_IO_Init(void) {
    
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    
    EN_VMOT_PIN = 1;
    EN_VMOT_PIN_TRIS = 0;
    
    #ifdef ENABLE_LIDAR
        EN_MOT_X4_PIN = 0;
        EN_MOT_X4_TRIS = 0;
    #endif
    
    

}


uint16_t Last_Timer_Led = 0;


void Gestion_IO_Loop(void) {
    
    if ((Timer_ms1 - Last_Timer_Led) > 1000) {
        Last_Timer_Led += 1000;
        //LED2 = !LED2;
        
    } 
}


