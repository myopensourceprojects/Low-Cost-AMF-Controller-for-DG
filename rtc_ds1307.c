/************************************************************************
* 	Digital clock using pic16F877A and RTC DS1307
* 	File:   rtc_ds1307.c
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
#include <string.h>
#include <stdio.h>
#include "rtc_ds1307.h"

#define _XTAL_FREQ 4e6

void ds1307_init()
{
   	TRISC3 = 1;      						/* RC3,RC4 set to I2C Mode(Input) */
   	TRISC4 = 1;

   	SSPCON = 0x28;   						/* Enable the SDA, SCL & I2C Master Mode */
   	SSPADD = (FOSC / (4 * I2C_FREG)) - 1;	/* SSP baud rate 100Khz */
   	SSPSTAT = 0x80; 						/* Disable slew Rate control */
   	SSPIF = 0;
	BCLIF = 0;
	SSPCON2 = 0;
}

void WaitMSSP()
{  
	while(RW || SEN || RSEN || PEN || RCEN || ACKEN) {
        __delay_ms(1);
    } 
}
 
void ds1307Write(unsigned char reg_addr, unsigned char data)
{
   SEN = 1;      			/* Initiate Start condition on SDA & SCL pins */
   WaitMSSP();                             
   SSPBUF = WRITE_CMD;   	/* Slave address + Write command */
   WaitMSSP();                           
   SSPBUF = reg_addr;
   WaitMSSP();
   SSPBUF = data;
   WaitMSSP();
   PEN = 1;               	/* Enable the Stop bit */
   WaitMSSP();                               
}

unsigned char ds1307Read(unsigned char reg_addr)
{
   unsigned char read_data;

   RSEN = 1;   				/* Enable the repeated Start Condition */
   WaitMSSP ();                          
   SSPBUF = WRITE_CMD;
   WaitMSSP();                           
   SSPBUF = reg_addr;     
   WaitMSSP();                          
   RSEN = 1;
   WaitMSSP();  
   SSPBUF = READ_CMD; 		
   WaitMSSP();                          
   RCEN = 1;         		/* Enable to receive data */
   WaitMSSP();                          
   ACKDT = 1;    			/* Acknowledge the operation (Send NACK) */
   ACKEN = 1;    			/* Acknowledge sequence on SDA & SCL pins */
   PEN = 1;      			/* Enable the Stop bit */
   WaitMSSP();                          
   read_data = SSPBUF;   	/* Store the Receive value in a variable */
   return (read_data);          
}

unsigned char BCDToDecimal (unsigned char bcdByte)
{
 	unsigned char Dec;

	if (bcdByte < 0x10)		/* 0 - 9   */
		Dec = bcdByte;
	else if (bcdByte < 0x20)	/* 10 - 19 */
		Dec = bcdByte - 6;
	else if (bcdByte < 0x30)	/* 20 - 29 */
		Dec = bcdByte - 12;
	else if (bcdByte < 0x40)	/* 30 - 39 */
		Dec = bcdByte - 18;
	else if (bcdByte < 0x50)	/* 40 - 49 */
		Dec = bcdByte - 24;
	else if (bcdByte < 0x60)	/* 50 - 59 */
		Dec = bcdByte - 30;

	return Dec;
}
 
unsigned char DecimalToBCD (unsigned char decimalByte)
{
	unsigned char bcd;
	
	if (decimalByte < 10)		/* 0 - 9   */
		bcd = decimalByte;
	else if (decimalByte < 20)	/* 10 - 19 */
		bcd = decimalByte + 6;
	else if (decimalByte < 30)	/* 20 - 29 */
		bcd = decimalByte+12;
	else if (decimalByte < 40)	/* 30 - 39 */
		bcd = decimalByte + 18;
	else if (decimalByte < 50)	/* 40 - 49 */
		bcd = decimalByte+24;
	else if (decimalByte < 60)	/* 50 - 59 */
		bcd = decimalByte + 30;

	return bcd;
}

unsigned char ds1307GetSec()
{
    unsigned char sec10;
    unsigned char sec1;

    unsigned char bcdSec = ds1307Read(SEC);

    bcdSec = bcdSec & 0b1111111;
    sec10 = bcdSec >> 4;
    sec1 = bcdSec & 0b1111;

    return sec10 * 10 + sec1;
}

unsigned char ds1307GetMin(){
    unsigned char min10;
    unsigned char min1;

    unsigned char bcdMin = ds1307Read(MIN);

    bcdMin = bcdMin & 0b1111111;
    min10 = bcdMin >> 4;
    min1 = bcdMin &0b1111;

    return min10 * 10 + min1;
}

unsigned char ds1307GetHours()
{
    unsigned char hour10, hour1, retHour, bcdHour;
    
    bcdHour = ds1307Read(HOUR);

    bcdHour = bcdHour & 0b1111111;
    if(bcdHour > 63){
        bcdHour = bcdHour & 0b111111;

        hour10 = (bcdHour & 0b11111) >> 4;
        hour1 = bcdHour & 0b1111;
        retHour = hour10 * 10 + hour1;
        if(bcdHour > 31){//is PM?
            if(retHour != 12)
                retHour = retHour + 12;
        }
    }else{
        bcdHour = bcdHour & 0b111111;
        hour10 = bcdHour >> 4;
        hour1 = bcdHour & 0b1111;

        retHour = hour10 * 10 + hour1;
    }

    return retHour;
}

unsigned char ds1307GetDay()
{
    return BCDToDecimal(ds1307Read(DAY));
}

unsigned char ds1307GetDate()
{
    return BCDToDecimal(ds1307Read(DATE));
}

unsigned char ds1307GetMonth()
{
    return (BCDToDecimal(ds1307Read(MONTH));
}

unsigned char ds1307GetYear()
{
    return BCDToDecimal(ds1307Read(YEAR));
}

char  set_time(char hr, char min, char sec, char time_format)
{
	
	ds1307Write(SEC, DecimalToBCD(sec)); 	/* Second */
	ds1307Write(MIN, DecimalToBCD(min)); 	/* Minute */
	hr = DecimalToBCD(hr);	
	if (time_format == HRS_12) 		/* 12 hrs */
 		hr = hr | 0x40;
	else if (time_format == HRS_24)
		hr = hr & 0xBF;
	ds1307Write(HOUR, hr); 						/* Hour	*/
	
	return 0;
}

char set_date(char day, char date, char month, char year)
{

	ds1307Write(DAY, DecimalToBCD(day)); 	/* Day */
	ds1307Write(DATE, DecimalToBCD(date));	/* Date */
	ds1307Write(MONTH, DecimalToBCD(month)); /* Month */
	ds1307Write(YEAR, DecimalToBCD(year)); 	/* Year */
	
	return 0;
}

void set_ctrl_reg()
{
	ds1307Write(CS, 0x10);
}
