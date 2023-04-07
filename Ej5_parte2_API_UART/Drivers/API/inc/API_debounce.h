#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define DEBOUNCE_TIME 40
typedef bool bool_t;

typedef enum{
	NC,
	ASC,
	DSC,
}flanco_PB;

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
}anti_rebote;

void debounceFSM_update(); //Actualiza la variable de estado
void debounceFSM_init(); //Inicializa la variable de estado
void buttonPressed(); //Detecta flanco de bajada
void buttonReleased(); //Detecta flanco de subida
flanco_PB readKey(); //Comprueba si el pulsador fue oprimido
