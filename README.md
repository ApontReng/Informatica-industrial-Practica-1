# Informatica-industrial-Practica-1
Para controlar un sistema de refrigeración de una planta industrial se adquiere periódicamente información de tres sensores: uno de temperatura, uno de presión y otro de caudal. Cada sensor manda por un bus de campo industrial la lectura que ha obtenido junto con la referencia de sensor y el instante de tiempo en que se ha adquirido (timestamp). Aunque la información proporcionada por cada sensor es similar (lectura y timestamp) el formato que emplea cada uno es distinto (ver tabla siguiente).
                  T               Q            P
Lectura         double      unsigned char   float
Timestamp       long int    string           string
 


En esta práctica nos ocuparemos únicamente de la lectura del sensor de temperatura, pero los programas realizados deberían ser fácilmente adaptables a la lectura de los otros dos sensores.
La información de la temperatura será almacenada en una cola, de donde se extraerá para calcular la ley de control siguiendo una política FIFO. La cola tendrá una capacidad máxima de 10 lecturas de forma que si llegan más se perderán las lecturas más antiguas albergando finalmente solo las 10 lecturas más recientes.
En el programa la entrada de datos inicial se hará desde fichero leyendo el archivo temperaturas.txt (ver archivo ejemplo adjunto). Esta lectura se hará automáticamente al arrancar el programa. En cualquier momento se podrán cargar en la cola nuevos datos desde el teclado. Concretamente el programa deberá presentar al menos las siguientes funcionalidades: 1. Sacar por pantalla todos los datos en la cola. 2. Extraer lectura y visualizar el dato extraído de la cola 3. Introducir nuevo dato en la cola. 4. Visualizar las temperaturas máxima y mínima de la cola y los instantes de tiempo en que se han originado.
Se realizarán dos versiones del programa en C++: una primera creando las clases que se necesiten y otra versión empleando contenedores STL.
