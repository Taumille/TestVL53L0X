
#ifndef __LED_SPI_HANDLER_H
#define __LED_SPI_HANDLER_H


#define MAX_NB_LED 30
#define NB_OCTECT_PER_LED 4

#define MAX_NB_LED_RUBANCS 5

#define CONF_LED_SPI		1


typedef struct {
    uint8_t Config;
	uint8_t O_Per_Led;
	uint8_t Speed;
	uint8_t Bit_per_Bit;
    uint8_t *Led_Tab;
    uint16_t Nb_Led;
} Rubanc_Led;


void LED_SPI_Handler_Init (void);

void LED_SPI_Handler_Loop (void);
void Led_SPI_Low_Handler_Loop (void);

void Led_SPI_Set_Config (uint8_t Config, uint8_t En);


void Rubanc_Fill_Uniform(uint8_t Id_Rubanc, uint8_t Tab_Color[]);
void Rubanc_Add_End(uint8_t Id_Rubanc, uint8_t Tab_Color[]);
void Rubanc_Add_Start(uint8_t Id_Rubanc, uint8_t Tab_Color[]);
void Rubanc_Set_Led(uint8_t Id_Rubanc, uint16_t Id_Led, uint8_t Tab_Color[]);
void Rubanc_Get_Led(uint8_t Id_Rubanc, uint16_t Id_Led, uint8_t Tab_Color[]);

uint8_t Rubanc_Fill_Uniform_Func (void);
uint8_t Rubanc_Set_Func (void);
uint8_t Led_RGB_Set_Func (void);

void Set_Random_Color(uint8_t *Color_Out, int Mode);
void Rubanc_Led_Test_Loop (void);

#endif


