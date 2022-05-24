#include "keypad.h"
#include "buttons.h"
#include "lcd.h"
#include "logic.h"
#include "C:\Users\user\Downloads\tm4c123gh6pm.h"


#define lcd_clear 0x01

void startCook(int* time);
void waitforstart(int* time);
int delay1Second(void);
int delay(unsigned long delay, int cooking);
int delay1ms(int cooking);
int delay1s(int cooking);
void end();

int main(void){

	LCD4bits_Init();
	keypad_init();
	init_buttons();


	while(1){
		disable_leds();
		disable_alarm();

		LCD4bits_Clear();

		LCD_WriteString("Choose Program");

		int time []= {0,0,0,0};

		if(checker()){
			char value = keypad_scan(0);
			if(value != 0){
				switch(value){
					case 'A':
						popCorn(time);

					  LCD4bits_Clear();
						LCD_WriteString("Pop Corn");
						waitforstart(time);
						break;

					case 'B':
					    break;


					case 'C':
					    break;

					case 'D':
				}
			}
		}
	}
}

void waitforstart(int* time){
    while(1){

        if(start()){
						  if(!get_door()){
              startCook(time);
              if(!time[0] && !time[1] && !time[2] && !time[3]){
									end();
								 break;
							}else{
								while(1){
									while(!clear_checker());
										disable_leds();
										if(delay1s(0))break;
										enable_leds();
										if(delay1s(0))break;
								}
							}
            }
            else{
							LCD4bits_Clear();
							LCD_WriteString("Close The Door");
						}
        }

        else if(clear()){
					 break;
				}

    }
}


void startCook(int* time){
		enable_leds();
		char currentTime []= {time[3],time[2],':',time[1],time[0]};
		timeToAscii(currentTime);
		LCD4bits_Clear();
		LCD_WriteString(currentTime);

    while(timeDecrement(time)){


        if(delay1s(1)) break;//will return 1 if door opened or pause clicked


				char currentTime []= {time[3],time[2],':',time[1],time[0]};
				timeToAscii(currentTime);
				LCD4bits_Clear();
				LCD_WriteString(currentTime);

    }

}


int delay(unsigned long delay, int cooking){ // delay = number of ticks
NVIC_ST_CTRL_R = 0X00;
NVIC_ST_RELOAD_R = delay - 1;
NVIC_ST_CURRENT_R = 0;
NVIC_ST_CTRL_R = 0X05; // ENABLE TIMER AND CLK SRC
while((NVIC_ST_CTRL_R&0x00010000)==0)
{
//wait for count flag
	if(clear()) return 1;
	if(cooking && get_door()) return 1;
	if(!cooking && start()) return 1;
}
return 0;
}



int delay1ms(int cooking){
 return delay(16000,cooking);
}


int delay1s(int cooking){ //delay by milli seconds.
	for(int i = 0; i < 1000; i++){
		if(delay1ms(cooking)) return 1;
	}
	return 0;
}

int delay_half_second(int cooking){ //delay by milli seconds.
	for(int i = 0; i < 500; i++){
		if(delay1ms(cooking)) return 1;
	}
	return 0;
}


void end(){
	while(1){
		LCD4bits_Clear();
		LCD_WriteString("DONE");
		enable_alarm();
		disable_leds();
		if(delay_half_second(0))break;
		enable_leds();
		disable_alarm();
		if(delay_half_second(0))break;
		disable_leds();
		enable_alarm();
		if(delay_half_second(0))break;
		enable_leds();
		disable_alarm();
		if(delay_half_second(0))break;
		disable_leds();
		enable_alarm();
		if(delay_half_second(0))break;
		enable_leds();
		disable_alarm();
		if(delay_half_second(0))break;
		break;
	}
}


