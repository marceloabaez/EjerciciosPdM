#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdbool.h>
#include"stm32f4xx.h"
//#include "stm32f4xx_hal_uart.h"
//#include "stm32f4xx_hal_rcc_ex.h"

typedef bool bool_t;


bool_t uartInit();
void uartSendString(uint8_t * pstring);
//void uartSendStringSize(uint8_t * pstring, 20);
//void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
