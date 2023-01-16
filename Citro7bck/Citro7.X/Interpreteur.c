    


#include "main.h"


char Current_Cmd[MAX_CMD_LENGTH + 1];
u16 i_Current_Cmd = 0;
u16 i_Lecture_Current_Cmd = 0;

u16 Between_Quotes = 0;



const Command Command_List[] = {
/*
    { "INIT", INIT_Cmd},


    { "F", SPI_Flash_Test_Func},
    
    { "1", SPI_EIO1_Test_Func},
    { "2", SPI_EIO2_Test_Func},
    //{"1", Test_Led1_Func},
    
    
    { "EIOSETUP", Setup_ExpIO_Func},
    { "EIOGET", Get_ExpIO_Data_Func},
    { "EIOSET", Set_ExpIO_Data_Func},
    { "EIOSETPIN", Set_ExpIO_Pin_Func},
    { "EIODIR", Set_ExpIO_Dir_Func},
	
	
	
    
    */
    
    /*
    
    
    
    { "GETTEMP", Get_Temp_Func},
    { "SETTEMP", Set_Temp_Consigne_Func},
    { "TEMPBASE", Set_Temp_Log_Time},*/
    
    
	

#ifdef PIC_RPI
    { "NETSLAVE", Master_En_Dis_Com_Slave},
#endif
    /*/
    
    { "INTERSETUP", Setup_Inter_Func},
    { "INTERAS", Inter_Auto_Send_Func},
	
    { "LUMSETUP", Setup_Lum_Func},
    { "LUM", Lum_Val_Func},
    
	
	
    
    { "RUBSET", Rubanc_Set_Func},
    { "RUBFILL", Rubanc_Fill_Uniform_Func},
	*/    
	
    { "VIN", Get_Vin_Func},
    { "TIMER", Test_Timer_Func},
    
    #ifdef ENABLE_UART_LIDAR
    { "LIDARMOT", Moteur_Lidar_Func},
    { "LIDARSTART", Lidar_Start_Func},
    { "LIDARSTOP", Lidar_Stop_Func},
    { "LIDARREBOOT", Lidar_Reboot_Func},
    #endif
    #ifdef I2C_MASTER
    { "I2CDISC", I2C_Discover_Cmd},
    { "I2CSTRESS", I2C_Stress_Cmd},
    
   // { "I2CTEST", I2C_Test_Func},
   //{ "I", I2C_Test_Func},
    //{ "I2C", Print_I2C_result},
    { "CMD", Command_I2C_Func},
    #endif

    #ifdef MOTOR_MASTER
    { "MOT", Motor_Master_Func},
    #endif
    #ifdef SERVO_MASTER
    { "SERVO", Servo_Master_Func},
    #endif
    
    #ifdef FLASH_HANDLER
    { "FLST", FlashStatus_Func},
    { "FLRD", FlashRd_Func},
    { "FLBRD", FlashRawSector_Rd_Func},
    { "FLWR", FlashWr_Func},
    { "FLERASE", FlashEr_Func},
    
    { "LOGRST", Flash_LogFile_RESET_Func},
    { "LOGINIT", InitLog_Func},
    { "LOGPRINT", printLog_Func},
    { "LOGADD", Log_Add_Func},
    { "LOGFILL", Log_Fill_Test_Func},
    #endif
    
    
    { "PRINTCMD", Print_All_CMD_Cmd},
    { "HELP", Print_All_CMD_Cmd},
    
    
    

};

const u16 Command_List_Length = sizeof (Command_List) / sizeof (Command_List[0]);

