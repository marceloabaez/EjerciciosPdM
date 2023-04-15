/*
P0: RS
P1: RW
P2: CS
P3: P3
P4: DB4
P5: DB5
P6: DB6
P7: DB7
*/

#include "API_LCD.h"

#define LCD_ADD 0b01001110
#define LCD_SET 0b00101000
#define LCD_CLR 0b00000001
#define LCD_RET 0b00000010

#define LCD_EN_RS0 0b00100000
#define LCD_DIS_RS0 0b00000000
#define LCD_EN_RS1 0b10100000
#define LCD_DIS_RS1 0b10000000

#define LCD_POS_00 0x00
#define LCD_POS_10 0x40

#define demora 1

extern I2C_HandleTypeDef hi2c1;

void LCD_init(){
	uint8_t msg = LCD_SET;
	uint8_t msg_upper = 0;
	uint8_t buf = 0;
	msg_upper = msg >> 4;
	buf = (msg_upper | LCD_EN_RS0);
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADD, &buf, 1, 20);
	HAL_Delay(demora);
	buf = (msg_upper | LCD_DIS_RS0);
	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADD, &buf, 1, 20);
	HAL_Delay(demora);
	LCD_send(LCD_SET, 0);


}

void LCD_clear(){
	LCD_send(LCD_CLR, 0);
}

void LCD_row_0(){
	LCD_send(LCD_POS_00, 0);
}

void LCD_row_1(){
	LCD_send(LCD_POS_10,0);
}


void LCD_send(uint8_t msg, bool RS){
uint8_t buf = 0;
uint8_t LCD_EN;
uint8_t LCD_DIS;
uint8_t msg_lower = 0;
uint8_t msg_upper = 0;
if(RS){
LCD_EN = 0b10100000;
LCD_DIS = 0b10000000;
}else{
LCD_EN = 0b00100000;
LCD_DIS = 0b00000000;
}

msg_lower = (msg & 0b00001111);
msg_upper = msg >> 4;
buf = msg_upper | LCD_EN;
HAL_I2C_Master_Transmit(&hi2c1, LCD_ADD, &buf, 1, 20);
HAL_Delay(demora);
buf = msg_upper | LCD_DIS;
HAL_I2C_Master_Transmit(&hi2c1, LCD_ADD, &buf, 1, 20);
HAL_Delay(demora);
buf = msg_lower | LCD_EN;
HAL_I2C_Master_Transmit(&hi2c1, LCD_ADD, &buf, 1, 20);
HAL_Delay(demora);
buf = msg_lower | LCD_DIS;
HAL_I2C_Master_Transmit(&hi2c1, LCD_ADD, &buf, 1, 20);
HAL_Delay(demora);
}
