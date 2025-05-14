#ifndef SysTick
#define SysTick

#include <stdint.h>

void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait10ms(uint32_t delay);

#endif	
