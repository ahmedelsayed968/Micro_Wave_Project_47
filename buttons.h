#ifndef BUTTONS_H
#define BUTTONS_H
/* ^^ these are the include guards */

/* Prototypes for the functions */
/* Sums two ints */
void init_buttons(void);

int start(void);
int clear (void);
int get_door (void);

char start_checker();
char door_checker();	
char clear_checker();

void enable_leds();
void disable_leds();

void enable_alarm();
void disable_alarm();

#endif