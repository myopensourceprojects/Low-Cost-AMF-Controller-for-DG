/* 
* 	PIC16F877A EEPROM Library
* 	File:   lcd_menu.c
* 	Author:  Jithin Krishnan.K
* 	Rev. 0.0.1 : 18/11/2015 :  9:28 PM
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
#include "rtc_ds1307.h"
#include "lcd_menu.h"
#include "lcd.h"
#include "relay.h"

#define _XTAL_FREQ 4e6

/* Function for Displaying cursor in Main menu */
void Display_CursorMainMenu()
{	
	if(UP_KEY == 1)
       {
		 main_menu_pos++;
		 if (main_menu_pos >= 5)
		 main_menu_pos = 5;
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1)
       {
		 main_menu_pos--;
		 if (main_menu_pos <= 2)
		 main_menu_pos = 2;	
	   }
    while(DOWN_KEY);
	ShowCursor(main_menu_pos);
}

/* Function for Displaying cursor in Time settings menu */
void Display_CursorTimeMenu()
{
	if(UP_KEY == 1)
       {
		 TimeMenu_pos++;
		 if (TimeMenu_pos >= 5)
		 TimeMenu_pos = 5;		
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1)
       {
		 TimeMenu_pos--;
		 if (TimeMenu_pos <= 2)
		 TimeMenu_pos = 2;		
	   }
    while(DOWN_KEY);
	ShowCursor(TimeMenu_pos);
}

/* Function for Displaying cursor in Sub menu */
void Display_CursorSubMenu()
{	
	if(UP_KEY == 1)
       {
		 submenu_pos++;
		 if (submenu_pos >= 4)
		 submenu_pos = 4;		
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1)
       {
		 submenu_pos--;
		 if (submenu_pos <= 1)
		 submenu_pos = 1;		
	   }
    while(DOWN_KEY);
	ShowCursor(submenu_pos);
}


void HomeMenu()
{	
	char buf[16];

	sprintf(buf, "Date :%2d/%2d/20%2d", ds1307GetDate(), ds1307GetMonth(), ds1307GetYear());
   	DBG_Print(1, 1, buf);
	sprintf(buf, "Time :%2d:%2d:%2d  ", ds1307GetHours(), ds1307GetMin(), ds1307GetSec());
	DBG_Print(2, 1, buf);

	
	if (UP_KEY && DOWN_KEY) {
		View = TIME_SETTINGS;
		LCD_Clear();
	}
	while(UP_KEY && DOWN_KEY);
}	

void CheckPassword()
{
	char pwd = 0, ok = 1;
	char buf[4];

    LCD_Clear();
	DBG_Print(1, 1, (char *)"Enter Password");
	while(ok) {	
	if(UP_KEY == 1)
       {
		 pwd++;
		 if (pwd >= 255)
		 pwd = 0;		
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1)
       {
		 pwd--;
		 if (pwd <= 1)
		 pwd = 255;		
	   }
    while(DOWN_KEY);
	sprintf(buf, "%2d",pwd);
	DBG_Print(2, 1, buf);
	if(OK_KEY == 1) {
			if(pwd == 10)
				ok = 0;
			else 
				ok = 1;
		}	
	while(OK_KEY);
	}
}

void MainMenu()
{	
 	if (main_menu_pos == 2) {
		DBG_Print(1, 2, (char *)"Main Menu");
		DBG_Print(2, 2, (char *)"Timing Settings");
	} else if (main_menu_pos > 2){
		DBG_Print(1, 2, (char *)"Cont. setting");
		DBG_Print(2, 2, (char *)SAVE_EXIT);
	}
}

void DateTimeMenu()
{
	if (TimeMenu_pos <=2) {
		DBG_Print(1, 2, (char *)"Date & Time");
		DBG_Print(2, 2, (char *)TIME_STR);
	} else if (TimeMenu_pos > 2){
		DBG_Print(1, 2, (char *)DATE_STR);
		DBG_Print(2, 2, (char *)SAVE_EXIT);
	}
}

