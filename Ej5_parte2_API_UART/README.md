- Proyecto Ej5_parte2_API_UART: El proyecto tiene como fin implementar una comunicación UART con la PC
se mantiene la máquina de estados finitos para realizar debounce en el PUSH_BUTTON de la placa NUCLEO.
El LED2 de la placa se enciende con el botón pulsado y apaga al soltar el botón. Los flancos ascendentes
y descendentes se comunican por UART, así como los estados de inicialización de la UART y los
parámetros de configuración de la misma.


- Archivos clave: Las funciones para enviar los mensajes por UART se incluyen en el archivo
API_uart.c . Los demás archivos se mantienen de las prácticas anteriores a excepción de readKey
a la cual se le aumentó la funcionalidad para representar las 3 posibilidades de cambio de estado
(flanco descendente, flanco ascendente y sin cambios).

- Para consultas y sugerencias sobre el proyecto puede contactarse por correo electrónico a
juanperez1234@gmail.com

- Proyecto mantenido y distribuido por Marcelo Aníbal Báez, como fork del proyeco original de 
Patricio Bos. Se encuentra hospedado en Github: https://github.com/marceloabaez/EjerciciosPdM.git
