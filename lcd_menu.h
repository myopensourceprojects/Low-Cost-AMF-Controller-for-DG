/* 
* 	PIC16F877A EEPROM Library
* 	File:   lcd_menu.h
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

#define HOMEMENU			1
#define MAINMENU			2
#define SUBMENU 			3
#define OPTMENU				4
#define TIME_SETTINGS		5
#define TIME_SETTINGS_TIME	6

char RTCHour, RTCMinute, RTCSecond;
char RTCMonth, RTCDate, RTCYear;
char View = HOMEMENU;

const char SAVE_EXIT[] = "Exit  Save      ";
const char GO_TO_MAIN[] = "Main Menu       ";
const char TIME_STR[] = "Time Settings   ";
const char DATE_STR[] = "Date Settings   ";
const char DG_START_DELAY[] = "DG Start Delay  ";
const char DG_STOP_DELAY[] = "DG Stop Delay   ";
const char OFF_SOLENOID[] = "OFFSolenoidDelay";
const char CONT_DELAY[] = "Cont.ON/OFF Time";
const char CRANK_[] = "DG Crank Time   ";
const char LLOP_DELAY[] = "LLOP hold Time  ";
const char LLOP_STR[] = "Low Oil Pressure";

char main_menu_pos = 2;
char submenu_pos = 1;
char TimeMenu_pos = 2;

char StartDelay_idx;
char StopDelay_idx;
char OffSolenoid_idx;
char Contactor_idx;
char Crank_idx;
char LLOP_idx;
char Date_Time_idx;

struct TimeConvert {
	char unit[4];
	char value;
};

void ShowCursor(char pos);
void Display_CursorMainMenu();
void Display_CursorSubMenu();
void Display_CursorTimeMenu();
void StartDelay_fun();
void StopDelay_fun();
void OffSolenoid_fun();
void Contactor_fun();
void Crank_fun();
void LLOP_fun();
void HomeMenu();
void MainMenu();
void DateTimeMenu();
void SetTime_Fun();
void SetDate_Fun();
void SubMenu1();
void SubMenu2();
struct TimeConvert SecToMinHr(unsigned int Tsec);
void CheckPassword();

#define	START_DELAY_IDX_MAX		10
#define	STOP_DELAY_IDX_MAX 		3
#define	OFFSOLENOID_IDX_MAX		7
#define	CONTACTOR_IDX_MAX		9
#define	CRANK_IDX_MAX			5
#define	LLOP_IDX_MAX			3

/* All Values are in seconds */
unsigned int StartDelay[START_DELAY_IDX_MAX] = {30, 60, 300, 600, 1800, 3600, 7200, 18000, 36000, 43200};
unsigned int StopDelay[STOP_DELAY_IDX_MAX] = {30, 60, 300};
unsigned int OffSolenoid[OFFSOLENOID_IDX_MAX] = {5, 10, 15, 20, 30, 40, 60};
unsigned int Contactor[CONTACTOR_IDX_MAX] = {5, 10, 15, 20, 30, 50, 60, 120, 180};
unsigned int Crank[CRANK_IDX_MAX] = {1, 2, 3, 4, 5};
unsigned int LLOP[LLOP_IDX_MAX] = {2, 5, 10};