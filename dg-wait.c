#include <pic.h>
#include <string.h> 
#include <stdio.h>

#include "lcd.h"
#include "rtc_ds1307.h";
#include "dg-wait.h";
#include "lcd_menu.h";

#define _XTAL_FREQ 4e6

void Wait(unsigned int TinSec)
  {
    char RTChr, RTCmin, RTCsec, RTCDate, i;  
    char tHr, tMin, tSec, tDate;
	char tHrDelay = 0, tMinDelay = 0, tSecDelay = 0, tDayDelay = 0;
	unsigned int tmp;
	char buf[16];

	tHr = TinSec/3600;
	tmp = TinSec%3600;
	tMin = tmp/60;
	tSec = tmp%60;

	sprintf(buf, "Delay <%2d:%2d:%2d> ", tHr, tMin, tSec);
	DBG_Print(2, 1,  buf);

	/* Get Current Time (RTC Time) */
   	RTCsec	= ds1307GetSec();     // Read second
    RTCmin	= ds1307GetMin();	  // Read minute
    RTChr	= ds1307GetHours();   // Read hour
    RTCDate	= ds1307GetDate();    // Read date
   
    tSecDelay = RTCsec+tSec;

 if(tSecDelay >= 59) {
  		tMinDelay = tSecDelay/60;
    	tSecDelay = tSecDelay%60;
  	}
 	tMinDelay = tMinDelay + RTCmin + tMin;

 if(tMinDelay >= 59) {
  		tHrDelay = tMinDelay/60;
  		tMinDelay = tMinDelay%60;
  }
	tHrDelay= tHrDelay + RTChr+tHr;
 
 if(tHrDelay > 23) {
  		tDayDelay = 1;
  		tHrDelay = tHrDelay%24;
  }  
	tDayDelay = tDayDelay+RTCDate; 

	while(1) 
    {   
		tSec	= ds1307GetSec();       // Read second
    	tMin	= ds1307GetMin();       // Read minute
    	tHr		= ds1307GetHours();      // Read hour
    	tDate	= ds1307GetDate();      // Read date
			
		for(i = 0; i < 9; i++) {
			__delay_ms(100);
		}
				/* Wait for TinSec */
	   if ((tSec >= tSecDelay) && (tMin >= tMinDelay) && (tHr>= tHrDelay) && tDate >= tDayDelay)
			break;     
    };
}


