/* 
* 	PIC16F877A EEPROM Library
* 	File:   eeprom.c
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
#include <pic.h>
#include "lcd_menu.h"
#include "eeprom.h"

unsigned char EEPROM_Read(unsigned char addr)
{
	unsigned char dat;

	EEADR = addr;	/* Adddress location */
	EEPGD = 0;		
	RD = 1;			/* T0 start read operation */
	while(RD == 1);	/* Wait to complete read operation */
	dat = EEDATA;

	return dat;
}

void EEPROM_Write(unsigned char addr, unsigned char dat)
{
	EEADR = addr;		/* Adddress location */
	EEDATA = dat;		/* Data	*/
	EEPGD = 0;
	WREN = 1;			/* Enable program operation */
	EECON2 = 0x55;
	EECON2 = 0xAA;
	WR = 1;
	WREN = 0;			/*	Disable program operation */
	while(EEIF == 0);	/* Wait to complete write */
	EEIF = 0;
}


void Save_Config()
{
	sysnc_config_LOCAL_to_GLOBAL();
	EEPROM_Write(SAVE_StartDelay_idx, StartDelay_idx_cfg);
	EEPROM_Write(SAVE_StopDelay_idx, StopDelay_idx_cfg);
	EEPROM_Write(SAVE_OffSolenoid_idx, OffSolenoid_idx_cfg);
	EEPROM_Write(SAVE_Contactor_idx, Contactor_idx_cfg);
	EEPROM_Write(SAVE_Crank_idx, Crank_idx_cfg);
	EEPROM_Write(SAVE_LLOP_idx, LLOP_idx_cfg);
}

void Read_Config()
{
	StartDelay_idx_cfg = EEPROM_Read(SAVE_StartDelay_idx);
	StopDelay_idx_cfg =  EEPROM_Read(SAVE_StopDelay_idx);
	OffSolenoid_idx_cfg = EEPROM_Read(SAVE_OffSolenoid_idx);
	Contactor_idx_cfg = EEPROM_Read(SAVE_Contactor_idx);
	Crank_idx_cfg = EEPROM_Read(SAVE_Crank_idx); 
	LLOP_idx_cfg = EEPROM_Read(SAVE_LLOP_idx);

	if (StartDelay_idx_cfg > START_DELAY_IDX_MAX) {
			StartDelay_idx_cfg = StartDelay_Default_idx;
			EEPROM_Write(SAVE_StartDelay_idx, StartDelay_idx_cfg);
		}	
	if (StopDelay_idx_cfg > STOP_DELAY_IDX_MAX) {
			StopDelay_idx_cfg = StopDelay_Default_idx;
			EEPROM_Write(SAVE_StopDelay_idx, StopDelay_idx_cfg);
	   }	
	if (OffSolenoid_idx_cfg > OFFSOLENOID_IDX_MAX) {
			OffSolenoid_idx_cfg = OffSolenoid_Default_idx;
			EEPROM_Write(SAVE_OffSolenoid_idx, OffSolenoid_idx_cfg);
	   }	
	if (Contactor_idx_cfg > CONTACTOR_IDX_MAX) {
			Contactor_idx_cfg = Contactor_Default_idx;
			EEPROM_Write(SAVE_Contactor_idx, Contactor_idx_cfg);
	   }	
	if (Crank_idx_cfg > CRANK_IDX_MAX) {
			Crank_idx_cfg = Crank_Default_idx;
			EEPROM_Write(SAVE_Crank_idx, Crank_idx_cfg);
	   }	
	if (LLOP_idx_cfg > LLOP_IDX_MAX) {
			LLOP_idx_cfg = LLOP_Default_idx;
			EEPROM_Write(SAVE_LLOP_idx, LLOP_idx_cfg);
	  }	
	sysnc_config_GLOBAL_to_LOCAL();
}

void sysnc_config_GLOBAL_to_LOCAL()
{
	StartDelay_idx = StartDelay_idx_cfg;
	StopDelay_idx = StopDelay_idx_cfg;
	OffSolenoid_idx = OffSolenoid_idx_cfg;
	Contactor_idx = Contactor_idx_cfg;
	Crank_idx = Crank_idx_cfg;
	LLOP_idx = LLOP_idx_cfg;
}

void sysnc_config_LOCAL_to_GLOBAL()
{
	StartDelay_idx_cfg = StartDelay_idx;
	StopDelay_idx_cfg = StopDelay_idx;
	OffSolenoid_idx_cfg = OffSolenoid_idx;
	Contactor_idx_cfg = Contactor_idx;
	Crank_idx_cfg = Crank_idx;
	LLOP_idx_cfg = LLOP_idx;
}