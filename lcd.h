/************************************************************************
* 	Digital clock using pic16F877A and RTC DS1307
* 	File:   lcd.h
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

#define	RS  RA2
#define	EN 	RA1
#define LCD_DATA_PORT PORTB

void LCD_Data(unsigned char lcd_data);
void LCD_Command(unsigned char lcd_cmd);
void LCD_Clear(void);
void LCD_String(const char *str);
void LCD_Init();
void LCD_Scroll(const char *str);
void DBG_Print(char Line, char pos, char *buf);
void Print_Char(char Line, char pos, char buf);
void LCD_Cursor_on(char Line, char pos );

#define	LCD_ROW_1	LCD_Command(0x80)
#define	LCD_ROW_2	LCD_Command(0xc0)
#define	LCD_ROW_3	LCD_Command(0x94)
#define	LCD_ROW_4	LCD_Command(0xD4)