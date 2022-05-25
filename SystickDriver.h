#ifndef _H_SYSTICKDRIVER_
#define _H_SYSTICKDRIVER
void delay_micro(int n);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait1ms();
void systick_delay_msec(int t);

#endif