//Driver para RTC DS3231

#include "API_RTC.h"
#include "API_uart.h"
//#include "API_RTC_port.c"

#define RTC_ADD 0b11010000 // dirección I2C del RTC
#define RTC_CTRL_REG 0x0E	// dirección del registro de control del RTC
#define RTC_CTRL_INIT 0b00000100   // byte de configuración inicial del registro de control
#define RTC_STAT_INIT 0b00000000   // byte de configuración inicial del registro stat
#define RTC_TIME_ADD 0x00 // dirección del registro de segundos
#define RTC_DATE_ADD 0x04 // dirección del registro de día

typedef enum{
	RTC_inactivo,
	RTC_activo,
	RTC_set_hora,
	RTC_set_fecha,
}RTC_FSM;

char fecha_i[] = "15/04/23"; //Fecha inicial utilizada porque la bateria esta agotada
char hora_i[] = "20:45:15"; //Hora inicial utilizada porque la bateria está agotada

//Strings para formatear la salida
char salto[] = "\n\r";
char espacio[] = "  ";
char espacio_largo[] = "          ";
char error_RTC[] = "\n\rEstado invalido de RTC\n\r";

static uint8_t hora [3];
static uint8_t fecha [3];
static int estado = RTC_inactivo;
static char i2c_msg[20];
static uint8_t opcion = 0;

uint8_t buff[20];


void I2C_Read(uint16_t i2c_add, uint16_t mem_add, uint16_t size);
void I2C_Write(uint16_t i2c_add, uint16_t mem_add, uint16_t size);
static char* RTC_leer_hora(); // devuelve un string con la hora en formato| hh:mm:ss
static char* RTC_leer_fecha(); // devuelve fecha en formato dd/mm/aaaa
static void RTC_send_hora(char *); // acepta un string con la hora formateada y lo guarda en el RTC
static void RTC_send_fecha(char *); // acepta un string con la fecha formateada


// Setea parámetros de funcionamiento del RTC
void RTC_init(){
estado = RTC_inactivo;
buff[0] = RTC_CTRL_INIT;
buff[1] = RTC_STAT_INIT;
I2C_Write(RTC_ADD, RTC_CTRL_REG, 1);
RTC_send_fecha(fecha_i);
RTC_send_hora(hora_i);
}


// MEF de estados del RTC
void RTC_estado(char comando){
	switch(estado){

	case RTC_inactivo:
		if (comando == 'D'){
			estado = RTC_activo;
		}
		break;

	case RTC_activo:
		RTC_leer_hora();
		uartSendString(i2c_msg);
		uartSendString(espacio);
		RTC_leer_fecha();
		uartSendString(i2c_msg);
		uartSendString(salto);
		if (comando == 'D'){
			estado = RTC_inactivo;
			comando = '\0';
		}
		if (comando == 'A'){
			estado = RTC_set_hora;
			RTC_leer_hora();
			opcion = 2;
			comando = '\0';
		}
		if (comando == 'B'){
			estado = RTC_set_fecha;
			RTC_leer_fecha();
			opcion = 0;
			comando = '\0';
		}

		break;

	case  RTC_set_hora:
		//RTC_leer_hora();
		if (comando == '2'){
			// Impide setear hora a valores sobre el rango correcto
			if(((opcion == 2) && (hora[opcion] < 23)) | ((opcion == 1) && (hora[opcion] < 59)) | ((opcion == 0) && (hora[opcion] < 59))){
				hora[opcion]++;
			}
			else {
				hora[opcion] = 0;
			}
			sprintf(i2c_msg, "%02hd:%02hd:%02hd", hora[2], hora[1], hora[0]);
		}

		if (comando == '8'){
			// Impide desborde por debajo a valores fuera del rango horario
			if(hora[opcion] > 0){
			hora[opcion]--;
			}
			else if ((opcion == 0) | (opcion == 1)){
				hora[opcion] = 59;
			}
			else{
				hora[opcion] = 23;
			}

			sprintf(i2c_msg, "%02hd:%02hd:%02hd", hora[2], hora[1], hora[0]);
		}

		if (comando == '6'){
			if(opcion > 0){
				opcion--;
			}
		}
		if (comando == '4'){
			if(opcion < 2){
				opcion++;
			}
		}
		uartSendString(i2c_msg);
		uartSendString(salto);
		if (comando == 'C'){
			estado = RTC_activo;
			RTC_send_hora(i2c_msg);
			comando = '\0';
		}
		break;

	case RTC_set_fecha:
		if (comando == '2'){
			// Impide setear fecha a valores sobre el rango correcto
			if(((opcion == 0) && (fecha[opcion] < 31)) | ((opcion == 1) && (fecha[opcion] < 12)) | ((opcion == 2) && (fecha[opcion] < 99))){
				fecha[opcion]++;
			}
			else if((opcion == 0) || (opcion == 1)){
				fecha[opcion] = 1;
			}
			else{
				fecha[opcion] = 0;
			}
			sprintf(i2c_msg, "%02hd/%02hd/%02hd", fecha[0], fecha[1], fecha[2]);
		}
		if (comando == '8'){
			// Impide setear hora a valores bajo el rango correcto y desbordes por abajo
			if(((opcion == 0) && (fecha[opcion] > 1)) | ((opcion == 1) && (fecha[opcion] > 1)) | ((opcion == 2) && (fecha[opcion] > 0))){
				fecha[opcion]--;
			}
			else if(opcion == 0){
				fecha[opcion]= 31;
			}
			else if(opcion == 1){
				fecha[opcion]= 12;
			}
			else{
				fecha[opcion]= 99;
			}
			sprintf(i2c_msg, "%02hd/%02hd/%02hd", fecha[0], fecha[1], fecha[2]);
		}
		if (comando == '6'){
			if(opcion < 2){
				opcion++;
			}
		}
		if (comando == '4'){
			if(opcion > 0){
				opcion--;
			}
		}
		uartSendString(espacio_largo);
		uartSendString(i2c_msg);
		uartSendString(salto);
		if (comando == 'C'){
			estado = RTC_activo;
			RTC_send_fecha(i2c_msg);
			comando = '\0';
			break;
				}

		break;

	default:
		uartSendString(error_RTC);
		while(1);
		break;
	}

}

