#include "numpad_4x4.h"
#include <stdbool.h>

#define delay_GPIO 1 // Si es necesario debería reemplazarse con un delay mucho mas pequeño
#define PORT GPIOE // Todos los pines deben pertenecer a un mismo puerto

//Completar con símbolos de salida del teclado
const char buttons [4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
//Completar con los pines de salida
const uint16_t row_pins [4] = {GPIO_PIN_15, GPIO_PIN_14, GPIO_PIN_12, GPIO_PIN_10};
//Completar con los pines de entrada
const uint16_t column_pins [4] = {GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_11, GPIO_PIN_9};


//Inicializa 8 pines del puerto PORT, 4 como entradas y 4 como salidas.
void GPIO_init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOE_CLK_ENABLE();

	//Inicialización de pines de salida
	HAL_GPIO_WritePin(PORT, GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PORT, &GPIO_InitStruct);

	//Inicialización de pines de entrada
	GPIO_InitStruct.Pin = (GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_9);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PORT, &GPIO_InitStruct);

}

// Devuelve caracter presionado en el teclado 4x4, no admite pulsaciones dobles
// por defecto devuelve NULL
char PressedKey_4x4(){
	int i = 0;
	int j = 0;
	for(i=0; i<4; i++){
		HAL_GPIO_WritePin(PORT, row_pins[i], GPIO_PIN_SET);
		HAL_Delay(delay_GPIO);
		for(j=0; j<4; j++){
			if(HAL_GPIO_ReadPin(PORT, column_pins[j])){
				HAL_GPIO_WritePin(PORT, row_pins[i], GPIO_PIN_RESET);
				return buttons[i][j];
			}
		}
		HAL_GPIO_WritePin(PORT, row_pins[i], GPIO_PIN_RESET);
	}
	return '\n';
	}


/*
char PressedKey_4x4(){
 //Primera fila
	bool a = 0;
	char key = '\0';
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_Delay(1);
	a = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8)){
		key = '2';
	}
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9)){
		key = 'A';
	}
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);

	// Segunda fila
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7)){
		key = '4';
	}
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)){
		key = '6';
	}
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9)){
		key = 'B';
	}
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);

	//Tercera fila
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(1);
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8)){
		key = '8';
	}
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9)){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
		key = 'C';
	}
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);

return key;
}    */