void Interp(char c) {
    // fin de commande = entrée
    //printf("Got %02X\r\n", c);
    if (c != '\n' && c != '\r') {
        if (c == '"') {
            Between_Quotes = !Between_Quotes;
        }
        if (c == 0x08) {    // code pour "effacer" dans tera term ?
            if (i_Current_Cmd) {
                i_Current_Cmd --;   // retour d'un cran en arriere
                if (Current_Cmd[i_Current_Cmd] == '"') {    // si ce cran c'était des guillemets, on enleve
                    Between_Quotes = !Between_Quotes; 
                }
                Current_Cmd[i_Current_Cmd] = '\0';  // on efface le caractere
            }
        } else if (i_Current_Cmd < MAX_CMD_LENGTH) { //si on est toujours dans la commande, on ajoute
            if (!Between_Quotes) {
                Current_Cmd[i_Current_Cmd] = To_UpperCase(c);
            } else {
                Current_Cmd[i_Current_Cmd] = c;
            }
            i_Current_Cmd++;
        } else if (i_Current_Cmd < (MAX_CMD_LENGTH + 1)) { // protection overshoot
            i_Current_Cmd++;
        }
    } else { // on a tappé entrée, il faut trouver quelle fonction executer..
        Between_Quotes = 0;
        if (i_Current_Cmd) {
            if (i_Current_Cmd == (MAX_CMD_LENGTH + 1)) {
                #ifndef WORLD_OF_SILENCE
                    printf("ERROR_Cmd_Length_Overshoot\r\n");
                #endif
            } else {

                Current_Cmd[i_Current_Cmd] = '\0'; // mise d'un fin de chaine à la fin
                // on recherche combien de caracteres fait la commande en elle même (sans les PARAM)
                u16 Len = 0;
                u16 Ind = 0;
                u8 Found = 0;
                while ( (Current_Cmd[Len] >= 'A' && Current_Cmd[Len] <= 'Z') || 
                        (Current_Cmd[Len] >= '0' && Current_Cmd[Len] <= '9')    )
                    Len++;
                if (Len) {
                    Current_Cmd[Len] = '\0';
                    i_Lecture_Current_Cmd = Len + 1;
                    while ((!Found) && (Ind < Command_List_Length)) {
                        if (strcmp(&Current_Cmd[0], Command_List[Ind].Name) == 0) {
                            Found = 1;
                        } else {
                            Ind++;
                        }
                    }
                    if (!Found) {
                        #ifndef WORLD_OF_SILENCE
                            printf("Cmd_Not_Found\r\n");
                        #endif
                    } else {
                        u8 val8 = (*Command_List[Ind].Func)();
                        #ifndef WORLD_OF_SILENCE
                            if (val8) 
                                printf("Cmd_Error %d\r\n", val8);
                        #endif      
                    }
                }
            }
        }
        i_Current_Cmd = 0;
    }
}

char To_UpperCase(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;
    else
        return c;
}



