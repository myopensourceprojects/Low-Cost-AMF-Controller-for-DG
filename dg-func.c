/* ***********************************************************************
* 	PIC16F877A DG AMF Controller functions
* 	File:   dg-func.c
* 	Author:  Jithin Krishnan.K
* 	Rev. 	 26/11/2015 :  9:28 AM
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
#include <string.h> 
#include <stdio.h>

#include "lcd.h"
#include "relay.h";
#include "dg-wait.h";
#include "dg-func.h";
#include "eeprom.h";
#include "lcd_menu.h"

void StartUpSequence() 
{
	DBG_Print(1, 1, (char *)" AMF Controller ");
	//DBG_Print(1, 1, (char *)" AMF Controller ");
	START_RELAY 	= 0;
	STOP_RELAY 		= 0;
	DG_CONTACTOR 	= 0;
	EB_CONTACTOR 	= 0;
    Wait(1);
	EB_CONTACTOR 	= 1;
	LCD_Clear();
}

/*
	DG Start Sequence Function 
*/
void StartSequence()
{	
	DBG_Print(1, 1, (char *)DG_START_DELAY);	
	Wait(GetDGStartDelay());
	if (VM_OUTPUT == 1) {
		START_RELAY = 1;
		DBG_Print(1, 1, (char *)CRANK_);
		Wait(GetCrankDelay());
		START_RELAY = 0;
		DG_CONTACTOR = 0;
		EB_CONTACTOR = 0;
		DBG_Print(1, 1, (char *)CONT_DELAY);
    	Wait(GetContactordDelay());
		DG_CONTACTOR = 1;
	}
		LCD_Clear();
}

/*
	DG Stop Sequence Function 
*/
void StopSequence()
{
	DBG_Print(1, 1, (char *)DG_STOP_DELAY);
	Wait(GetDGStopDelay());
	if (VM_OUTPUT == 0) {
		DG_CONTACTOR = 0;
		EB_CONTACTOR = 0;
		STOP_RELAY = 1;
		DBG_Print(1, 1, (char *)OFF_SOLENOID);
		Wait(GetOffSolenoidDelay());
		STOP_RELAY = 0;
		DBG_Print(1, 1, (char *)CONT_DELAY);
    	Wait(GetContactordDelay());
		EB_CONTACTOR = 1;
	}
	LCD_Clear();
}

/*
	DG LLOP/EMERGENCY Stop Sequence Function 
*/
void LLOP_EMERGENCY_StopSequence()
{	
	DBG_Print(1, 1, (char *)"Wait 5 Sec");
	Wait(5);
	DG_CONTACTOR = 0;
	EB_CONTACTOR = 0;
	STOP_RELAY = 1;
	DBG_Print(1, 1, (char *)OFF_SOLENOID);
	Wait(GetOffSolenoidDelay());
	STOP_RELAY = 0;
	//LCD_Clear();
  }

unsigned int GetDGStartDelay(void)
{
	 return StartDelay[StartDelay_idx_cfg];
}
 
unsigned int GetDGStopDelay(void)
{
	return StopDelay[StopDelay_idx_cfg];
}
 
unsigned int GetOffSolenoidDelay(void)
{
	return OffSolenoid[OffSolenoid_idx_cfg];
}

unsigned int GetContactordDelay(void)
{
	return Contactor[Contactor_idx_cfg];
}

unsigned int GetCrankDelay(void)
{
	return Crank[Crank_idx_cfg];
}

unsigned int GetLLOPDelay(void)
{
	return LLOP[LLOP_idx_cfg];
}





