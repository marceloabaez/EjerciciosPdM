#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include"stm32f4xx.h"
#include"stm32f4xx_hal_i2c.h"

void LCD_init();
void LCD_clear();
void LCD_row_0();
void LCD_row_1();
void LCD_send(uint8_t msg, bool RS);
