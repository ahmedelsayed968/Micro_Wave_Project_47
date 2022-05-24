#include <TM4C123.h>
#include "C:\Users\user\Downloads\tm4c123gh6pm.h"
#include "buttons.h"
#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08

void init_buttons(void){
// set clock to turn on the port
SYSCTL_RCGCGPIO_R |=0x21;
// set delay to let the clock reaches the port
while((SYSCTL_PRGPIO_R & 0x2) == 0){}//wait to make sure that port is activated
GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock PortF PF0

GPIO_PORTF_CR_R |= 0x11; // allow changes to PF4-0
GPIO_PORTA_CR_R |= 0x1C; // allow changes to PF4-0
	
GPIO_PORTF_AMSEL_R &= ~(0x11); // 3) disable analog function
GPIO_PORTA_AMSEL_R &= ~(0x1C); // 3) disable analog function

GPIO_PORTF_PCTL_R |=~(0x11) ; // 4) GPIO clear bit PCTL
GPIO_PORTA_PCTL_R |=~(0x1C) ; // 4) GPIO clear bit PCTL

GPIO_PORTF_DIR_R = 0x00; // 5) PF4,PF0 input, PF3,PF2,PF1 output
GPIO_PORTA_DIR_R = 0x18; // 5) PF4,PF0 input, PF3,PF2,PF1 output

GPIO_PORTF_AFSEL_R &= ~(0x11); // 6) no alternate function
GPIO_PORTA_AFSEL_R &= ~(0x1C); // 6) no alternate function

GPIO_PORTF_PUR_R = 0x11; // enable pullup resistors on PF4,PF0
GPIO_PORTA_PUR_R = 0x1C; // enable pullup resistors on PF4,PF0

GPIO_PORTF_DEN_R |= 0x1F;
GPIO_PORTA_DEN_R |= 0x1C;


GPIO_PORTF_DATA_R |= 0x00;
GPIO_PORTA_DATA_R |= 0x04;

}

int start(void){
	return (GPIO_PORTF_DATA_R & 0x11) == 0x10; //PF0
}
int clear (void){
	return (GPIO_PORTF_DATA_R & 0x11) == 0x01; // PF4
}
int get_door (void){
	return (GPIO_PORTA_DATA_R & 0x04) == 0x00; //PA2
}
char clear_checker(){
	unsigned char col = GPIO_PORTF_DATA_R & 0x10; 	// read columns
	delay_micro(2);
	return col == 0x10;
}	

char door_checker(){
	unsigned char col = GPIO_PORTA_DATA_R & 0x04; 	// read columns
	delay_micro(2);
	return col == 0x04;
}
char start_checker(){
	unsigned char col = GPIO_PORTF_DATA_R & 0x01; 	// read columns
	delay_micro(2);
	return col == 0x01;
}	

void enable_leds(){
	GPIO_PORTA_DATA_R |= 0x08; //PA3
}
void disable_leds(){
	GPIO_PORTA_DATA_R &= ~(0x08);
}
void enable_alarm(){
	GPIO_PORTA_DATA_R |= 0x10; //PA4
}
void disable_alarm(){
	GPIO_PORTA_DATA_R &= ~(0x10);
}