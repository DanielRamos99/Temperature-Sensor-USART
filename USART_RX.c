/*
 * File:   PROYECTORX.c
 * Author: Daniel Ramos 
 */


#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "configuration.h"
#include "LCD_library.h"
#include "ADC_library.h"
#include "USART_library.h"


//Global variables
float temp; 
char datos[20];

//LCD initialization
void LCD_Init(void){
    OpenXLCD(FOUR_BIT & LINES_5X7 );
    while(BusyXLCD()); //LCD busy
    WriteCmdXLCD(0x06); //Move cursor to thew right
    WriteCmdXLCD(0x0C); //Uneable cursor
}

void main(){
    USART_Init(1200);  //USART initialization (1200 baud)
    LCD_Init();  //LCD initialization
    //Proyect presentation
    LCD_gotoXY(0,0);
    putrsXLCD("    PROJECT    ");
    __delay_ms(100);
    LCD_gotoXY(1,0);                //Position (x,y)
    putrsXLCD("  TERMOMETER  ");
    __delay_ms(2500);
    WriteCmdXLCD(BORRAR_LCD);   //Cleaning LCD
    LCD_gotoXY(0,0);
    putrsXLCD("  DANIEL RAMOS  ");
    __delay_ms(2500);
    WriteCmdXLCD(BORRAR_LCD);
    
    while(1){
        temp = 0;
        WriteCmdXLCD(BORRAR_LCD);
        __delay_ms(20);
        LCD_gotoXY(0,0);
        putrsXLCD("  TEMPERATURA:  ");
        __delay_ms(100);
        temp = USART_Rx();  //Reading sended data
        __delay_ms(20);
        LCD_gotoXY(1,0);
        sprintf(datos,"    %.2f C    ",temp); //Data on LCD
        putrsXLCD(datos);
        __delay_ms(100);
    }
}
