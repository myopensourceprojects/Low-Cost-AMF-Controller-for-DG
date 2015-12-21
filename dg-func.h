
#define MAINS_OK 		0
#define MAINS_FAIL 		1

void StartSequence();
void StopSequence();
void StartUpSequence();
void LLOP_EMERGENCY_StopSequence();
unsigned int GetDGStartDelay(void);
unsigned int GetDGStopDelay(void);
unsigned int GetOffSolenoidDelay(void);
unsigned int GetContactordDelay(void);
unsigned int GetCrankDelay(void);
unsigned int GetLLOPDelay(void);