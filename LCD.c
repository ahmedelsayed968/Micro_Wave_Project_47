#include "C:\Keil\Labware\tm4c123gh6pm.h"
#include "SystickDriver.h"
#include "lcd.h"
#define lcd_clear 0x01
#define RS 1				 	//RS -> PB0 1
#define EN 4  		 	 	    //EN -> PB2 4


/*
 * @author ahmed elsayed 
 * 
 * */

// PB-> 	7 ,     6  ,    5 ,     4 ,     3 ,     2 , 1 , 0
// lcd->    D7 ,     D6 ,   D5  ,   D4 ,    ,       E , RW , RS
// ----------------------------------------------------------------------

// LCD commands 
/*0F	LCD ON, cursor ON
	01	Clear display screen
	02	Return home
	04	Decrement cursor (shift cursor to left)
	06	Increment cursor (shift cursor to right)
	05	Shift display right
	07	Shift display left
	0E	Display ON, cursor blinking
	80	Force cursor to beginning of first line
	C0	Force cursor to beginning of second line
	38	2 lines and 5?7 matrix
	83	Cursor line 1 position 3
	3C	Activate second line
	08	Display OFF, cursor OFF
	C1	Jump to second line, position 1
	OC	Display ON, cursor OFF
	C1	Jump to second line, position 1
	C2	Jump to second line, position 2
*/




void LCD4bits_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x02;    //enable clock for PORT B
	while((SYSCTL_PRGPIO_R & 0x02) == 0){};      //Wait to enable the clock of PORTB
    	GPIO_PORTB_DIR_R |= 0xFF;     //Set Port B Pins as Output Pins
	GPIO_PORTB_DEN_R |= 0xFF;     //Enable Port B Digital
	LCD4bits_Cmd(0x28);          //2 lines and 5x7 character (4-bit data, D4 to D7) 
	LCD4bits_Cmd(0x06);          //Automatic Increment cursor (shift cursor to right)
	LCD4bits_Cmd(lcd_clear);		 //Clear display screen
	LCD4bits_Cmd(0x0F);          //Cursor Blink
}


void LCD_Write4bits(unsigned char data, unsigned char control) //control is RS value , data coming will be in the format of 1234 0000
{
	data &= 0xF0;                       		   	//clear lower 4-bits for control 
	control &= 0x0F;                    				//clear upper 4-bits for data
	GPIO_PORTB_DATA_R = data | control;         //Include RS value (command or data ) with data 
	GPIO_PORTB_DATA_R  = data | control | EN;   //pulse EN
	delay_micro(0);													    //delay for pulsing EN
	GPIO_PORTB_DATA_R  = data | control;				//Turn off EN
	GPIO_PORTB_DATA_R  = 0;                     //Clear the Data 
}
 
void LCD4bits_Data(unsigned char data)
{
	LCD_Write4bits(data & 0xF0 , RS);   //send the Upper 4-bits
	LCD_Write4bits(data << 4 , RS);     //then the Lower 4-bits
	delay_micro(40);		  						  //Delay for LCD 
}

// iterate over the whole string to send it to the lcd character by character          
void LCD_WriteString(char * str)
{  
	
	while(*str != '\0')       	
	{
		LCD4bits_Data(*str); 
		str++;                        
	}
}
 
void LCD4bits_Cmd(unsigned char command)
{
	LCD_Write4bits(command & 0xF0 , 0);    //upper 4-bits first
	LCD_Write4bits(command << 4 , 0);      //then lower 4-bits
 
	if(command < 4)
		systick_delay_msec(2);          //commands 1 and 2 need around ~1.64ms (Check LCD Delays Table)
	else
		delay_micro(40);      //other commands take 40 us
}
 

 void LCD4bits_Clear(void){
	 		LCD4bits_Cmd(lcd_clear);
			LCD4bits_Cmd(0x80);
			delay_micro(1000);
 }
 

 
