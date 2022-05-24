#ifndef LCD_H
#define LCD_H

void LCD4bits_Init(void);
void LCD_WriteString(char * str);
void LCD4bits_Data(unsigned char data);
void LCD4bits_Cmd(unsigned char command);
void LCD4bits_Clear(void);

#endif