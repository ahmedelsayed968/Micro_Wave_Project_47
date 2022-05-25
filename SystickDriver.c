#include "SystickDriver.h"
#include "C:\Keil\Labware\tm4c123gh6pm.h"

void delay_micro(int n){
    int i;
    for(i=0;i<n;i++){
        SysTick_Wait(80);
    }
    
}
 
//systick delay functions
void SysTick_Wait(unsigned long delay) // delay = number of ticks
{
    NVIC_ST_CTRL_R = 0X00;
    NVIC_ST_RELOAD_R = delay - 1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0X05; // ENABLE TIMER AND CLK SRC
    while((NVIC_ST_CTRL_R&0x00010000)==0) 
    {}
}
 
void SysTick_Wait1ms(){
    SysTick_Wait(16000);
}

void systick_delay_msec(int t) //delay by milli seconds.
{
    int i; 
    for(i=0; i<t; i++)
    {
        SysTick_Wait1ms();
    }
}