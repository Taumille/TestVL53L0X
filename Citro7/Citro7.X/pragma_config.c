#include "main.h"
#include <xc.h>

#pragma config FNOSC = FRC               // debute sans la PLL, sera rajout?e durant le code
#pragma config IESO = OFF               // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)

// Select clock.
// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Source (Primary Oscillator Disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
//#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)

// Watchdog Timer.
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// Select debug channel.
// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)


// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)