void SubMenu1()
{
	if (submenu_pos <=2) {
		DBG_Print(1, 2, (char *)DG_START_DELAY);
		DBG_Print(2, 2, (char *)DG_STOP_DELAY);
	} else if (submenu_pos > 2) {	
		DBG_Print(1, 2, (char *)OFF_SOLENOID);
		DBG_Print(2, 2, (char *)GO_TO_MAIN);
	}	
}

void SubMenu2()
{
	if (submenu_pos <=2) {
		DBG_Print(1, 2, (char *)CONT_DELAY);
		DBG_Print(2, 2, (char *)CRANK_);
	} else if (submenu_pos > 2) {
		DBG_Print(1, 2, (char *)LLOP_DELAY);
		DBG_Print(2, 2, (char *)GO_TO_MAIN);
	}
}

void StartDelay_fun()
{	
	struct TimeConvert tmp;
	char buf[4];

	DBG_Print(1, 1, (char *)DG_START_DELAY);
	if(UP_KEY == 1) {
		    if (StartDelay_idx >= (START_DELAY_IDX_MAX - 1))
		 		StartDelay_idx = (START_DELAY_IDX_MAX - 1);
			else
				StartDelay_idx++;
		 LCD_Clear();			
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1) {
		 if (StartDelay_idx < 1)
		 	StartDelay_idx = 0;
		 else
			StartDelay_idx--;		
		 LCD_Clear();	
	   }
    while(DOWN_KEY);
	
	if(OK_KEY == 1) {
		View = SUBMENU;
		LCD_Clear();
	}
	   while(OK_KEY){__delay_ms(50);};

		tmp = SecToMinHr(StartDelay[StartDelay_idx]);
		sprintf(buf, "%2d %s",tmp.value, tmp.unit );
		DBG_Print(2, 1, buf);
}

void StopDelay_fun()
{	
	struct TimeConvert tmp;
	char buf[4];

	DBG_Print(1, 1, (char *)DG_STOP_DELAY);
		if(UP_KEY == 1) {
		 	if (StopDelay_idx >= (STOP_DELAY_IDX_MAX - 1))
		 		StopDelay_idx = (STOP_DELAY_IDX_MAX - 1);
			else
				StopDelay_idx++;
		 LCD_Clear();			
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1) {
		  if (StopDelay_idx < 1)
		 	StopDelay_idx = 0;
		  else
			StopDelay_idx--;	
		 LCD_Clear();	
	   }
    while(DOWN_KEY);
	
	if(OK_KEY == 1) {
		View = SUBMENU;
		LCD_Clear();
	}
	   while(OK_KEY){__delay_ms(50);};

	   tmp = SecToMinHr(StopDelay[StopDelay_idx]);
	   sprintf(buf, "%2d %s",tmp.value, tmp.unit );
	   DBG_Print(2, 1, buf);	
}

void OffSolenoid_fun()
{	
	struct TimeConvert tmp;
	char buf[4];

	DBG_Print(1, 1, (char *)OFF_SOLENOID);
		if(UP_KEY == 1) {
		  	if (OffSolenoid_idx >= (OFFSOLENOID_IDX_MAX - 1))
		 		OffSolenoid_idx = (OFFSOLENOID_IDX_MAX - 1);
			else
				OffSolenoid_idx++;
		 LCD_Clear();			
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1) {
		    if (OffSolenoid_idx < 1)
		 		OffSolenoid_idx = 0;
			else
				OffSolenoid_idx--;	
		 LCD_Clear();	
	   }
    while(DOWN_KEY);
	
	if(OK_KEY == 1) {
		View = SUBMENU;
		LCD_Clear();
	}
	   while(OK_KEY){__delay_ms(50);};
	   
	   tmp = SecToMinHr(OffSolenoid[OffSolenoid_idx]);
	   sprintf(buf, "%2d %s",tmp.value, tmp.unit );
	   DBG_Print(2, 1, buf);
}

