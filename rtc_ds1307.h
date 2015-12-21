/************************************************************************
* 	Digital clock using pic16F877A and RTC DS1307
* 	File:   main.c
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

#define WRITE_CMD	0xd0
#define READ_CMD	0xd1
#define I2C_FREG	1000
#define FOSC		4000000L

#define SEC 	0  /* RTC Register Address */
#define MIN		1
#define HOUR	2
#define DAY		3 
#define DATE	4 
#define MONTH	5
#define YEAR	6
#define CS		7  

#define HRS_12 		1
#define HRS_24 		0

void ds1307_init(void);
void WaitMSSP(void);
void ds1307Write(unsigned char reg_addr, unsigned char data);
unsigned char ds1307Read(unsigned char reg_addr);
void set_ctrl_reg(void);

unsigned char ds1307GetSec();
unsigned char ds1307GetMin();
unsigned char ds1307GetHours();
unsigned char ds1307GetDay();
unsigned char ds1307GetDate();
unsigned char ds1307GetMonth();
unsigned char ds1307GetYear();
unsigned char BCDToDecimal (unsigned char bcdByte);
unsigned char DecimalToBCD (unsigned char decimalByte);
char set_date(char day, char date, char month, char year);
char set_time(char hr, char min, char sec, char time_format);