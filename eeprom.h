/* 
* 	PIC16F877A EEPROM Library
* 	File:   eeprom.h
* 	Author:  Jithin Krishnan.K
* 	Rev. 0.0.1 : 15/03/2014 :  9:28 AM
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
*	jithinkrishnan.k@gmail.com
*      
************************************************************************/
#define SAVE_StartDelay_idx		0x00
#define SAVE_StopDelay_idx		0x01
#define SAVE_OffSolenoid_idx	0x02
#define SAVE_Contactor_idx		0x03
#define SAVE_Crank_idx			0x04
#define SAVE_LLOP_idx			0x05

/* Default Values*/
#define StartDelay_Default_idx		0x00//0x02
#define StopDelay_Default_idx		0x00//0x02
#define OffSolenoid_Default_idx		0x00//0x02
#define Contactor_Default_idx		0x00//0x02
#define Crank_Default_idx			0x00//0x01
#define LLOP_Default_idx			0x00//0x02

/* Configuration Variable */
unsigned char StartDelay_idx_cfg;
unsigned char StopDelay_idx_cfg;
unsigned char OffSolenoid_idx_cfg;
unsigned char Contactor_idx_cfg;
unsigned char Crank_idx_cfg;
unsigned char LLOP_idx_cfg;

void Save_Config();
void Read_Config();
void sysnc_config_GLOBAL_to_LOCAL();
void sysnc_config_LOCAL_to_GLOBAL();

unsigned char EEPROM_Read(unsigned char addr);
void EEPROM_Write(unsigned char addr, unsigned char dat);
