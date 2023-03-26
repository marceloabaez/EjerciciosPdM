- Proyecto Ej4_MEF_debounce: El proyecto tiene como fin empezar a familiarizarse con la modularización
de programas. Las funciones que contienen el delay se ubican en un archivo separado, dejándose en
el main.h solamente las llamadas a éstas. 

- Archivos clave: El código fuente y cabecera de la API que controla los retardos no bloqueantes
se encuentran en /Drivers/API/. Basan su funcionamiento en el contador interno de 32bits que se
incrementa cada milisegungo, y es accedida mediante la HAL.

- Para consultas y sugerencias sobre el proyecto puede contactarse por correo electrónico a
juanperez1234@gmail.com

- Proyecto mantenido y distribuido por Marcelo Aníbal Báez, como fork del proyeco original de 
Patricio Bos. Se encuentra hospedado en Github: https://github.com/marceloabaez/EjerciciosPdM.git
