

#ifndef __GESTION_IO_H
#define __GESTION_IO_H



// ***************************************************
// ******************* IOS Simples *******************
// ***************************************************

#define LED1         _LATC1
#define LED1_TRIS    _TRISC1

#define LED2         _RC2
#define LED2_TRIS    _TRISC2



// RB4
#define RUBANC_LED_TRIS _TRISB7
#define RUBANC_LED_PIN_REG _RP7R

#define EN_VMOT_PIN_TRIS  _TRISB1
#define EN_VMOT_PIN       _RB1

#define PIC_DAC_PIN _RC6
#define PIC_DAC_TRIS _TRISC6

// ***************************************************
// ******************** H_BRIDGE  ********************
// ***************************************************
#ifdef MOTOR_HANDLER
#define DRV1_PIN _RB14
#define DRV2_PIN _RB15
#define DRV1_TRIS _TRISB14
#define DRV2_TRIS _TRISB15

#define DRV_MODE_PIN _RA1
#define DRV_MODE_TRIS _TRISA1
#define DRV_NSLEEP _RB12
#define DRV_NSLEEP_TRIS _TRISB12

#endif

#ifdef SERVO_HANDLER
#define SERVO1_TRIS _TRISC7
#define SERVO1_PIN  _LATC7
#define SERVO2_TRIS _TRISC8
#define SERVO2_PIN  _LATC8

#endif

// ***************************************************
// ****************** FREESCALE_CAM ******************
// ***************************************************
#ifdef CAM_HANDLER
#define CLK_CAM _RB4   // chen_wifi
#define TRIG_CAM _RC8  //gpio2
#define CLK_CAM_TRIS _TRISB4
#define TRIG_CAM_TRIS _TRISC8

// analog sur RB3/ AN5

#endif


// ***************************************************
// ********************** UART  **********************
// ***************************************************
// USB : RX = RC4 (RP20), TX = RC3 (RP19)

// mode USB
#define UART_RX_PIN_NB 12
#define UART_TX_PIN_REG _RP13R


// ***************************************************
// *********************** I2C ***********************
// ***************************************************

#define I2C_SCL_PIN     _RB8
#define I2C_SCL_TRIS    _TRISB8
#define I2C_SDA_PIN     _RB9
#define I2C_SDA_TRIS    _TRISB9


// ***************************************************
// *************** FLASH SUR CARTE COM ***************
// ***************************************************

#ifdef FLASH_HANDLER

#define CON1_SPI_MISO_PIN_NB    11
#define CON1_SPI_MOSI_PIN_REG   _RP14R
#define CON1_SPI_SCLK_PIN_REG   _RP15R
#define CON1_SPI_MISO_TRIS      _TRISB11
#define CON1_SPI_MOSI_TRIS      _TRISB14
#define CON1_SPI_SCLK_TRIS      _TRISB15

#define FLASH_CS _LATA7
#define FLASH_CS_TRIS _TRISA7



#endif





// ***************************************************
// ******************** LIDAR X4  ********************
// ***************************************************
#ifdef ENABLE_LIDAR
#define EN_MOT_X4_PIN     _LATA8
#define EN_MOT_X4_TRIS    _TRISA8

#define UART_LIDAR_RX_PIN_NB 10
#define UART_LIDAR_TX_PIN_REG _RP25R
#endif

void Gestion_IO_Init(void);
void Gestion_IO_Loop(void);

#endif

