#ifndef GPIO
#define GPIO

#define GPIO_RED_LED       0x02
#define GPIO_BLUE_LED      0x04
#define GPIO_GREEN_LED     0x08
#define GPIO_LED_ON					1				
#define GPIO_LED_OFF				0

#define GPIO_SW1						0
#define GPIO_SW2						1

void GPIO_Init_PortA(void);
void GPIO_Init_PortF(void);

unsigned char GPIO_GetSwitchValue(unsigned char SW);
void GPIO_SetLedValue(unsigned char LedColor , unsigned char LedState);
void RGB_SetOutput(unsigned char data);
void RGB_ClearOutput(unsigned char data);

#endif
