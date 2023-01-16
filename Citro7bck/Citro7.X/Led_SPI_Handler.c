

#include "main.h"

uint16_t Led_Bit_Tab[128];
volatile uint8_t Led_Bit_Tab_DONE = 0;
uint8_t Led_Bit_Tab_TODO = 0;
uint8_t Led_bit_Tab_Failed = 0;

uint8_t Led_Octet_Tab[NB_OCTECT_PER_LED*MAX_NB_LED];
uint8_t *Current_Led_Tab;
uint16_t Current_Led_Tab_TODO = 0;
uint16_t Current_Led_Tab_DONE = 0;
uint8_t Current_Led_Bit_Conf = 3;	// 3 ou 4

Rubanc_Led Rubanc_Led_Tab[MAX_NB_LED_RUBANCS];

uint8_t Rubanc_Led_Tab_TODO = 0;
uint8_t Must_Start_A_Led_Rubanc = 0;

uint16_t Last_Timer_Start_Rubanc = 0;

uint8_t Led_SPI_Handler_State = 0;
uint8_t Low_Led_Handler_State = 0;

// il faut faire 3 bit par 3 bit, (enfin, 3 pour 1)
// remplir petit à petit le tableau
// 
// ou voir pour 4

uint8_t Led_PB = 0;
uint16_t Led_Sended = 0;
uint16_t Last_Led_Sended = 0;

uint16_t Nb_Led_Transferts = 0;
uint16_t Last_Nb_Led_Transferts = 0;

uint16_t Bit_Sended = 0;
uint16_t Last_Bit_Sended = 0;

void LED_SPI_Handler_Init(void)
{
	
	// init SPI
    SPI2CON1bits.SMP = 1;       // 1 = sample a la fin du bit, 0 = au milieu (STD)
    SPI2CON1bits.MODE16 = 1;    // 16 bits
    SPI2CON1bits.MSTEN = 1;     // Master
    
    
    // ne supporte pas que les 2 soient à 1/1 (3 et 7)
    // pour FCY = 40MHz
    SPI2CON1bits.SPRE = 5;      // de 0 à 7, 0 = 1/8, 1 = 1/7 ... 5 = 1/3, 6 = 1/2, 7 = 1/1
    SPI2CON1bits.PPRE = 2;      // de 0 à 3, 0 = 1/64, 1 = 1/16, 2 = 1/4, 3 = 1/1
	// vu que FCY est à 40MHz
	// en divisant par 12, ça donne 3.33MHz, soit 0.3µs de période de bit, idéal pourr les Leds WSB
    
    // pour FCY = 20MHz
    //SPI2CON1bits.SPRE = 2;      // de 0 à 7, 0 = 1/8, 1 = 1/7 ... 5 = 1/3, 6 = 1/2, 7 = 1/1
    //SPI2CON1bits.PPRE = 3;      // de 0 à 3, 0 = 1/64, 1 = 1/16, 2 = 1/4, 3 = 1/1
    // div by 6
    
    SPI2STATbits.SPIEN = 1;
    IPC8bits.SPI2IP = 6;
    IFS2bits.SPI2IF = 1;
    IEC2bits.SPI2IE = 0;
    
    
    Rubanc_Led_Tab[0].Bit_per_Bit = 4;
    Rubanc_Led_Tab[0].Config = CONF_LED_SPI;
    Rubanc_Led_Tab[0].Led_Tab = &Led_Octet_Tab[0];
    Rubanc_Led_Tab[0].Nb_Led = 1;
    Rubanc_Led_Tab[0].O_Per_Led = 3;
    Rubanc_Led_Tab[0].Speed = 4;
    
    
    uint8_t Tab_Test[3] = {0,0,0};     // Green, Red, Blue
    Rubanc_Fill_Uniform(0, &Tab_Test[0]);
    
}

uint32_t Last_Color_Timer = 0;

