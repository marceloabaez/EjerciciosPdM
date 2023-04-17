#include "API_RTC.h"
#include "API_uart.h"
//#include "API_RTC_port.c"

#define RTC_ADD 0b11010000 // dirección I2C del RTC
#define RTC_CTRL_REG 0x0E	// dirección del registro de control del RTC
#define RTC_CTRL_INIT 0b00000100	// byte de configuración inicial del registro de control
#define RTC_STAT_INIT 0b00000000
#define RTC_TIME_ADD 0x00 // dirección del registro de segundos
#define RTC_DATE_ADD 0x04 // dirección del registro de día

char fecha_i[] = "15/04/23";
char hora_i[] = "20:45:15";
char salto[] = "\n\r";
char espacio[] = "  ";

uint8_t hora [3];
uint8_t fecha [3];

void I2C_Read(uint16_t i2c_add, uint16_t mem_add, uint16_t size);
void I2C_Write(uint16_t i2c_add, uint16_t mem_add, uint16_t size);

static int estado = RTC_inactivo;
uint8_t opcion = 0;
uint8_t buff[20];
static char i2c_msg[20];


// Setea parámetros de funcionamiento del RTC
void RTC_init(){
estado = RTC_activo;
buff[0] = RTC_CTRL_INIT;
buff[1] = RTC_STAT_INIT;
I2C_Write(RTC_ADD, RTC_CTRL_REG, 2);
RTC_send_fecha(fecha_i);
RTC_send_hora(hora_i);
}

void RTC_estado(char comando){
	switch(estado){

	case RTC_activo:
		RTC_leer_hora();
		uartSendString(i2c_msg);
		uartSendString(espacio);
		RTC_leer_fecha();
		uartSendString(i2c_msg);
		uartSendString(salto);

		if (comando == 'A'){
			estado = RTC_set_hora;
			opcion = 0;
			comando = '\0';
		}
		if (comando == 'B'){
			estado = RTC_set_fecha;
			opcion = 0;
			comando = '\0';
		}

		break;

	case  RTC_set_hora:
		RTC_leer_hora();
		if (comando == '2'){
			hora[opcion]++;
		}
		if (comando == '8'){
			hora[opcion]--;
		}
		if (comando == '6'){
			if(opcion < 2){
				opcion++;
			}
		}
		if (comando == '2'){
			if(opcion > 0){
				opcion--;
			}
		}
		RTC_leer_hora();
		uartSendString(i2c_msg);
		uartSendString(salto);
		if (comando == 'A'){
			estado = RTC_activo;
			comando = '\0';
		}
		break;

	case RTC_set_fecha:
		RTC_leer_fecha();
		if (comando == '2'){
			fecha[opcion]++;
		}
		if (comando == '8'){
			fecha[opcion]--;
		}
		if (comando == '6'){
			if(opcion < 2){
				opcion++;
			}
		}
		if (comando == '2'){
			if(opcion > 0){
				opcion--;
			}
		}
		RTC_leer_fecha();
		uartSendString(i2c_msg);
		uartSendString(salto);
		if (comando == 'B'){
			estado = RTC_activo;
			comando = '\0';
			break;
				}

		break;

	default:



		break;
	}

}

// devuelve un string con la hora en formato| hh:mm:ss
char* RTC_leer_hora(){
//HAL_I2C_Mem_Read(&hi2c1, RTC_ADD, RTC_TIME_ADD, 1, buff, 3, I2C_TO);
I2C_Read(RTC_ADD, RTC_TIME_ADD, 3);
hora[0] = (buff[0] >> 4)* 10 + (buff[0] & 0b00001111);
hora[1] = (buff[1] >> 4)* 10 + (buff[1] & 0b00001111);
hora[2] = ((buff[2] >> 4)& 0b00000011)* 10 + (buff[2] & 0b00001111);
sprintf(i2c_msg, "%hd:%hd:%hd", hora[2], hora[1], hora[0]);
return(i2c_msg);
}

// devuelve fecha en formato dd/mm/aaaa
char* RTC_leer_fecha(){
//HAL_I2C_Mem_Read(&hi2c1, RTC_ADD, RTC_DATE_ADD, 1, buff, 3, I2C_TO);
I2C_Read(RTC_ADD, RTC_DATE_ADD, 3);
fecha[0] = (buff[0] >> 4)* 10 + (buff[0] & 0b00001111);
fecha[1] = ((buff[1] >> 4) & 0b00000011)* 10 + (buff[1] & 0b00001111);
fecha[2] = (buff[2] >> 4)* 10 + (buff[2] & 0b00001111);
sprintf(i2c_msg, "%hd/%hd/%hd", fecha[0], fecha[1], fecha[2]);
return(i2c_msg);
}

// acepta un string con la hora formateada y lo guarda en el RTC
void RTC_send_hora(char * i2c_msg){
uint8_t decenas;
hora[2] = (i2c_msg[0] - '0')*10 + (i2c_msg[1] - '0');
hora[1] = (i2c_msg[3] - '0')*10 + (i2c_msg[4] - '0');
hora[0] = (i2c_msg[6] - '0')*10 + (i2c_msg[7] - '0');
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
	uint8_t decenas = 0;
	fecha[0] = (i2c_msg[0] - '0')*10 + (i2c_msg[1] - '0');
	fecha[1] = (i2c_msg[3] - '0')*10 + (i2c_msg[4] - '0');
	fecha[2] = (i2c_msg[6] - '0')*10 + (i2c_msg[7] - '0');
	decenas = fecha[0] / 10;
	buff[0] = (decenas << 4) + (fecha[0] - decenas * 10);
	decenas = fecha[1] / 10;
	buff[1] = (decenas << 4) + (fecha[1] - decenas * 10);
	decenas = fecha[2] / 10;
	buff[2] = (decenas << 4) + (fecha[2] - decenas * 10);
	I2C_Write(RTC_ADD, RTC_DATE_ADD, 3);
}