void Contactor_fun()
{	
	struct TimeConvert tmp;
	char buf[4];

	DBG_Print(1, 1, (char *)CONT_DELAY);
		if(UP_KEY == 1) {
		 	if (Contactor_idx >= (CONTACTOR_IDX_MAX - 1))
		 		Contactor_idx = (CONTACTOR_IDX_MAX - 1);
			else
				Contactor_idx++;
		 LCD_Clear();			
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1) {
		 	if (Contactor_idx < 1)
		 		Contactor_idx = 0;
			else
				Contactor_idx--;	
		 LCD_Clear();	
	   }
    while(DOWN_KEY);
	
	if(OK_KEY == 1) {
		View = SUBMENU;
		LCD_Clear();
	}
	   while(OK_KEY){__delay_ms(50);};
	   
       tmp = SecToMinHr(Contactor[Contactor_idx]);
	   sprintf(buf, "%2d %s",tmp.value, tmp.unit );
	   DBG_Print(2, 1, buf);
}


void Crank_fun()
{	
	struct TimeConvert tmp;
	char buf[4];

	DBG_Print(1, 1, (char *)CRANK_);
		if(UP_KEY == 1) {
		 	if (Crank_idx >= (CRANK_IDX_MAX - 1))
		 	Crank_idx = (CRANK_IDX_MAX - 1);
			else
			Crank_idx++;		
		 LCD_Clear();			
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1)
       {
		     if (Crank_idx < 1)
		 		Crank_idx = 0;
			 else 
				Crank_idx--;		
		 LCD_Clear();	
	   }
    while(DOWN_KEY);
	
	if(OK_KEY == 1) {
		View = SUBMENU;
		LCD_Clear();
	}
	   while(OK_KEY){__delay_ms(50);};

	   tmp = SecToMinHr(Crank[Crank_idx]);
	   sprintf(buf, "%2d %s",tmp.value, tmp.unit);
	   DBG_Print(2, 1, buf);	
}

void LLOP_fun()
{	
	struct TimeConvert tmp;
	char buf[4];

	DBG_Print(1, 1, (char *)LLOP_DELAY);
	if(UP_KEY == 1) {
		 	if (LLOP_idx >= (LLOP_IDX_MAX - 1))
		 		LLOP_idx = (LLOP_IDX_MAX - 1);
			else
				LLOP_idx++;
		 LCD_Clear();			
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1) {
			if (LLOP_idx < 1)
		 	LLOP_idx = 0;
				else
			LLOP_idx--;	
		 LCD_Clear();	
	   }
    while(DOWN_KEY);
	
	if(OK_KEY == 1) {
		View = SUBMENU;
		LCD_Clear();
	}
	   while(OK_KEY){__delay_ms(50);};

	   tmp = SecToMinHr(LLOP[LLOP_idx]);
	   sprintf(buf, "%2d %s",tmp.value, tmp.unit);
	   DBG_Print(2, 1, buf);
}