void LED_SPI_Handler_Loop (void)
{
/*    if ((Timer_ms1 - Last_Color_Timer) > 100) {
        Last_Color_Timer += 100;
        uint16_t Color_Alacon = (Last_Color_Timer/100)%100 ;
        //uint8_t Tab_Test[3] = {Color_Alacon,Color_Alacon,Color_Alacon};
        
        uint8_t Tab_Test[3] = {0,0,0};
        if (Color_Alacon & 0x1)
            Tab_Test[0] = 30;
        if (Color_Alacon & 0x2)
            Tab_Test[1] = 30;
        if (Color_Alacon & 0x4)
            Tab_Test[2] = 30;
        
        //Rubanc_Fill_Uniform(0, &Tab_Test[0]);
        //Rubanc_Fill_Uniform(1, &Tab_Test[0]);
        Rubanc_Add_End(0, &Tab_Test[0]);
        //Rubanc_Add_Start(1, &Tab_Test[0]);
        
        Rubanc_Set_Led(1, Color_Alacon %15, &Tab_Test[0]);
    }*/
    
	if (!Led_SPI_Handler_State) {
        
		if (Must_Start_A_Led_Rubanc) {
			Rubanc_Led_Tab_TODO = (Rubanc_Led_Tab_TODO + 1) % MAX_NB_LED_RUBANCS;
			if (Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].Nb_Led != 0) {
				Must_Start_A_Led_Rubanc = 0;
                
				Led_Bit_Tab_DONE = 0;
				Led_Bit_Tab_TODO = 0;
				
				Current_Led_Tab = Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].Led_Tab;
				Current_Led_Tab_DONE = 0;
				Current_Led_Tab_TODO = Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].O_Per_Led * Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].Nb_Led;
				
				Current_Led_Bit_Conf = Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].Bit_per_Bit;
				SPI2CON1bits.SPRE = Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].Speed;
				
				Led_SPI_Set_Config(Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].Config, 1);
				
				Low_Led_Handler_State = 1;
				Led_SPI_Handler_State = 1;
				
				IFS2bits.SPI2IF = 1;
			}
		} else if ((Timer_ms1 - Last_Timer_Start_Rubanc) > 10) {
            Last_Timer_Start_Rubanc = Timer_ms1;
            Must_Start_A_Led_Rubanc = 1;
        }
	} else {
		if (!Low_Led_Handler_State && !IEC2bits.SPI2IE) {
			Led_SPI_Set_Config(Rubanc_Led_Tab[Rubanc_Led_Tab_TODO].Config, 0);
			Led_SPI_Handler_State = 0;
            Last_Timer_Start_Rubanc = Timer_ms1;
		}
	}
}

void Led_SPI_Low_Handler_Loop(void)
{
	if (Low_Led_Handler_State) {
		uint8_t O_To_Send = 0;
		uint8_t Bit_Count = 0;
		uint8_t Decal_Count = 0;
		uint32_t Shifter = 0;
        
		
		while (		(Current_Led_Tab_DONE < Current_Led_Tab_TODO) && 		// tant qu'on a pas tout envoyé
					(((Led_Bit_Tab_TODO - Led_Bit_Tab_DONE) & 0x7F) < 100)    ) {		// ou bcp préparé
			do {
				if (!Bit_Count) {
					O_To_Send = Current_Led_Tab[Current_Led_Tab_DONE];
					Current_Led_Tab_DONE ++;
					Bit_Count = 8;
				}
				if (Current_Led_Bit_Conf == 3) {
					Shifter = Shifter << 3;
					if (O_To_Send & 0x80) {
						Shifter |= 0b110;
					} else {
						Shifter |= 0b100;
					}
					Decal_Count += 3;
				} else {
					Shifter = Shifter << 4;
					if (O_To_Send & 0x80) {
						Shifter |= 0b1100;
					} else {
						Shifter |= 0b1000;
					}
					Decal_Count += 4;
				}
				O_To_Send = O_To_Send << 1;
				Bit_Count --;
				
				if (Decal_Count >= 16) {
					Decal_Count -= 16;
					Led_Bit_Tab[Led_Bit_Tab_TODO] = Shifter >> (Decal_Count);
					Led_Bit_Tab_TODO = (Led_Bit_Tab_TODO + 1) & 0x7F;
				}
			} while ((Decal_Count != 0) || (Bit_Count != 0));	// on reste là dedans tant qu'on est pas bien réalignés
		}
		
        IEC2bits.SPI2IE = 1;
        
        
		if (Current_Led_Tab_DONE >= Current_Led_Tab_TODO) {
			Low_Led_Handler_State = 0;
		}
	}
}

void Led_SPI_Set_Config (uint8_t Config, uint8_t En)
{
    switch (Config) {
        case CONF_LED_SPI:
            if (En) {
                RUBANC_LED_PIN_REG   = _RPOUT_SDO2;
                RUBANC_LED_TRIS      = 0;
            } else {
                RUBANC_LED_PIN_REG   = 0;
            }
            break;
    }
}


