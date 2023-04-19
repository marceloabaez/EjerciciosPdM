#include "API_delay.h"

// Actualiza el retardo y resetea la bandera del contador
void delayInit( delay_t * delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
}

//Si la bandera está alta resetea el tiempo de inicio, si está baja comprueba el
//tiempo transcurrido, si se ha cumplido levanta la bandera

bool_t delayRead( delay_t * delay ){
	if(delay->running == false){
		delay->startTime = HAL_GetTick();
		delay->running = true;
		return 0;}
	else {
		if((HAL_GetTick()-delay->startTime) >= delay->duration){
			delay->running = false;
			return(1);
		}
		else{
			return 0;
		}}}

//Actualiza el delay del retardo
void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration = duration;}
