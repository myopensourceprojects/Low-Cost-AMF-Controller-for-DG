#include<pic.h>
#include "relay.h"

void Relay_Init()
{
	TRISD4 = 1; //Input Key
	TRISD1 = 1; // VM_OUTPUT - Input
	TRISD0 = 1; // LLOP Input
	TRISD3 = 1; //Input Key
	TRISD2 = 1; //Input Key

	TRISE2 = 0; // DG_CONTACTOR
	TRISE1 = 0; // STOP_RELAY
	TRISE0 = 0; // START_RELAY 
	TRISA5 = 0; // EB_CONTACTOR

	RE2 = 0;
	RE1 = 0;
	RE0 = 0;
	RA5 = 0;	

 }


void Relay_All_Off()
 {
    //RD4 = 0;
	//RC5 = 0;
	//RC4 = 0;
	//RD3 = 0;
	//RD2 = 0;

	
	//RA3 = 0;
 } 