void __attribute__((interrupt, auto_psv)) _SPI2Interrupt(void)
{
    uint16_t poubelle = SPI2BUF;
    if (!SPI2STATbits.SPITBF) {
		if (Led_Bit_Tab_DONE == Led_Bit_Tab_TODO) {
			IEC2bits.SPI2IE = 0;
		} else {
            IFS2bits.SPI2IF = 0;        // clear flag
			SPI2BUF = Led_Bit_Tab[Led_Bit_Tab_DONE];
			Led_Bit_Tab_DONE = (Led_Bit_Tab_DONE + 1) & 0x7F; //simple limite à 127
		}
    }
}


void Rubanc_Fill_Uniform(uint8_t Id_Rubanc, uint8_t Tab_Color[])
{
	if (Id_Rubanc < MAX_NB_LED_RUBANCS) {
		uint16_t Id_O = 0;
		uint8_t i;
		while (Id_O < (Rubanc_Led_Tab[Id_Rubanc].Nb_Led * Rubanc_Led_Tab[Id_Rubanc].O_Per_Led)) {
			for (i = 0; i < Rubanc_Led_Tab[Id_Rubanc].O_Per_Led; i++) {
				Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O] = Tab_Color[i];
				Id_O ++;
			}
		}
	}
}

void Rubanc_Add_End(uint8_t Id_Rubanc, uint8_t Tab_Color[])
{
	if (Id_Rubanc < MAX_NB_LED_RUBANCS) {
		uint16_t Id_O;
		uint8_t i;
		Id_O = 0;
		while (Id_O < ((Rubanc_Led_Tab[Id_Rubanc].Nb_Led - 1) * Rubanc_Led_Tab[Id_Rubanc].O_Per_Led)) {
			Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O] = Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O + Rubanc_Led_Tab[Id_Rubanc].O_Per_Led];
			Id_O ++;
		}
        
        Id_O = (Rubanc_Led_Tab[Id_Rubanc].Nb_Led - 1) * Rubanc_Led_Tab[Id_Rubanc].O_Per_Led;
		for (i = 0; i < Rubanc_Led_Tab[Id_Rubanc].O_Per_Led; i++) {
			Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O] = Tab_Color[i];
			Id_O ++;
		}
	}
}

void Rubanc_Add_Start(uint8_t Id_Rubanc, uint8_t Tab_Color[])
{
	if (Id_Rubanc < MAX_NB_LED_RUBANCS) {
		uint16_t Id_O;
		uint8_t i;
		Id_O = Rubanc_Led_Tab[Id_Rubanc].Nb_Led * Rubanc_Led_Tab[Id_Rubanc].O_Per_Led - 1;
		while (Id_O >= Rubanc_Led_Tab[Id_Rubanc].O_Per_Led) {
			Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O] = Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O - Rubanc_Led_Tab[Id_Rubanc].O_Per_Led];
			Id_O --;
		}
        Id_O = 0;
		for (i = 0; i < Rubanc_Led_Tab[Id_Rubanc].O_Per_Led; i++) {
			Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O] = Tab_Color[i];
			Id_O ++;
		}
	}
}

void Rubanc_Set_Led(uint8_t Id_Rubanc, uint16_t Id_Led, uint8_t Tab_Color[])
{
    if (Id_Rubanc < MAX_NB_LED_RUBANCS) {
        if (Id_Led < Rubanc_Led_Tab[Id_Rubanc].Nb_Led) {
            uint16_t Id_O;
            uint8_t i;
            Id_O = Id_Led * Rubanc_Led_Tab[Id_Rubanc].O_Per_Led;
            for (i = 0; i < Rubanc_Led_Tab[Id_Rubanc].O_Per_Led; i++) {
                Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O] = Tab_Color[i];
                Id_O ++;
            }
        }
    }
}

void Rubanc_Get_Led(uint8_t Id_Rubanc, uint16_t Id_Led, uint8_t Tab_Color[])
{
    if (Id_Rubanc < MAX_NB_LED_RUBANCS) {
        if (Id_Led < Rubanc_Led_Tab[Id_Rubanc].Nb_Led) {
            uint16_t Id_O;
            uint8_t i;
            Id_O = Id_Led * Rubanc_Led_Tab[Id_Rubanc].O_Per_Led;
            for (i = 0; i < Rubanc_Led_Tab[Id_Rubanc].O_Per_Led; i++) {
                Tab_Color[i] = Rubanc_Led_Tab[Id_Rubanc].Led_Tab[Id_O];
                Id_O ++;
            }
        }
    }
}


