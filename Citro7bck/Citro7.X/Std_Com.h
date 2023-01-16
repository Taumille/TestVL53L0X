
#ifndef __STD_COM_H
#define __STD_COM_H


#define STD_COM_SIZE_BUFF 300

void Std_Com_Init(void);

void Send_Std_Out(u8 symbol);
int write(int handle, void *buffer, unsigned int len);

u16 Std_Out_Data_Count (void);
u16 Std_Out_To_Buff (u8 Buff[], u16 Max_Len);

u8 Is_Std_Out_Empty(void);


void Buff_To_Std_In (u8 Buff[], u16 Len);
u8 Get_Std_In(u8 *c);

void Std_Comm_Loop(void);

#endif