// devuelve un string con la hora en formato hh:mm:ss
char* RTC_leer_hora(){
I2C_Read(RTC_ADD, RTC_TIME_ADD, 3); // Carga hora actual del RTC para editarla
// Conversión de BCD (formato de almacenamiento del RTC) a entero
hora[0] = (buff[0] >> 4)* 10 + (buff[0] & 0b00001111);
hora[1] = (buff[1] >> 4)* 10 + (buff[1] & 0b00001111);
hora[2] = ((buff[2] >> 4)& 0b00000011)* 10 + (buff[2] & 0b00001111);
sprintf(i2c_msg, "%02hd:%02hd:%02hd", hora[2], hora[1], hora[0]);
return(i2c_msg);
}

// devuelve fecha en formato dd/mm/aaaa
char* RTC_leer_fecha(){
I2C_Read(RTC_ADD, RTC_DATE_ADD, 3); // Lee fecha del RTC
// Conversión de BCD (formato de almacenamiento del RTC) a entero
fecha[0] = (buff[0] >> 4)* 10 + (buff[0] & 0b00001111);
fecha[1] = ((buff[1] >> 4) & 0b00000011)* 10 + (buff[1] & 0b00001111);
fecha[2] = (buff[2] >> 4)* 10 + (buff[2] & 0b00001111);
sprintf(i2c_msg, "%02hd/%02hd/%02hd", fecha[0], fecha[1], fecha[2]);
return(i2c_msg);
}

// acepta un string con la hora formateada y lo guarda en el RTC
void RTC_send_hora(char * i2c_msg){
// Individualización de parámetros
uint8_t decenas;
hora[2] = (i2c_msg[0] - '0')*10 + (i2c_msg[1] - '0');
hora[1] = (i2c_msg[3] - '0')*10 + (i2c_msg[4] - '0');
hora[0] = (i2c_msg[6] - '0')*10 + (i2c_msg[7] - '0');
// Conversión de entero a BCD (formato de almacenamiento del RTC)
decenas = hora[2] / 10;
buff[2] = (decenas << 4) + (hora[2] - decenas*10);
decenas = hora[1] / 10;
buff[1] = (decenas << 4) + (hora[1] - decenas*10);
decenas = hora[0] / 10;
buff[0] = (decenas << 4) + (hora[0] - decenas*10);
I2C_Write(RTC_ADD, RTC_TIME_ADD, 3);
}

// acepta un string con la fecha formateada
void RTC_send_fecha(char * i2c_msg){
	// Invividualización de parámetros
	uint8_t decenas = 0;
	fecha[0] = (i2c_msg[0] - '0')*10 + (i2c_msg[1] - '0');
	fecha[1] = (i2c_msg[3] - '0')*10 + (i2c_msg[4] - '0');
	fecha[2] = (i2c_msg[6] - '0')*10 + (i2c_msg[7] - '0');
	// Conversión de entero a BCD (formato de almacenamiento del RTC)
	decenas = fecha[0] / 10;
	buff[0] = (decenas << 4) + (fecha[0] - decenas * 10);
	decenas = fecha[1] / 10;
	buff[1] = (decenas << 4) + (fecha[1] - decenas * 10);
	decenas = fecha[2] / 10;
	buff[2] = (decenas << 4) + (fecha[2] - decenas * 10);
	I2C_Write(RTC_ADD, RTC_DATE_ADD, 3);
	HAL_Delay(1000);
}