uint8_t Rubanc_Fill_Uniform_Func (void)
{
	uint8_t Tab_Color [4];
	uint8_t i_Color = 0;
	
	uint8_t Id_Rubanc;
	uint32_t val32;
	
	if (Get_Param_u32(&val32))
        return PARAM_ERROR_CODE;
	if (val32 >= MAX_NB_LED_RUBANCS)
		return PARAM_OUT_OF_RANGE_ERROR_CODE;
	Id_Rubanc = val32;
	
	for (i_Color = 0; i_Color < Rubanc_Led_Tab[Id_Rubanc].O_Per_Led; i_Color++) {
		if (Get_Param_u32(&val32))
			return PARAM_ERROR_CODE;
		
		Tab_Color[i_Color] = val32;
	}
	
	Rubanc_Fill_Uniform(Id_Rubanc, &Tab_Color[0]);
	
	return 0;
}


uint8_t Rubanc_Set_Func (void)
{
	
	uint8_t Id_Rubanc;
	uint16_t Start_Pos;
	uint16_t Nb_Led;
	uint8_t O_Per_Led;
	uint8_t Speed;
	uint8_t Bit_per_Bit;
	uint8_t Config;
	uint32_t val32;
	
	
	if (Get_Param_u32(&val32))
        return PARAM_ERROR_CODE;
	if (val32 >= MAX_NB_LED_RUBANCS)
		return PARAM_OUT_OF_RANGE_ERROR_CODE;
	Id_Rubanc = val32;
	
	if (Get_Param_u32(&val32))
        return PARAM_ERROR_CODE;
	Nb_Led = val32;
	
	if (Nb_Led != 0) {
		if (Get_Param_u32(&val32))
			return PARAM_ERROR_CODE;
		Start_Pos = val32;
		
		
		if (Get_Param_u32(&val32))
			return PARAM_ERROR_CODE;
		Config = val32;
		
		if (Get_Param_u32(&val32))
			return PARAM_ERROR_CODE;
		Speed = val32;
		
		if (Get_Param_u32(&val32))
			return PARAM_ERROR_CODE;
		Bit_per_Bit = val32;
		
		if (Get_Param_u32(&val32))
			return PARAM_ERROR_CODE;
		O_Per_Led = val32;
	}
	
	Rubanc_Led_Tab[Id_Rubanc].Config = Config;
	Rubanc_Led_Tab[Id_Rubanc].O_Per_Led = O_Per_Led;
	Rubanc_Led_Tab[Id_Rubanc].Speed = Speed;
	Rubanc_Led_Tab[Id_Rubanc].Bit_per_Bit = Bit_per_Bit;
	Rubanc_Led_Tab[Id_Rubanc].Led_Tab = &Led_Octet_Tab[Start_Pos];
	Rubanc_Led_Tab[Id_Rubanc].Nb_Led = Nb_Led;
	
	
	
	return 0;
}

uint8_t Led_RGB_Set_Func (void)
{
    int nb_params = 0;
    uint32_t Params[4];
    while ((nb_params < 4) && !Get_Param_u32(&Params[nb_params])) {
        nb_params ++;
    }
    if (nb_params < 3) {
        return PARAM_ERROR_CODE;
    } else if (nb_params == 3) {
        if (Params[0] > 255)    return PARAM_OUT_OF_RANGE_ERROR_CODE;
        if (Params[1] > 255)    return PARAM_OUT_OF_RANGE_ERROR_CODE;
        if (Params[2] > 255)    return PARAM_OUT_OF_RANGE_ERROR_CODE;
        uint8_t Tab_Color[3];       // params en RGB, leds en GRB
        Tab_Color[0] = Params[1]*0.1;
        Tab_Color[1] = Params[0]*0.1;
        Tab_Color[2] = Params[2]*0.1;
        Rubanc_Fill_Uniform(0, &Tab_Color[0]);
    } else {
        if (Params[0] > 5)      return PARAM_OUT_OF_RANGE_ERROR_CODE;
        if (!Params[0])         return PARAM_OUT_OF_RANGE_ERROR_CODE;
        if (Params[1] > 255)    return PARAM_OUT_OF_RANGE_ERROR_CODE;
        if (Params[2] > 255)    return PARAM_OUT_OF_RANGE_ERROR_CODE;
        if (Params[3] > 255)    return PARAM_OUT_OF_RANGE_ERROR_CODE;
        uint8_t Id_Led = Params[0] - 1;
        uint8_t Tab_Color[3];   // params en RGB, leds en GRB
        Tab_Color[0] = Params[2]*0.1;
        Tab_Color[1] = Params[1]*0.1;
        Tab_Color[2] = Params[3]*0.1;
        Rubanc_Set_Led(0, Id_Led, &Tab_Color[0]);
    }    
    
    return 0;
}



