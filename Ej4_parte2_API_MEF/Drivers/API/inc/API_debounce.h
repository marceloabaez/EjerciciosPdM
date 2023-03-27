#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define DEBOUNCE_TIME 40

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
tick_t startTime;
tick_t duration;
bool_t running;
} delay_t;

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
void delayInit( delay_t * delay, tick_t duration ); //Inicia conteo de retardo
bool_t delayRead( delay_t * delay ); //Comprueba cumplimiento del tiempo de retardo
void delayWrite( delay_t * delay, tick_t duration ); //Actualiza el valor del retardo
bool_t readKey(); //Comprueba si el pulsador fue oprimido
