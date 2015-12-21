/************************************************************************
* 	Digital clock using pic16F877A and RTC DS1307
* 	File:   lcd.c
* 	Author:  Jithin Krishnan.K
*   Rev. 0.0.1 : 17/03/2014 :  10:11 AM
* 
*	This program is free software: you can redistribute it and/or modify
*  	it under the terms of the GNU General Public License as published by
*  	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*	Email: jithinkrishnan.k@gmail.com
*   
************************************************************************/

#include <pic.h>
#include "lcd.h"

#define _XTAL_FREQ 4e6

void LCD_Data(unsigned char lcd_data)
{
    RS = 1;
    __delay_us(200);
    LCD_DATA_PORT = lcd_data;
    EN= 1;
    __delay_us(200);
    EN = 0;
}

void LCD_Command(unsigned char lcd_cmd)
{
    RS = 0;
    __delay_us(1);
    LCD_DATA_PORT = lcd_cmd;
    EN= 1;
    __delay_us(200);
    EN = 0;
}


void LCD_Clear(void)
{
    LCD_Command(0x01);
    __delay_ms(1);
}

void LCD_String(const char *str)
{   
    while(*str) {
    LCD_Data(*str++);
   }
}

void LCD_Init()
{
    TRISB  = 0x00;
	ADCON1 = 0x06;
    CMCON  = 0x07;
	
	TRISA2  = 0;
	TRISA1  = 0;

    __delay_ms(15);
    LCD_Command(0x38);
    __delay_ms(5);
    LCD_Command(0x38);
    __delay_us(50);
    LCD_Command(0x38);
    __delay_us(50);
    LCD_Command(0x06);    
    __delay_us(50);
	LCD_Command(0x0F);
   __delay_us(50);    
   LCD_Command(0x0c);
   __delay_us(50);
}

void DBG_Print(char Line, char pos, char *buf)
{
   pos = pos - 1;
   switch(Line){
     case 1:
		LCD_Command(0x80 + pos);
		break;
	 case 2:
		LCD_Command(0xc0 + pos);
		break;
 	 case 3:
		LCD_Command(0x94 + pos);
		break;
     case 4:
		LCD_Command(0xD4 + pos);
		break;	
   }
	LCD_String(buf);
}

void Print_Char(char Line, char pos, char buf)
{
   
   pos = pos - 1;
   switch(Line){
     case 1:
		LCD_Command(0x80 + pos);
		break;
	 case 2:
		LCD_Command(0xc0 + pos);
		break;
 	 case 3:
		LCD_Command(0x94 + pos);
		break;
     case 4:
		LCD_Command(0xD4 + pos);
		break;	
   }
	LCD_Data(buf);
}

void LCD_Scroll(const char *str)
{
   int i;
 
	while (*str) {
        LCD_Clear();
		LCD_String(str++);
		for(i = 0; i < 8; i++)
		__delay_ms(20);
    }
}

void LCD_Cursor_on(char Line, char pos)
{
		LCD_Command(0x0E);
}