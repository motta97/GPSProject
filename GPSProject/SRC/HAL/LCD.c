#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include "SysTick.h"
#include "GPIO.h"
#include "LCD.h"
#include "UART.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>




void Pins_Init(){
	// Clock of PORTA, PORTB, PORTD, PORTE
	SYSCTL_RCGCGPIO_R |=0x1B ;
	// Digitalize the datapins and config pins
	GPIO_PORTA_DEN_R |= 0xE0 ;
	GPIO_PORTB_DEN_R |= 0x10 ;
	GPIO_PORTD_DEN_R |= 0x0F ;
	GPIO_PORTE_DEN_R |= 0x32 ;
	// Direction of datapins and config pins -> Output Pins
	GPIO_PORTA_DIR_R |= 0xE0 ;
	GPIO_PORTB_DIR_R |= 0x10 ;
	GPIO_PORTD_DIR_R |= 0x0F ;
	GPIO_PORTE_DIR_R |= 0x32 ;
}

void PrintData (char data){ // data = 8 bit hexadecimal data
	// zeroth bit = D0 = PA7
	if((data&0x01) == 0x01)	{	SET_BIT(GPIO_PORTA_DATA_R,7) 	;	}
	else										{	CLR_BIT(GPIO_PORTA_DATA_R,7) 	;	}
	//First bit = D1 = PA6
	if((data&0x02) == 0x02)	{	SET_BIT(GPIO_PORTA_DATA_R,6) 	;	}
	else										{	CLR_BIT(GPIO_PORTA_DATA_R,6) 	;	}
	//Second bit = D2 = PA5
	if((data&0x04) == 0x04)	{	SET_BIT(GPIO_PORTA_DATA_R,5)	;	}
	else										{	CLR_BIT(GPIO_PORTA_DATA_R,5)	;	}
	//Third bit = D3 = PB4
	if((data&0x08) == 0x08)	{	SET_BIT(GPIO_PORTB_DATA_R,4)	;	}
	else										{	CLR_BIT(GPIO_PORTB_DATA_R,4)	;	}
	//Fourth bit = D4 = PE5
	if((data&0x10) == 0x10)	{	SET_BIT(GPIO_PORTE_DATA_R,5)	;	}
	else										{	CLR_BIT(GPIO_PORTE_DATA_R,5)	;	}
	//Fifth bit = D5 = PE4
	if((data&0x20) == 0x20)	{	SET_BIT(GPIO_PORTE_DATA_R,4)	;	}
	else										{	CLR_BIT(GPIO_PORTE_DATA_R,4)	;	}
	//Sixth bit = D6 = PB1->PE1
	if((data&0x40) == 0x40)	{	SET_BIT(GPIO_PORTE_DATA_R,1)	;	}
	else										{	CLR_BIT(GPIO_PORTE_DATA_R,1)	;	}
	//Seventh bit = D7 = PB0->PD3
	if((data&0x80) == 0x80)	{	SET_BIT(GPIO_PORTD_DATA_R,3)	;	}
	else										{	CLR_BIT(GPIO_PORTD_DATA_R,3)	;	}
}
void LCD_Data(char data){	
	
	PrintData(data);									//Pass the 8 Bit data to the datalines of LCD
	GPIO_PORTD_DATA_R &= (~(1<<1));		//Turn OFF the RW for write operation in LCD
	GPIO_PORTD_DATA_R |= (1<<0);			//Turn ON the RS for writing to the data register of LCD
	GPIO_PORTD_DATA_R |= (1<<2);			//Turn ON the En of LCD for enabling the clock of LCD
	SysTick_Wait10ms(1);						//Wait for sometime
	GPIO_PORTD_DATA_R &= (~(1<<2));		//Turn OFF the En of LCD
}

void LCD_Cmd(unsigned char cmd){
	PrintData(cmd);										//Pass the 8 Bit data to the datalines of LCD
	GPIO_PORTD_DATA_R &= (~(1<<1));		//Turn OFF the RW for write operation in LCD
	GPIO_PORTD_DATA_R &= (~(1<<0));		//Turn OFF the RS for writing to the data register of LCD
	GPIO_PORTD_DATA_R |= (1<<2);			//Turn ON the En of LCD for enabling the clock of LCD
	SysTick_Wait10ms(1);							//Wait for sometime
	GPIO_PORTD_DATA_R &= (~(1<<2));		//Turn OFF the En of LCD
}

//to print a String which is array of char we will call LCD_Data until we print all the String

void LCD_String(char *str , char len){
	char i;
	for(i=0 ; i<len ; i++){
		LCD_Data(str[i]);
		}
}
void LCD_String_modified(char *str){
	
	for( ; *str ; str++){
		LCD_Data(*str);
		}
}


void LCD_Init(void){
		Pins_Init();
	SysTick_Init();
		LCD_Cmd(0x38);		//Turn ON 8 Bit Mode
	SysTick_Wait10ms(1);	
	LCD_Cmd(0x06);		//Auto increment the cursor when prints the data in current
	SysTick_Wait10ms(1);	
	LCD_Cmd(0x0C);		//Cursor OFF and display ON
	SysTick_Wait10ms(1);	
	LCD_Cmd(0x01);		//Clear Screen
SysTick_Wait10ms(2);
}

void LCD_Char(char c) {
	LCD_Data(c);  // Send one ASCII character to LCD
}