void SetTime_Fun()
{	
	char buf[17], i, pos = 1;
	char hr_ = 0, min_ = 0, sec_ = 0;
	char key = 1;	
	
	sec_		= ds1307GetSec();        // Read second
   	min_		= ds1307GetMin();        // Read minute
    hr_			= ds1307GetHours();      // Read hour
	
	LCD_Clear();
	DBG_Print(1, 1, (char *)TIME_STR);
	sprintf(buf, "%2d:%2d:%2d", hr_, min_, sec_);
	DBG_Print(2, 1, buf);

	while (1) {
		if (key == 1) {
	if(UP_KEY == 1) {
		if (pos >= 4)
		     pos = 4;
		else 
			 pos++;				
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1) {
		 if (pos <= 1)
		     pos = 1;
		else
			pos--;
	   }
    while(DOWN_KEY);

	switch(pos)
		{
			case 1:
			DBG_Print(2, 12, (char *)"Exit ");
			if(OK_KEY == 1) {
				RTCHour 	= hr_;
				RTCMinute 	= min_;
				RTCSecond 	= sec_;
					key = 2;
					__delay_ms(50);
				}
			while(OK_KEY){__delay_ms(50);};
			break;
			case 2:
			DBG_Print(2, 12, (char *)"Hour ");
			if(OK_KEY == 1) {
					key = 2;
					__delay_ms(50);
				}
			while(OK_KEY){__delay_ms(50);};
			break;
			case 3:
			DBG_Print(2, 12, (char *)"Min  ");
				if(OK_KEY == 1) {
					key = 2;
					__delay_ms(50);
				}
			while(OK_KEY){__delay_ms(50);};
			break;
			case 4:
			DBG_Print(2, 12, (char *)"Sec  ");
				if(OK_KEY == 1) {
					key = 2;
					__delay_ms(50);
				}
			while(OK_KEY){__delay_ms(50);};
			break;
		}		
	} else if (key == 2) {
		switch(pos)
        {
			case 1: 
				  RTCHour 	= hr_;
				  RTCMinute = min_;
				  RTCSecond = sec_;			
				  View = TIME_SETTINGS;
				  key = 3;	
				  break;
			case 2:
				if(UP_KEY == 1) {
		 		 if (hr_ >= 23)
		     		hr_ = 23;
				  else 
					hr_++;			
	  			 }
    			while(UP_KEY);

				if(DOWN_KEY == 1) {
				
		 		if (hr_ <= 1)
		    		 hr_ = 0;
				else
					hr_--;
	   			}
    			while(DOWN_KEY);
				break;
			case 3:
				if(UP_KEY == 1) {
		 			
					 if (min_ >= 59)
		     		min_ = 59;
					 else
					min_++;
								
	  			 }
    			while(UP_KEY);

				if(DOWN_KEY == 1) {
				if (min_ <= 1)
		    		 min_ = 0;
				else
					 min_--;
	   			}
    			while(DOWN_KEY);
				break;
			case 4:
				if(UP_KEY == 1) {
		 			
					 if (sec_ >= 59)
		     		sec_ = 59;
					else
					sec_++;			
	  			 }
    			while(UP_KEY);

				if(DOWN_KEY == 1) {
				
		 		if (sec_ <= 1)
		    		 sec_ = 0;
				else
					sec_--;
	   			}
    			while(DOWN_KEY);
				break;
		}
			DBG_Print(1, 1, (char *)TIME_STR);
			sprintf(buf, "%2d:%2d:%2d", hr_, min_, sec_);
			DBG_Print(2, 1, buf);
			
			if(OK_KEY == 1) {
					key = 1;
				}
	   		while(OK_KEY){__delay_ms(50);};
	} else if (key == 3)
	  break;		
	 
};
}

