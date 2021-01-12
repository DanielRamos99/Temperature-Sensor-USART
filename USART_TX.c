/*
 * File:   USART_TX.c
 * Author: Daniel Ramos
 */


#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "configuration.h"
#include "LCD_library.h"
#include "ADC_library.h"
#include "USART_library.h"


//ADC parameters
/*
10 bit -> 2^10= 1024, 12  bit 2^12, 8 bits 2^8
Vref 5v -> adc = 5/ 1024 = 4.8mV 1bit -> 3.3V 
20Mhz -> 1/20MHz = 50ns : Tosc
TAD > 0.7us
8Tosc -> 8*50ns =  0.4us 
16Tosc -> 16*50ns = 0.8us : TAD 
2.45us < xTAD
TACQ = 6*TAD = 6*0.8us = 4.8us > 2.45us 
 */

//Global variables
uint16_t valor;
float voltaje, temp;

void main(){
    USART_Init(1200);  //USART initialization (1200 baud)
    ADC_init();  //ADC initialitazion
    TRISA = 1;  // PORTA -> Input
    TRISDbits.RD3 = 0;  //Fan output
    
    while(1){
        valor = 0;
        voltaje = 0;
        temp = 0;
        valor = ADC_read(0);  //Reading ADC
        voltaje = (valor*5.0)/1023;  //Volatge conversion
        temp = voltaje*20;  //Temperature conversion
        USART_Tx(temp);  //Sending data
        //Condition to turn on the fan
        if(temp > 35.0){    //35°C
            LATDbits.LD3 = 1;
        }
        else{
            LATDbits.LD3 = 0;
        }
        __delay_ms(200);
    }
}
