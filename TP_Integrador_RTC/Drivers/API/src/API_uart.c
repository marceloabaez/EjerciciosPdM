#include "API_uart.h"

#define uart_ok "\n\n\rInicializacion correcta\r\n"
#define uart_failed "\n\n\rFallo inicializacion\r\n"
#define init_msg "Comunicación UART 9600, 8N1, HwC_OFF, Tx-Rx, OS_16\n\n\r"
typedef bool bool_t;

UART_HandleTypeDef UartHandle;
uint32_t uart_delay = 100;

//Inicializa la UART y envía por UART confirmación de inicialización y parámetros
bool_t uartInit(){
	UartHandle.Instance        = USART3;
	UartHandle.Init.BaudRate   = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;


	if (HAL_UART_Init(&UartHandle) != HAL_OK){
		uartSendString((uint8_t *) uart_failed);
		return 1;
	}
	uartSendString((uint8_t *) uart_ok);
	uartSendString((uint8_t *) init_msg);
	return 0;
}

//Envía un string por UART
void uartSendString(uint8_t * pstring){
	uint16_t len = ((uint16_t) strlen((const char *)pstring));
	HAL_UART_Transmit(&UartHandle, pstring, len, uart_delay);
	return;
}

//Envía una cantidad "size" de elementos de un string
void uartSendStringSize(uint8_t * pstring, uint16_t size){
	if(size <= strlen((const char *) pstring)){
	HAL_UART_Transmit(&UartHandle, pstring, size, uart_delay);
}	else{
	uartSendString((uint8_t *) "Caracteres > longitud del string");
}
	return;
}


//void uartReceiveStringSize(uint8_t * pstring, uint16_t size){}
