#ifndef __TIMER_MS_H
#define __TIMER_MS_H



extern volatile uint32_t Timer_ms1;

void Timers_Init(void);

//unsigned int Get_Maxtime_Seq_AX12(void);
//void Set_Maxtime_Seq_AX12(unsigned int val);
//
//void Set_Maxtime(unsigned int val);
//char Get_Maxtime(void);

//ms

void Delay_ms(uint32_t Nb_ms);





#endif