void SetDate_Fun()
{	
	char buf[16], i, pos = 1;
	char date, mon, year;
	char key = 1;	
	
	date	= ds1307GetDate();       // Read date DS1307Read(DATE)
 	mon		= ds1307GetMonth();	     // Read month
 	year	= ds1307GetYear();       // Read year

	DBG_Print(1, 1, (char *)DATE_STR);
	sprintf(buf, "%2d/%2d/20%2d", date, mon, year);
	DBG_Print(2, 1, buf);
		
	while (1) {
		if (key == 1) {
	if(UP_KEY == 1) {
		if (pos >= 4)
		     pos = 4;
		else 
			 pos++;				
	   }
    while(UP_KEY);

	if(DOWN_KEY == 1) {
		 if (pos <= 1)
		     pos = 1;
		else
			pos--;
	   }
    while(DOWN_KEY);


	   switch(pos)
		{
			case 1:
			DBG_Print(2, 12, (char *)"Exit ");
			if(OK_KEY == 1) {
				RTCDate 	= date;
 	 	    	RTCMonth 	= mon;
				RTCYear  	= year;	
					key = 2;
				}
			while(OK_KEY){__delay_ms(50);};
			break;
			case 2:
			DBG_Print(2, 12, (char *)"Date ");
			if(OK_KEY == 1) {
					key = 2;
				}
			while(OK_KEY){__delay_ms(50);};
			break;
			case 3:
			DBG_Print(2, 12, (char *)"Month");
				if(OK_KEY == 1) {
					key = 2;
				}
			while(OK_KEY){__delay_ms(50);};
			break;
			case 4:
			DBG_Print(2, 12, (char *)"Year ");
				if(OK_KEY == 1) {
					key = 2;
				}
			while(OK_KEY){__delay_ms(50);};
			break;
		}		
			
	} else if (key == 2) {
		switch(pos)
        {
			case 1: 
				  RTCDate = date;
 				  RTCMonth = mon;
				  RTCYear  = year;	
				  key = 3;
				  View = TIME_SETTINGS;	
				  break;
			case 2:
				if(UP_KEY == 1) {
		 		 if (date >= 31)
		     		date = 31;
				  else 
					date++;			
	  			 }
    			while(UP_KEY);

				if(DOWN_KEY == 1) {
				
		 		if (date <= 1)
		    		 date = 1;
				else
					date--;
	   			}
    			while(DOWN_KEY);
				break;
			case 3:
				if(UP_KEY == 1) {
		 			
					 if (mon >= 12)
		     		mon = 12;
					 else
					mon++;			
	  			 }
    			while(UP_KEY);

				if(DOWN_KEY == 1) {
				if (mon <= 1)
		    		 mon = 1;
				else
					 mon--;
	   			}
    			while(DOWN_KEY);
				break;
			case 4:
				if(UP_KEY == 1) {
		 			
					 if (year >= 99)
		     		   year = 99;
					else
					  year++;			
	  			 }
    			while(UP_KEY);

				if(DOWN_KEY == 1) {
				
		 		if (year <= 15)
		    		 year = 15;
				else
					year--;
	   			}
    			while(DOWN_KEY);
				break;
		}
			DBG_Print(1, 1, (char *)DATE_STR);
			sprintf(buf, "%2d/%2d/20%2d", date, mon, year);
			DBG_Print(2, 1, buf);
			
				if(OK_KEY == 1) {
					key = 1;
				}
	   		while(OK_KEY){__delay_ms(50);};
	} else if (key == 3)
	  break;		
	 
};
}

void ShowCursor(char pos)
{
		if ((pos == 5) && ((View == MAINMENU)||(View == TIME_SETTINGS))) {/*Applicable to main Menu & Time settings menu only*/
				Print_Char(2, 7, '>');
				Print_Char(2, 1, ' ');
				__delay_ms(20);	
			}
		if ((pos == 1) || (pos == 3)) {		
			Print_Char(1, 1, '>');
			Print_Char(2, 1, ' ');
			__delay_ms(20);
		} else if ((pos == 2) || (pos == 4)) {
			Print_Char(1, 1, ' ');
			Print_Char(2, 1, '>');
			__delay_ms(20);
		}
}

struct TimeConvert SecToMinHr(unsigned int TSec)
{
	struct TimeConvert tmp;

	if (TSec < 60) /* Second */
		{
			strcpy(tmp.unit, "Sec");
			tmp.value = TSec;
		}
	else if (TSec < 3600) /* Minute */
		{
			strcpy(tmp.unit, "Min");
			tmp.value = TSec/60;
		}
	else if (TSec <= 43200) /* Hour */
		{
			strcpy(tmp.unit, "Hr ");
			tmp.value = TSec/3600;
		}
	return tmp;	
}
