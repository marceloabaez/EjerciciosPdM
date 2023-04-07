#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct{
tick_t startTime;
tick_t duration;
bool_t running;
} delay_t;



void delayInit( delay_t * delay, tick_t duration ); //Inicia conteo de retardo
bool_t delayRead( delay_t * delay ); //Comprueba cumplimiento del tiempo de retardo
void delayWrite( delay_t * delay, tick_t duration ); //Actualiza el valor del retardo
