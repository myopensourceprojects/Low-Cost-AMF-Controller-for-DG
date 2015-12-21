#define START_RELAY 	RE0
#define STOP_RELAY 		RE1
#define DG_CONTACTOR 	RE2
#define EB_CONTACTOR	RA5

#define UP_KEY	 		RD2
#define DOWN_KEY 		RD3
#define OK_KEY 			RD4

#define LLOP_PIN		RD1
#define VM_OUTPUT  		RD0
//#define EMR_STOP		RA0
#define EMR_STOP		0

void Relay_Init();
void Relay_All_Off();
