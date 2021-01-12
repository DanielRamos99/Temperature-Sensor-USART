/* 
 * File:   USART_libreria.c
 * Author: Daniel Ramos
 */

#include <xc.h>
#include "configuration.h"
#include "USART_library.h"

void USART_Init(long BAUD){
    //Pins configuration
    TRISCbits.RC6 = 0;      //RC6 = Tx -> Output
    TRISCbits.RC7 = 1;      //RC7 = Rx -> Input
    
    //Baud
    SPBRG = (unsigned char)(((_XTAL_FREQ/BAUD)/64)-1);
    
    //Configuration
    TXSTAbits.BRGH = 0;     //Low Speed
    TXSTAbits.SYNC = 0;     //Asinchronous
    RCSTAbits.SPEN = 1;     //Tx and Rx enable
    
    //Transmmision
    TXSTAbits.TX9 = 0;      //8 bits
    TXSTAbits.TXEN = 1;     //Transmmision enable
    
    //Reception
    RCSTAbits.RC9 = 0;      //8 bits
    RCSTAbits.CREN = 1;     //Reception enable
}

void USART_Tx(char data){
    TXREG = data;
}

char USART_Rx(){
    return RCREG; 
}
