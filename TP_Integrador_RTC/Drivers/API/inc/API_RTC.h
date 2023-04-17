#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include"stm32f4xx.h"
#include"stm32f4xx_hal_i2c.h"

typedef enum{
	RTC_inactivo,
	RTC_activo,
	RTC_set_hora,
	RTC_set_fecha,
}RTC_FSM;


void RTC_estado(char comando);
void RTC_init(); // Setea parámetros de funcionamiento del RTC
char* RTC_leer_hora(); // devuelve un string con la hora en formato| hh:mm:ss
char* RTC_leer_fecha(); // devuelve fecha en formato dd/mm/aaaa
void RTC_send_hora(char *); // acepta un string con la hora formateada y lo guarda en el RTC
void RTC_send_fecha(char *); // acepta un string con la fecha formateada
