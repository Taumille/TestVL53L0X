#ifndef _USER_H_
#define _USER_H_

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define PIC_DISTANT
//#define PIC_RPI

/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        80000000UL
//#define SYS_FREQ        40000000UL
#define FCY             (SYS_FREQ/2)
#define FOSC            FCY

#define BAUDRATE_UART_CMD	115200
//#define BAUDRATE_UART_CMD	460800
//#define BAUDRATE_UART_CMD	9600
//#define BRGVAL_UART_CMD ((FCY / BAUDRATE_UART_CMD / 16) - 1)
#define BRGVAL_UART_CMD ((FCY / BAUDRATE_UART_CMD / 4) - 1)


typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define Min_Ternaire(a,b) (a<b)?a:b
#define Max_Ternaire(a,b) (a>b)?a:b

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */

// initialize all things
void Init_All(void);




#endif // _USER_H_
