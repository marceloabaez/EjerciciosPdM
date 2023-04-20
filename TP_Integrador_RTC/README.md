- Proyecto El proyecto se basa en la comunicación entre la placa Nucleo con un Real Time Clock 
(RTC), más precisamente el DS3231, mediante protocolo I2C. Se emplea una MEF para poder definir 
distintos tipos de estados en los que puede operar el mismo (inactivo, activo, seteo de horario
y seteo de calendario). Los datos leídos del RTC y a grabar en él se envían al puerto serie de
la PC mediante protocolo UART. Para la elección entre los distintos estados del RTC; y la 
navegación y seteo de los parámetros del mismo, se empleó un teclado matricial 4x4.

- Archivos clave:
API_RTC.c Manejo del RTC e implementación de su MEF
API_RTC_port.c Wrapper de las funciones de la HAL que se comunucan con el RTC por I2C
API_numpad_4x4 Driver del teclado 4x4
API_uart.c Envío de mensajes al puerto serie de la PC

- Para consultas y sugerencias sobre el proyecto puede contactarse por correo electrónico a
juanperez1234@gmail.com

- Proyecto mantenido y distribuido por Marcelo Aníbal Báez. Se encuentra hospedado en Github:
https://github.com/marceloabaez/EjerciciosPdM.git
