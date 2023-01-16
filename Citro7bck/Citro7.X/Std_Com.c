

#include "main.h"





u8 Std_Com_Out_Buff[STD_COM_SIZE_BUFF];
u16 i_Std_Com_Out_Buff_TODO = 0;
u16 i_Std_Com_Out_Buff_DONE = 0;

u8 Std_Com_In_Buff[STD_COM_SIZE_BUFF];
u16 i_Std_Com_In_Buff_TODO = 0;
u16 i_Std_Com_In_Buff_DONE = 0;


void Std_Com_Init (void)
{
	i_Std_Com_Out_Buff_TODO = 0;
	i_Std_Com_Out_Buff_DONE = 0;
	i_Std_Com_In_Buff_TODO = 0;
	i_Std_Com_In_Buff_DONE = 0;
}


void Send_Std_Out (u8 symbol)
{
    u16 i = i_Std_Com_Out_Buff_TODO;
    Std_Com_Out_Buff[i] = symbol;
    i++;
    if (i >= STD_COM_SIZE_BUFF) {
        i = 0;
    }
    i_Std_Com_Out_Buff_TODO = i;
}

int write (int handle, void *buffer, unsigned int len)	// printf entree
{
    unsigned int i;
    u8 *buff = buffer;
    for (i = 0; i < len; i++) {
        Send_Std_Out(*buff);
        buff++;
    }
    return len;
}

u16 Std_Out_Data_Count (void)
{
    return (STD_COM_SIZE_BUFF + i_Std_Com_Out_Buff_TODO - i_Std_Com_Out_Buff_DONE) % STD_COM_SIZE_BUFF;
}

u16 Std_Out_To_Buff (u8 Buff[], u16 Max_Len)
{
	u16 Len = 0;
	while (	(i_Std_Com_Out_Buff_DONE != i_Std_Com_Out_Buff_TODO) &&
			(Len < Max_Len)		) {
        Buff[Len] = Std_Com_Out_Buff[i_Std_Com_Out_Buff_DONE];
		Len++;
        i_Std_Com_Out_Buff_DONE++;
        if (i_Std_Com_Out_Buff_DONE >= STD_COM_SIZE_BUFF)
            i_Std_Com_Out_Buff_DONE = 0;
	}
    return Len;
}

u8 Is_Std_Out_Empty(void) {
    return (i_Std_Com_Out_Buff_TODO == i_Std_Com_Out_Buff_DONE);
}

void Buff_To_Std_In (u8 Buff[], u16 Len)
{
	u16 i;
	for (i = 0; i < Len; i++) {
		Std_Com_In_Buff[i_Std_Com_In_Buff_TODO] = Buff[i];
        i_Std_Com_In_Buff_TODO++;
        if (i_Std_Com_In_Buff_TODO >= STD_COM_SIZE_BUFF)
            i_Std_Com_In_Buff_TODO = 0;
	}
}

u8 Get_Std_In (u8 *c)
{
    if (i_Std_Com_In_Buff_DONE != i_Std_Com_In_Buff_TODO) { // si il y a qq chose dans le buffer
        *c = Std_Com_In_Buff[i_Std_Com_In_Buff_DONE];
        i_Std_Com_In_Buff_DONE++;
        if (i_Std_Com_In_Buff_DONE >= STD_COM_SIZE_BUFF)
            i_Std_Com_In_Buff_DONE = 0;
        return 1;
    } else {
        return 0;
    }
}

void Std_Comm_Loop(void)
{
    #ifdef ENABLE_COM_UART
        u8 c;
        u16 Max_Count;
        if (!Is_Std_Out_Empty()) {
            Max_Count = Place_In_Uart_Cmd();
            Max_Count = Min_Ternaire(Max_Count, 50);
            u8 Buff[50];
            Max_Count = Std_Out_To_Buff(&Buff[0], Max_Count);
            Send_Buff_Uart_Cmd(&Buff[0], Max_Count);
        }
        if (Get_Uart_Cmd(&c)) {
            Buff_To_Std_In(&c, 1);
        }
    #endif
}

