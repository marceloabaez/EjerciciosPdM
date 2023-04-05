#include "API_uart.h"

#define uart_ok "Inicializacion correcta\r\n"
#define uart_failed "Fallo inicializacion\r\n"
typedef bool bool_t;

UART_HandleTypeDef UartHandle;
uint32_t uart_delay = 1000;
char pstring[100];

//Inicializa la UART;
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

		return 1;
	}
	//uartSendString((uint8_t *) uart_failed);
	return 0;
}

void uartSendString(uint8_t * pstring){
	uint16_t len = (uint16_t) strlen((char *)pstring);
	HAL_UART_Transmit(&UartHandle, pstring, 28, uart_delay);
}


void uartSendStringSize(uint8_t * pstring, uint16_t size){
	if(size <= strlen((const char *) pstring)){
	HAL_UART_Transmit(&UartHandle, pstring, size, uart_delay);
}	else{
	uartSendString((uint8_t *) "La cantidad de caracteres debe ser menor que la longitud del string");
}
}


//void uartReceiveStringSize(uint8_t * pstring, uint16_t size){}
