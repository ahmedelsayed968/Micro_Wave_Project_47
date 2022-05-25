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
						while(1){
							LCD4bits_Clear();
							LCD_WriteString("Beef Weight?");
							if (checker()){
								char weight = keypad_scan(0);
								if(weight){
									char weightInt = weight - 48;
									if(beef(time, weightInt)){
										LCD4bits_Clear();
										LCD_WriteString("Err");
										delay1s(0);
										delay1s(0);
									} //LCDPreview("Invalid Input");
									else{
										LCD4bits_Clear();
										LCD4bits_Data(weight);
										waitforstart(time);
										break;
									}
								}else{
									break;
								}
							}
            }
					break;
					
					
					case 'C':
						while(1){
							LCD4bits_Clear();
							LCD_WriteString("Chicken Weight?");
							if (checker()){
								char weight = keypad_scan(0);
								if(weight){
									char weightInt = weight - 48;
									if(chicken(time, weightInt)){
										LCD4bits_Clear();
										LCD_WriteString("Err");
										delay1s(0);
										delay1s(0);
									} //LCDPreview("Invalid Input");
									else{
										LCD4bits_Clear();
										LCD4bits_Data(weight);
										waitforstart(time);
										break;
									}
								}else{
									break;
								}
							}
            }
					break;
					
					case 'D':	
						char phrase[]="Cooking Timer?";
						LCD4bits_Clear();
						LCD_WriteString(phrase);
						while(1){
							while(!start_checker()); // For too much time

								if(checker() && clear_checker()){
									char input = keypad_scan(1);
								if(input){
									int error = keypadInputNumber(time,input);
									if(error){
										char phrase[]="Invalid Input";
										LCD4bits_Clear();
										LCD_WriteString(phrase);
									}else{
										char currentTime []= {time[3],time[2],':',time[1],time[0]};
										timeToAscii(currentTime);				
										LCD4bits_Clear();
										LCD_WriteString(currentTime);
							//			delay1s(0);
								//		delay1s(0);
									}
								}else{
										if(start()){
											timeSet(time);
											if(time[3] < 3){
												waitforstart(time);
												break;
											}
											else if(time [3] == 3){
												if(!time[2] && !time[1] && !time[0]){
													waitforstart(time);
													break;
												}else{
													LCD4bits_Clear();
													LCD_WriteString("Too Much Time");
													timeClear(time);
												}
											}
											else{
												LCD4bits_Clear();
												LCD_WriteString("Too Much Time");
												timeClear(time);
											}
											
											
										}else{
											if(!time[3] && !time[2] && !time[1] && !time[0]){
												break;
											}
											else{
												time[3] = 0;
												time[2] = 0;
												time[1] = 0;
												time[0] = 0;
												
												char currentTime []= {time[3],time[2],':',time[1],time[0]};
												timeToAscii(currentTime);				
												LCD4bits_Clear();
												LCD_WriteString(currentTime);
											}
										}
								//	break;
								}
								}
						}
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


