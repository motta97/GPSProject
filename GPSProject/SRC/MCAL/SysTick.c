#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Bit_Utilies.h"

//SysTick initialization
 void SysTick_Init(void){
 NVIC_ST_CTRL_R=0; 								//1)disable SysTick during setup
 NVIC_ST_RELOAD_R=0x00FFFFFF; 		//2) maximum reload value
 NVIC_ST_CURRENT_R=0; 						//3)any write to CURRENT clears it
 NVIC_ST_CTRL_R=0x00000005; 			//4) enable Systick with core clock
}
 
// The delay parameter is in units of the 80 MHz core clocks (12.5)

  void SysTick_Wait(uint32_t delay){
 NVIC_ST_RELOAD_R=delay-1; 											//number of counts
 NVIC_ST_CURRENT_R=0; 													//any value written to CURRENT clears
 while((NVIC_ST_CTRL_R&0x00010000)==0) {}				//wait for flag
}
	
//Call this routine to wait for delay*10ms

void SysTick_Wait10ms(uint32_t delay){
	unsigned long i;
	for(i=0;i<delay;i++){
	SysTick_Wait(160000);													//wait 10ms
		}
}
