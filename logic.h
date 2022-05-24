#ifndef LOGIC_H
#define LOGIC_H
int keypadInputNumber(int*  time, int input);
int popCorn(int* time);
int beef(int* time, int weight);
int chicken(int* time, int weight);
int timeDecrement(int* time);
void timeToAscii(char* time);
int timeClear(int* time);
void timeSet(int* time);
#endif
