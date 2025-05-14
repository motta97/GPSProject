#ifndef LCD
#define LCD



///***************** Prototypes *****************///

void PrintData(char data);
void LCD_Data(char data);
void LCD_Cmd(unsigned char cmd);
void LCD_String(char *str , char len);
void LCD_String_modified(char *str);
void LCD_Init(void);
void Pins_Init();	
	
void LCD_Char(char c);

	// RS = PD0
	// RW = PD1
	// EN = PD2
	// D0 = PA7
	// D1 = PA6
	// D2 = PA5
	// D3 = PB4
	// D4 = PE5
	// D5 = PE4
	// D6 = PE1
	// D7 = PD3
	
#endif