void Set_Random_Color(uint8_t *Color_Out, int Mode)
{
    Color_Out[0] = 0;   // GREEN
    Color_Out[1] = 0;   // RED
    Color_Out[2] = 0;   // BLUE
    
    if (Mode == 0) {    // pour accenter les couleurs
        Color_Out[0] = rand();
        Color_Out[1] = rand();
        Color_Out[2] = rand();
        if ((Color_Out[0] <= Color_Out[1]) && (Color_Out[1] <= Color_Out[2])) {             //  0   1   2
            Color_Out[0] *= 0.3;
            Color_Out[1] *= 0.7;
        } else if ((Color_Out[0] <= Color_Out[2]) && (Color_Out[2] <= Color_Out[1])) {      //  0   2   1
            Color_Out[0] *= 0.3;
            Color_Out[2] *= 0.7;
        } else if ((Color_Out[1] <= Color_Out[0]) && (Color_Out[0] <= Color_Out[2])) {      //  1    0   2
            Color_Out[1] *= 0.3;
            Color_Out[0] *= 0.7;
        } else if ((Color_Out[1] <= Color_Out[2]) && (Color_Out[2] <= Color_Out[0])) {      //  1    2   0
            Color_Out[1] *= 0.3;
            Color_Out[2] *= 0.7;
        } else if ((Color_Out[2] <= Color_Out[0]) && (Color_Out[0] <= Color_Out[1])) {      //  2    0   1
            Color_Out[2] *= 0.3;
            Color_Out[0] *= 0.7;
        } else { //if ((Breath_Color[1] <= Breath_Color[2]) && (Breath_Color[2] <= Breath_Color[0])) {  //  2    1   0
            Color_Out[2] *= 0.3;
            Color_Out[1] *= 0.7;
        }
    } else if (Mode == 1) {     // mode couleur de noel
        int i = rand()%12;
        if (i < 3) {
            Color_Out[0] = 150; // Green
        } else if (i < 6) {
            Color_Out[1] = 150; // Red
        } else if (i < 8) {
            Color_Out[2] = 150; // Blue (moins frequent)
        } else if (i < 10) {
            Color_Out[0] = 150; // blanc
            Color_Out[1] = 150; // blanc
            Color_Out[2] = 150; // blanc
        } else if (i < 12) {
            Color_Out[0] = 150; // jaune orangé
            Color_Out[1] = 120; // 
            Color_Out[2] = 10; // 
        } else {    // reste éteint
            
        }
        
    } else { //if (Mode == 2) {     // autre mode de génération
        uint8_t val8 = 0;
        while (!(val8 & 0x7)) {
            val8 = rand();
            Color_Out[0] = 100* (val8 & 0x1);
            Color_Out[1] = 50 * (val8 & 0x2);
            Color_Out[2] = 25 * (val8 & 0x4);
        }
    }
}

    
uint32_t Last_Timer_Rubanc_Mode = 0;
uint8_t Rubanc_Mode_Param = 0;

uint32_t Last_Timer_Rubanc_Test = 0;
uint16_t Rubanc_Test_State = 0;


uint8_t Static_Color[3] = {0};

uint8_t Rubanc_Random_Rub = 0;

uint8_t Rainbow_Color_Tab[40][3];

uint8_t Rotary_State = 0;

uint8_t Laisse_Count = 0;
uint8_t Laisse_State = 0;

#define MODE_RANDOM_POP        1

uint8_t Mode_Rubanc = MODE_RANDOM_POP;



void Rubanc_Led_Test_Loop (void)
{
    if (Mode_Rubanc == MODE_RANDOM_POP) {
        if ((Timer_ms1 - Last_Timer_Rubanc_Test) > 1000) {
            Last_Timer_Rubanc_Test = Timer_ms1;
            uint8_t Pop_Rubanc = 0;
            uint8_t Pop_Led = rand() % Rubanc_Led_Tab[Pop_Rubanc].Nb_Led;
            uint8_t Pop_Color[3];
            Set_Random_Color(&Pop_Color[0], 1);
                
            Rubanc_Set_Led(Pop_Rubanc, Pop_Led, &Pop_Color[0]);        
        }
    }
}