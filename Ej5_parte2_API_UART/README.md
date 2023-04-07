- Proyecto Ej4_parte2_API_MEF: El proyecto tiene como fin implementar una máquina de estados finitos
para realizar debounce en el PUSH_BUTTON de la placa NUCLEO. El LED2 de la placa debe traté dparpadear
de manera intermitente, el período de parpadeo puede adoptar dos valores, cambiando entre ellos
al detectar el flanco de bajada del pulsador PUSH_BUTTON.


- Archivos clave: Las funciones para controlar la MEF que detectan el estado del pulsador, el flanco
de bajada y que controla la frecuencia de parpadeo del LED se definen en el archivo API_debounce.c
Las funciones buttonPressed() y buttonReleased() podrían haberse omitido en este ejercico haciendo que
la función debounceFSM_update() actúe sobre la variable debounceState_t el pasar al estado BUTTON_DOWN,
pero mi intención fue hacer que las funciones sirvieran para los dos ejercicios casi sin 
modificarlas.

- Para consultas y sugerencias sobre el proyecto puede contactarse por correo electrónico a
juanperez1234@gmail.com

- Proyecto mantenido y distribuido por Marcelo Aníbal Báez, como fork del proyeco original de 
Patricio Bos. Se encuentra hospedado en Github: https://github.com/marceloabaez/EjerciciosPdM.git