u8 Get_Param_Float(float *retour) {
    float valf = 0;
    float div = 0;
    u8 Is_Neg = 0;
    u8 Result_Is_Error = 1;
    // tant qu'on est sur un caractère, et qu'on a pas trouvé un chiffre
    while ((Current_Cmd[i_Lecture_Current_Cmd] != '\0') && (Current_Cmd[i_Lecture_Current_Cmd] != '-') &&
            !((Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9')))
    {
        i_Lecture_Current_Cmd++;
    }
    
    // if (Current_Cmd[i_Lecture_Current_Cmd] == '\0') // si on est au bout, on renvoie error...
    //    return 1;

    if ((Current_Cmd[i_Lecture_Current_Cmd] == '-')) {
        Is_Neg = 1;
        i_Lecture_Current_Cmd++;
    }
    
    while (((Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9')) || (Current_Cmd[i_Lecture_Current_Cmd] == '.')) {
        if (Current_Cmd[i_Lecture_Current_Cmd] != '.') {
            valf *= 10;
            valf += Current_Cmd[i_Lecture_Current_Cmd] - '0';
            div *= 10;
            Result_Is_Error = 0;
        } else {
            div = 1;
        }
        i_Lecture_Current_Cmd++;
    }
    
    if (!Result_Is_Error) {
        if (div == 0)
            div = 1;

        valf = valf / div;

        if (Is_Neg)
            *retour = - valf;
        else
            *retour = valf;
    }
    return Result_Is_Error;
}

u8 Get_Param_u32(u32 *retour) {
    u32 val = 0;
    //u8 Is_Neg = 0;
    u8 Result_Is_Error = 1;
    
    // tant qu'on est sur un caractère, et qu'on a pas trouvé un chiffre
    
    while ((Current_Cmd[i_Lecture_Current_Cmd] != '\0') && 
            // (Current_Cmd[i_Lecture_Current_Cmd] != '-') &&
            !((Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9')))
    {
        i_Lecture_Current_Cmd++;
    }
    
/*
    if ((Current_Cmd[i_Lecture_Current_Cmd] == '-')) {
        Is_Neg = 1;
        i_Lecture_Current_Cmd++;
    }
 */
    
    while ((Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9')) {
        val *= 10;
        val += Current_Cmd[i_Lecture_Current_Cmd] - '0';
        Result_Is_Error = 0;
        i_Lecture_Current_Cmd++;
    }
    
    if (!Result_Is_Error) {
        /*if (Is_Neg)
            *retour = - val;
        else*/
        
        *retour = val;
    }
    return Result_Is_Error;
}

u8 Get_Param_x32(u32 *retour) {
    u32 val = 0;
    //u8 Is_Neg = 0;
    u8 Result_Is_Error = 1;
    
    // tant qu'on est sur un caractère, et qu'on a pas trouvé un chiffre
    
    while ((Current_Cmd[i_Lecture_Current_Cmd] != '\0') && 
            //(Current_Cmd[i_Lecture_Current_Cmd] != '-') &&
            !((Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9')) &&
            !((Current_Cmd[i_Lecture_Current_Cmd] >= 'A') && (Current_Cmd[i_Lecture_Current_Cmd] <= 'F'))      )
    {
        i_Lecture_Current_Cmd++;
    }
    
/*
    if ((Current_Cmd[i_Lecture_Current_Cmd] == '-')) {
        Is_Neg = 1;
        i_Lecture_Current_Cmd++;
    }
 */
    
    while ( ((Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9')) ||
            ((Current_Cmd[i_Lecture_Current_Cmd] >= 'A') && (Current_Cmd[i_Lecture_Current_Cmd] <= 'F'))     )
    {
        val *= 16;
        if ((Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9'))
            val += Current_Cmd[i_Lecture_Current_Cmd] - '0';
        else if ((Current_Cmd[i_Lecture_Current_Cmd] >= 'A') && (Current_Cmd[i_Lecture_Current_Cmd] <= 'F'))
            val += 10 + Current_Cmd[i_Lecture_Current_Cmd] - 'A';
        
        Result_Is_Error = 0;
        i_Lecture_Current_Cmd++;
    }
    
    if (!Result_Is_Error) {
        /*if (Is_Neg)
            *retour = - val;
        else*/
        
        *retour = val;
    }
    return Result_Is_Error;
}

u8 Get_Param_String(char Dest_Str[], u8 Max_Len)
{
    u8 Len = 0;
    
    u16 i_Start = 0, i_End = 0;
    
    while ((Current_Cmd[i_Lecture_Current_Cmd] != '"') && (Current_Cmd[i_Lecture_Current_Cmd] != '\0')) {
        i_Lecture_Current_Cmd ++;   // recherche du premier "
    }
    if (Current_Cmd[i_Lecture_Current_Cmd] == '"') {
        i_Lecture_Current_Cmd ++;
        i_Start = i_Lecture_Current_Cmd;    // i_Start = 1er après "
    }
    while ((Current_Cmd[i_Lecture_Current_Cmd] != '"') && (Current_Cmd[i_Lecture_Current_Cmd] != '\0')) {
        i_Lecture_Current_Cmd ++;   // recherche du second "
    }
    if (Current_Cmd[i_Lecture_Current_Cmd] == '"') {
        i_End = i_Lecture_Current_Cmd;  // i_End = 2em "
        i_Lecture_Current_Cmd ++;
    }
    if (i_End > i_Start) {  // si on a bien trouvé 2 "
        if ((i_End - i_Start) < (Max_Len - 1)) {    // et que ca rentre dans le truc
            u16 i = i_Start;
            while (i != i_End) {
                Dest_Str[Len] = Current_Cmd[i];
                Len ++;
                i ++;
            }
            Dest_Str[Len] = '\0';
            Len ++;
        }
    }
    return Len;
}

u8 Print_All_CMD_Cmd(void) {
    u16 i;
    for (i = 0; i < Command_List_Length; i++) {
        printf("%s\n", Command_List[i].Name);
        u8 j;
        for (j = 0; j < 10; j++) {
            Delay_ms(1);
            Std_Comm_Loop();    // moche, mais permet de faire sortir les printf
        }
    }
    return 0;
}
