#include "API_debounce.h"
#include "API_delay.h"

delay_t tiempo_rebote;

void debounceFSM_update(); //Actualiza la variable de estado
void debounceFSM_init(); //Inicializa la variable de estado
void buttonPressed(); //Detecta flanco de bajada
void buttonReleased(); //Detecta flanco de subida
bool_t readKey(); //Comprueba si el pulsador fue oprimido

static int estado = BUTTON_UP; //Variable de estado de la MEF
static int estado_anterior = BUTTON_UP;
static bool_t estado_PB = 1;
static bool_t debounceState_t = 0;


//Función que comprueba si el pulsador fue oprimido, reseteándolo en dicho caso
bool_t readKey(){
	buttonPressed();
	buttonReleased();
	if(debounceState_t == 1){
		debounceState_t = 0;
		return 1;
	}
	return 0;
}


//Definición de función de MEF para debounce
void debounceFSM_update(){

	switch (estado){

	case BUTTON_UP:
		if(BSP_PB_GetState(BUTTON_USER)){
			estado = BUTTON_FALLING;
			delayInit(&tiempo_rebote, DEBOUNCE_TIME);
		}
		break;

	case BUTTON_FALLING:
		if(delayRead(&tiempo_rebote)){
			if(BSP_PB_GetState(BUTTON_USER)){
				estado = BUTTON_DOWN;
				estado_PB = 0;
			}
			else{
				estado = BUTTON_UP;
			}
			break;

	case BUTTON_DOWN:
		if(!BSP_PB_GetState(BUTTON_USER)){
			estado = BUTTON_RISING;
			delayInit(&tiempo_rebote, DEBOUNCE_TIME);
		}
		break;

	case BUTTON_RISING:
		if(delayRead(&tiempo_rebote)){
			if(!BSP_PB_GetState(BUTTON_USER)){
				estado = BUTTON_UP;
				estado_PB = 1;
			}
			else{
				estado = BUTTON_DOWN;
			}
			break;

	default:
		break;
	}

}}}

//Inicializa la variable de estado en UP
void debounceFSM_init(){
	estado = BUTTON_UP;
}

//Funciones de detección de flanco de bajada y subida. Siempre deben incluirse ambas y
//ejecutarse una tras la otra, ya que trabajan sobre una misma bandera, habilitándose mutuamente.
void buttonPressed(){
	if(estado == BUTTON_DOWN && estado_anterior == BUTTON_UP){
	debounceState_t = 1;
	estado_anterior = estado;
	}
}

void buttonReleased(){
	if(estado == BUTTON_UP && estado_anterior == BUTTON_DOWN){
	estado_anterior = estado;
}
}


