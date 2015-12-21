/* ***********************************************************************
* 	PIC16F877A DG AMF Controller
* 	File:   main.c
* 	Author:  Jithin Krishnan.K
* 	Rev. 	26/11/2015 :  9:28 AM
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
#include <stdio.h>
#include<string.h>

#include "rtc_ds1307.h"
#include "lcd.h"
#include "relay.h"
#include "lcd_menu.h"
#include "eeprom.h"
#include "dg-func.h"
#include "dg-wait.h"

#define _XTAL_FREQ 4e6
__CONFIG(0x3F3A);

//#include <htc.h>
//__CONFIG(FOSC_XT & WDTE_OFF & PWRTE_OFF & BOREN_OFF & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);
//#define _XTAL_FREQ 4000000


char dg_state = 0; // 0 - off; 1 - running

void main()
{
	char Menu = 1, do_start = 1, do_stop = 0, do_once = 1, do_timeset = 0, do_dateset = 0;
 	char tHr, tMin, tSec, buf[20], llop = 1;
	
	LCD_Init();
	ds1307_init();
	Read_Config();
	Relay_Init();

	//set_time(11,55,0, 0);
	//set_date(1, 8, 12, 15);
	
	
while(1) {

	if ((VM_OUTPUT == MAINS_OK) && Menu) {
		if (do_once) {
			StartUpSequence();
			do_once = 0;
		}	
	switch(View) {
	case TIME_SETTINGS:  /* Time Settings Menu view */
		DateTimeMenu();
		Display_CursorTimeMenu();
		if (OK_KEY) {
			LCD_Clear();
			View = TIME_SETTINGS_TIME;	
		}
		while(OK_KEY);
		break;
	case TIME_SETTINGS_TIME:	/* Time Settings Sub Menu view */
		switch(TimeMenu_pos)
			{
				case 2:
					SetTime_Fun();
					do_timeset = 1;
					View == TIME_SETTINGS;
				break;
				case 3:
					SetDate_Fun();
					do_dateset = 1;
					View == TIME_SETTINGS;
				break;
				case 4:// Exit Without saving changes
					View = HOMEMENU;
					TimeMenu_pos = 2;
				break;
				case 5: // Exit with saving changes
					
					if(do_timeset == 1) {
						set_time(RTCHour, RTCMinute, RTCHour, 0);
						do_timeset = 0;
					}
					if (do_dateset == 1) {
						set_date(0, RTCDate, RTCMonth, RTCYear);
						do_dateset = 0;
					}
					
				TimeMenu_pos = 2;
				View = HOMEMENU;
				break;
			}
		break;
	case HOMEMENU: /*Shows Product info*/
		HomeMenu();
	    if(OK_KEY == 1) {
			View = MAINMENU;
			LCD_Clear();
		}
			while(OK_KEY);
		break;
	
    case MAINMENU:	/*Main Menu View */
		MainMenu();
		Display_CursorMainMenu();
		if(OK_KEY == 1) {
			View = SUBMENU;
			LCD_Clear();
		}
			while(OK_KEY);
			break;
	case SUBMENU:	/* Sub Menu View */
		switch(main_menu_pos) {
			case 2:
			SubMenu1();
			Display_CursorSubMenu();
			break;
			case 3:
			SubMenu2();
			Display_CursorSubMenu();
			break;
			case 4: /* Exit without Saving Settings */
			View = HOMEMENU;
			main_menu_pos = 2;
			sysnc_config_GLOBAL_to_LOCAL();
			LCD_Clear();
			break;
			case 5: /* Exit with Saving Settings */
			View = HOMEMENU;
			main_menu_pos = 2;
			Save_Config();
			LCD_Clear();
			break;
			}
				if(OK_KEY == 1) {
				View = OPTMENU;
				LCD_Clear();
			}
			while(OK_KEY);
			break;
    case OPTMENU: /*Options of Sub menu*/
		if (main_menu_pos == 2) {
		switch(submenu_pos)
		{
			case 1:
			StartDelay_fun();
			break;
			case 2:
			StopDelay_fun();
			break;
			case 3:
			OffSolenoid_fun();
			break;
			case 4:
			View = MAINMENU;
			submenu_pos = 1;
			LCD_Clear();
			break;
		 }
		} else if (main_menu_pos == 3) {
		switch(submenu_pos)
		{
			case 1:
			Contactor_fun();
			break;
			case 2:
			Crank_fun();
			break;
			case 3:
			LLOP_fun();
			break;
			case 4:
			View = MAINMENU;
			submenu_pos = 1;
			LCD_Clear();
			break;
		 }
		}
		break;
  		}
  	 } else if((VM_OUTPUT == MAINS_FAIL) && do_start == 1) {	
			if (LLOP_PIN == 1) {
					DBG_Print(1, 1, (char *)LLOP_STR);
					Wait(GetLLOPDelay());
					if (LLOP_PIN == 1) {
						DBG_Print(2, 1, (char *)"Reset System    ");
						while(1);
		   			}
					//LCD_Clear();
					//__delay_ms(10);	
							
				} else {
		     		StartSequence();
					if (VM_OUTPUT == 1) {
			 			do_start  = 0;
			 			do_stop  = 1;	
			 			dg_state = 1; // DG run
			 			Menu = 0;
			 			LCD_Clear();
						__delay_ms(10);	
			 			DBG_Print(1, 3, (char *)"Mains Fail");
					}
		 	  } 	
   			} else if ((VM_OUTPUT == MAINS_OK) && do_stop) {
			 		StopSequence();
				  if (VM_OUTPUT == 0) {	
			 		do_stop = 0;
			 		do_start  = 1;
			 		dg_state = 0; // Dg off 
			 		Menu = 1;
				  }			  	

			} else if ((VM_OUTPUT == MAINS_FAIL) && dg_state && !do_start) { // Emergency Stop and Run time DG Checking 
		 		if (LLOP_PIN == 1) {
					DBG_Print(1, 1, (char *)LLOP_DELAY);
					Wait(GetLLOPDelay());
					if (LLOP_PIN == 1) {
		   					LLOP_EMERGENCY_StopSequence();
							//LCD_Clear();
							//__delay_ms(100);
							DBG_Print(1, 1, (char *)LLOP_STR);
							DBG_Print(2, 1, (char *)"Reset System    ");
							//do_start  = 1;
							//do_stop = 0;
							while(1);
						}
						
					} else if (EMR_STOP == 1) {
						LCD_Clear();	
		   				LLOP_EMERGENCY_StopSequence();
						DBG_Print(1, 1, (char *)"Emergency Stop");
			        	while(1);// Hard Reset required for System work after EMR STOP
					} 
			
			}
			
	}	/* End of While Loop */
   }	/* End of main()*/
 

