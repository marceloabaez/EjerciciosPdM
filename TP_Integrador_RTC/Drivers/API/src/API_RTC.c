#include <API_RTC.h>

#define RTC_ADD 0b11010000 // dirección I2C del RTC
#define RTC_CTRL_REG 0x0E	// dirección del registro de control del RTC
#define RTC_CTRL_INIT 0b	// byte de configuración inicial del registro de control
#define RTC_TIME_ADD 0x00 // dirección del registro de segundos
#define RTC_DATE_ADD 0x04 // dirección del registro de día
#define I2C_TO 50 // Timeout de la comunicación I2C

uint8_t segundos;
uint8_t minutos;
uint8_t horas;

uint8_t dia;
uint8_t mes;
uint8_t anio;


static int estado = RTC_inactivo;
static uint8_t buff[20];
static char i2c_msg[20];

// Setea parámetros de funcionamiento del RTC
void RTC_init(){
estado = RTC_activo;
HAL_I2C_Mem_Write(&hi2c1,RTC_ADD);

}

void RTC_estado(){


}

// devuelve un string con la hora en formato| hh:mm:ss
char* RTC_leer_hora(){
HAL_I2C_Mem_Read(&hi2c1, RTC_ADD, RTC_TIME_ADD, 1, buff, 3, I2C_TO);
segundos = (buff[0] >> 4)* 10 + (buff[0] & 0b00001111);
minutos = (buff[1] >> 4)* 10 + (buff[1] & 0b00001111);
horas = ((buff[2] >> 4)& 0b00000011)* 10 + (buff[2] & 0b00001111);
sprintf(i2c_msg, "%hd:%hd:%hd", horas, minutos, segundos);
return(i2c_msg);
}

// devuelve fecha en formato dd/mm/aaaa
char* RTC_leer_fecha(){
HAL_I2C_Mem_Read(&hi2c1, RTC_ADD, RTC_DATE_ADD, 1, buff, 3, I2C_TO);
dia = (buff[0] >> 4)* 10 + (buff[0] & 0b00001111);
mes = ((buff[1] >> 4) & 0b00000011)* 10 + (buff[1] & 0b00001111);
anio = (buff[2] >> 4)* 10 + (buff[2] & 0b00001111);
sprintf(i2c_msg, "%hd:%hd:%hd", dia, mes, anio);
return(i2c_msg);
}

// acepta un string con la hora formateada y lo guarda en el RTC
void RTC_send_hora(char * i2c_msg){
uint8_t decenas;
horas = (i2c_msg[0] - '0')*10 + (i2c_msg[1] - '0');
minutos = (i2c_msg[3] - '0')*10 + (i2c_msg[4] - '0');
segundos = (i2c_msg[6] - '0')*10 + (i2c_msg[7] - '0');
decenas = horas / 10;
buff[2] = (decenas << 4) + (horas - decenas);
decenas = minutos / 10;
buff[1] = (decenas << 4) + (minutos - decenas);
decenas = segundos / 10;
buff[0] = (decenas << 4) + (segundos - decenas);
HAL_I2C_Mem_Write(&hi2c1, RTC_ADD, RTC_TIME_ADD, 1, buff, 3, I2C_TO);
return 0;
}

// acepta un string con la fecha formateada
void RTC_send_fecha(char * i2c_msg){
	uint8_t decenas;
	dia = (i2c_msg[0] - '0')*10 + (i2c_msg[1] - '0');
	mes = (i2c_msg[3] - '0')*10 + (i2c_msg[4] - '0');
	anio = (i2c_msg[6] - '0')*10 + (i2c_msg[7] - '0');
	buff[0] = (decenas << 4) + (dia - decenas);
	decenas = anios / 10;
	buff[1] = (decenas << 4) + (mes - decenas);
	decenas = segundos / 10;
	buff[2] = (decenas << 4) + (anios - decenas);
	decenas = minutos / 10;
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADD, RTC_DATE_ADD, 1, buff, 3, I2C_TO);
	return 0;
}
