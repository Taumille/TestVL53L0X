

#include "main.h"

#ifdef ENABLE_LIDAR


u16 Lidar_Trame_Xor = 0;
u16 State_Lidar_Trame = 0;

u8 Lidar_Trame_Package_Type;
u16 Lidar_Trame_Sample_Qty;
float Lidar_Trame_Start_Angle, Lidar_Trame_End_Angle, Lidar_Point_Reso;
u16 Lidar_Trame_Check_Code;
u16 Lidar_Trame_Nb_Point = 0;
u32 All_Lidar_Points[360] = {0};
u16 All_Lidar_Points_Count[360];
u16 Lidar_Nb_Points = 0;
u16 Lidar_Nb_Good_Points = 0;


u16 Lidar_Print_Points[180];
u16 i_print_Lidar_Point = 0;


void Lidar_Loop(void)
{    
    static u32 Point_To_Print = 0;
    
    u8 Car_Lidar;
    static u16 Lidar_Rolling;
    if (Get_Uart_Lidar(&Car_Lidar)) {
        Lidar_Rolling = (((u16)(Car_Lidar)) << 8) + (Lidar_Rolling >> 8);
        
        switch (State_Lidar_Trame) {
            case 0:     // case 0 et 1 : detection du header
                if (Car_Lidar == 0xAA) {
                    State_Lidar_Trame++;
                }
                break;
            case 1:
                if (Car_Lidar == 0x55) {
                    State_Lidar_Trame++;
                    Lidar_Trame_Xor = 0x55AA;
                } else {
                    State_Lidar_Trame = 0;
                }
                break;
            case 2:
                Lidar_Trame_Package_Type = Car_Lidar;
                Lidar_Trame_Nb_Point = 0;
                State_Lidar_Trame++;
                break;
            case 3:
                Lidar_Trame_Sample_Qty = Car_Lidar;
                Lidar_Trame_Xor ^= Lidar_Rolling;
                State_Lidar_Trame++;
                break;
            // 4 en default ++
            case 5:
                Lidar_Trame_Start_Angle = (Lidar_Rolling >> 1) / 64.0;
                Lidar_Trame_Xor ^= Lidar_Rolling;
                State_Lidar_Trame++;
                break;
            // 6 en default ++
            case 7:
                Lidar_Trame_End_Angle =  (Lidar_Rolling >> 1) / 64.0;
                if ((Lidar_Trame_Start_Angle != Lidar_Trame_End_Angle) && (Lidar_Trame_Sample_Qty > 1)) {
                    if (Lidar_Trame_End_Angle < Lidar_Trame_Start_Angle) {
                        Lidar_Trame_End_Angle += 360;
                    }
                    Lidar_Point_Reso = (Lidar_Trame_End_Angle - Lidar_Trame_Start_Angle) / ((float)(Lidar_Trame_Sample_Qty - 1));
                } else {
                    Lidar_Point_Reso = 0.0;
                }
                Lidar_Trame_Xor ^= Lidar_Rolling;
                State_Lidar_Trame++;
                break;
            // 8 en default ++
            case 9:
                Lidar_Trame_Check_Code = Lidar_Rolling;
                Lidar_Trame_Xor ^= Lidar_Rolling;  // come ça, si résulat final = 0, ça veut dire OK !
                State_Lidar_Trame++;
                break;
            default :
                if (State_Lidar_Trame & 1) {    // seuls les etats impairs sont à travailler
                    // on recoit une donnee
                    Lidar_Trame_Xor ^= Lidar_Rolling;
                    if (Lidar_Rolling) {    // on ne prend jamais les points nuls = pb
                        float This_Point_Anglef = Lidar_Trame_Start_Angle + Lidar_Trame_Nb_Point*Lidar_Point_Reso;
                        float This_Point_Dist = Lidar_Rolling / 4.0;
                        This_Point_Anglef += atan(21.8*(155.3-This_Point_Dist)/(155.3*This_Point_Dist)) * 180.0 / 3.14159;
                        u16 This_Point_Angle = This_Point_Anglef;
                        This_Point_Angle = This_Point_Angle % 360;
                        // new = (15*old + point) / 16
                        // pour faire une moyenne sur tous les points
                        //All_Lidar_Points[This_Point_Angle] += Lidar_Rolling;
                        //All_Lidar_Points_Count[This_Point_Angle] ++;
                        // pour ne garder que le plus proche
                        if (All_Lidar_Points_Count[This_Point_Angle]) {
                            All_Lidar_Points[This_Point_Angle] = Min_Ternaire(All_Lidar_Points[This_Point_Angle], Lidar_Rolling);
                        } else {
                            All_Lidar_Points[This_Point_Angle] = Lidar_Rolling;
                            All_Lidar_Points_Count[This_Point_Angle] = 1;
                        }
                        Lidar_Nb_Good_Points ++;
                    }
                    Lidar_Nb_Points ++;
                    Lidar_Trame_Nb_Point ++;
                    if (((State_Lidar_Trame - 8) >> 1) == Lidar_Trame_Sample_Qty) {
                        //printf("\r\nGot a trame Len %d, type %d\r\n", Lidar_Trame_Sample_Qty, (int)(Lidar_Trame_Package_Type));
                        
                        if (Lidar_Trame_Package_Type) {
                            printf("%6d, %4d, %4d\n", Timer_ms1, Lidar_Nb_Points, Lidar_Nb_Good_Points);
                            
                            Lidar_Nb_Points = 0;
                            Lidar_Nb_Good_Points = 0;
                            /*if (!i_print_Lidar_Point) {
                                printf("Start;");
                                i_print_Lidar_Point = 1;
                            }*/
                        }
                        if (Lidar_Trame_Xor) {
                            printf("Error Xor %.3f\n", Lidar_Trame_Start_Angle);
                        }
                        State_Lidar_Trame = 0;
                        
                    } else {
                        State_Lidar_Trame ++;
                    }
                } else {
                    State_Lidar_Trame ++;
                }
                break;
        }
    }
    /*
    if (i_print_Lidar_Point && Lidar_Uart_RX_Is_Empty()) {
        if (Is_Std_Out_Empty()) {
            u16 i = i_print_Lidar_Point-1;
            u32 Sum_of_Dist = All_Lidar_Points[i];
            u16 Count = All_Lidar_Points_Count[i];
            All_Lidar_Points[i] = 0;
            All_Lidar_Points_Count[i] = 0;
            if (Count) {
                Point_To_Print = Sum_of_Dist / (4*Count);
            }
            printf("%4ld;", Point_To_Print);
            if (Point_To_Print < 50) {
                printf("\nerror?\n");
            }
            i_print_Lidar_Point ++;
            if (i_print_Lidar_Point == 181) {
                i_print_Lidar_Point = 0;
                printf("\r\n");
            }
        }
    }*/
}


u8 Moteur_Lidar_Func (void)
{
    EN_MOT_X4_TRIS = 0;
    EN_MOT_X4_PIN = !EN_MOT_X4_PIN;
    return 0;
}

u8 Lidar_Start_Func(void)
{
    u8 Buff [] = {0xA5, 0x60};
    Send_Buff_Uart_Lidar(Buff, 2);
    
    u16 i;
    for (i = 0; i < 180; i++) {
        All_Lidar_Points[i] = 0;
    }
    
    return 0;
}

u8 Lidar_Stop_Func(void)
{
    u8 Buff [] = {0xA5, 0x65};
    Send_Buff_Uart_Lidar(Buff, 2);
    return 0;
}

u8 Lidar_Reboot_Func(void)
{
    u8 Buff [] = {0xA5, 0x80};
    Send_Buff_Uart_Lidar(Buff, 2);
    return 0;
}

#endif