


#include <xc.h>
#include "main.h"

volatile uint32_t Timer_ms1 = 0;        // timer en ms depuis l'allumage, ne jamais remettre à 0



void Timers_Init(void) {
    // activation/config du Timer3
    T3CONbits.TCS = 0;      // select internal clock (Fosc/2))
    T3CONbits.TCKPS = 2;    // div by 64
    PR3 = 625;              // periode pour 1ms
    T3CONbits.TON = 1;      // enable
    
    // config de l'interruption
    IPC2bits.T3IP = 7;  // interruption ultra haute priorité
    IEC0bits.T3IE = 1;  // enable interruption
    
    //IPC2bits.T3IP = 7

    // on va utiliser les interruptions SPI2 (normal et erreurs)
    // pour les timers avec moins de priorité...
    IFS2bits.SPI2EIF = 0;
    IFS2bits.SPI2IF = 0;
    IEC2bits.SPI2EIE = 1;
    IEC2bits.SPI2IE = 1;

    IPC8bits.SPI2IP = 2; // normal basse prio
    IPC8bits.SPI2EIP = 4; // Erreur "haute" prio, pour l'asserv




}



//volatile unsigned int Maxtime_Seq_AX12 = 0;
//volatile unsigned int Loc_Maxtime = 0;
//
//unsigned int Get_Maxtime_Seq_AX12(void)
//{   return Maxtime_Seq_AX12;    }
//
//void Set_Maxtime_Seq_AX12(unsigned int val)
//{   Maxtime_Seq_AX12 = val;    }
//
//void Set_Maxtime(unsigned int val)
//{    Loc_Maxtime = val; }
//
//char Get_Maxtime(void)
//{
//    if (Loc_Maxtime)
//        return 1;
//    else
//        return 0;
//}

void Delay_ms(uint32_t Nb_ms) {
    uint32_t Objectif = Timer_ms1 + Nb_ms;
    while (Timer_ms1 <= Objectif);
}


// every ms  super haute priorité

void __attribute__((interrupt, auto_psv)) _T3Interrupt(void) {
    Timer_ms1++;
    
    IFS2bits.SPI2IF = 1; // déclenche l'IT ms pas prioritaire
    
    IFS0bits.T3IF = 0; // Flag de ce Timer à 0;
}

// toute les ms, pas prioritaire

void __attribute__((interrupt, auto_psv)) _SPI2Interrupt(void) {
    //static uint8_t count_Evit = 5;
    
    //if (Match_Fini)
    //    motion_free();


    
    

   /* count_Evit--;
    if (!count_Evit) {
        Gestion_Evitement_Every_few_ms();
        count_Evit = 5;
    }*/


    IFS2bits.SPI2IF = 0; // clear le flag d'ici
}

