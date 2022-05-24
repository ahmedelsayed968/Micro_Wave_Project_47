#ifndef KEYPAD_H
#define KEYPAD_H
/* ^^ these are the include guards */

/* Prototypes for the functions */
/* Sums two ints */
void keypad_init();
char keypad_scan(int want_start);
void delay_micro(int n);
char checker();
#endif