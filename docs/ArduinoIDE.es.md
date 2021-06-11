# Guía de Arduino para principiantes
[[English]](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.md)
[[Español]](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.es.md)


El propósito de esta guía es ayudar a astrónomos aficionados que quieran construir el [proyecto de Apuntador Digital para Telescopio](https://github.com/vlaate/DobsonianDSC), pero que nunca hayan tenido experiencia previa con Arduino ni microcontroladores.

Como tal, esta guía es para novatos y ofrece instrucciones paso a paso desde cómo instalar y configurar el IDE de Arduino en su computadora, hasta cómo conectar su microcontrolador, cargarle un programa y verificar que funcione correctamente.

### 1. Descargar el Entorno de Desarrollo Arduino

Visite https://www.arduino.cc/en/software y descargue el software de desarrollo (IDE) Arduino para su sistema operativo. A la fecha (2021) recomiendo usar la versión 1.8.15 or superior.

### 2. Instalar Arduino

Ejecute el instalador que ha descargado, asegúrese de que todos los componentes de Arduino estén seleccionados para ser instalados (incluso el "USB driver") y espere a que se complete la instalación:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/2.png "Installing IDE")

### 3. Abrir el IDE Arduino

Ahora que ya tiene instalado el Entorno de Desarrollo Arduino (Arduino IDE) podrá encontrar un nuevo ícono de Arduino en su computador. Úselo para ejecutar el IDE Arduino. 

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/3.png "Launch IDE")

Éste es el software que utilizará para compilar programas tipo Arduino y cargarlos (vía USB) a su microcontrolador ESP32. 

### 4. Agregar URLs de Placas

Para que el IDE Arduino pueda funcionar con microcontroladores ESP32 y similares, necesita primero descargar su “manejador de placas” (board manager).

Para hacer esto, en el menú principal del IDE Arduino seleccione "File" -> "Preferences":

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/4.png "Add URLs")

En la ventana emergente hay una configuración llamada “Additional Boards Manager URLs".

Copie y pegue el siguiente valor en esa opción:


```
https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

### 5. Instalar Manejadores de Placas

Haga click en "OK" para cerrar la ventana de preferencias, y de regreso en el menú principal de Arduino, seleccione "Tools" -> "Board: XXX" -> "Boards Manager"

Aparecerá la ventana emergente del manejador de placas. El campo de texto es un campo de búsqueda, escriba "ESP32" en ese campo y espere a que la lista de placas se actualice. Cuando aparezca una placa llamada *"esp32 by Espressif Systems"*, haga click en el botón "Install" a su derecha:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/5.png "Install ESP32 BM")

Una vez termina de instalar, haga click en el botón "Close".

### 6. Instalar Librerías

El proyecto de Apuntador Digital para Telescopio (ADT) necesita un par de librerías de código abierto. Para instalarlas, haga lo siguiente:

En el menú principal, seleccione "Tools" -> "Manage Libraries"

Aparecerá la ventana del manejador de librerías. El campo de texto es para hacer búsquedas, escriba "ESP32Encoder" allí y espere a que la lista de librerías se actualice. Cuando aparezca una librería llamada *"ESP32Encoder by Kevin Harrington"* haga click en su botón "Install".

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/6.png "Install ESP32Encoder")

Una vez la librería ESP32Encoder esté instalada, cambie el texto de búsqueda por "ArduinoJson" y espere a que aparezca una librería llamada *"ArduinoJson by Benoit Blanchon"* y haga click en su botón “Install” para instalarla de la misma manera que la anterior. Una vez haya finalizado instalando ambas librerías, cierre la ventana del manejador de librerías.

### 7. Seleccionar Placa

Ahora que su IDE Arduino está lista para compilar programas para la familia de microcontroladores ESP32, es hora de configurarla para el microcontrolador específico que vamos a usar para el proyecto.

En el menú principal del IDE, seleccione "Tools" -> "Board: XXX" -> "ESP32 Arduino"

Aparecerá una lista larga de placas ESP32 boards soportadas por el entorno de desarrollo. Se recomienda elegir "ESP32 Dev Module". 

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/7.png "Select Board")

### 8. Configurar el Particionamiento de Memoria

El proyecto de Apuntador Digital para Telescopio ocupa bastante memoria (principalmente debido a que las librerías Bluetooth son muy grandes).
Para evitar que le aparezca un error de compilación diciendo *"Sketch too big"*, es necesario asignar una porción mayor de la memoria del microcontrolador a la aplicación.

Para ello, seleccione en el menú principal del IDE la opción "Tools" -> "Partition Scheme: XX" -> *"Huge App 3MB no OTA/1MB SPIFFS"*. Con ésto se evita que al compilar se aparezca el siguiente error (ver texto en naranja):

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/8.png "Sketch Too Big")

**Nota:** Parte de la razón por la cual recomiendo seleccionar la placa "ESP32 Dev Module" en un paso anterior, es porque otras placas no permiten cambiar el particionamiento de memoria (por ejemplo la placa NodeMCU32-S no lo permite). Si usted decide usar una placa distinta como la Wemos D1 ESP32 o similar, busque opciones de particionamiento con un nombre parecido a "Huge App".

### 9. Conectar el Microcontrolador

Ahora es necesario enseñarle al IDE Arduino cómo comunicarse con su microcontrolador. Conecte un extremo del cable USB a su to microcontrolador ESP32, y el otro extremo a su computador.

En circunstancias normales, los drivers necesarios ya deberían venir con su sistema operativo e instalarse automáticamente con sólo conectar el ESP32 vía USB al computador. Si su computador tiene un sistema operativo antiguo, revise la guía de Espressiff   (el fabricante del ESP32) la cual contiene enlaces a diferentes drivers:

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html

### 10. Identificar el Puerto Serial COM

Una vez el driver USB para el microcontrolador esté instalado, es hora de verificar que el IDE se pueda conectar correctamente al dispositivo.

En el menú principal del IDE, seleccione "Tools" -> "Port: XX"

Verá que aparece una lista de puertos seriales (ejemplo: COM1, COM5, etc). Se supone que usted debe elegir el puerto serial COM que su computador le asignó al microcontrolador ESP32:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/10.png "Com Ports")

**¿Cómo averiguo cual de los puertos COM de la lista es el que está asignado al microcontrolador que está conectado por USB??**

Una forma sencilla de averiguarlo es: Mientras el cable USB todavía está conectado, tome nota de todos los nombres en la lista de puertos COM. Entonces haga click con el ratón en algún otro lugar del IDE para que el menú (y la lista de puertos COM) se oculte. Entonces desconecte el cable USB, y vuelva a seleccionar "Tools" -> "Port: XX" en el menú, para volver a ver la lista de puertos COM. El nombre que haya desaparecido de la lista después de desconectar el cable USB, ese es el puerto serial COM que corresponde a su microcontrolador ESP32.

### 11. Valide la conexión USB

Asegúrese de que el cable USB cable está conectado tanto al ESP32 como al computador.

Entonces, en el menú principal del IDE Arduino, seleccione "Tools" -> "Get Board Info".

Debería ver aparecer una pequeña ventana emergente que contiene el número serial del microcontrolador ó el mensaje *"SN: upload any sketch to obtain it"*:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/11.png "Board Info")

Si usted obtiene un mensaje similar a éste, significa que todo está bien. Si usted obtiene un pequeño mensaje en la barra verde del IDE Arduino diciendo "can't obtain info", intente con un puerto serial COM diferente.

### 12. Creando un programa de prueba

Ahora vamos a usar un programa sencillo para verificar que el microcontrolador esté funcionando correctamente.

En el IDE Arduino, seleccione "File" - > "New"

En la nueva ventana del IDE que aparece, copie y pegue el siguiente contenido:

``` C
/** Programa Eco sencillo para validar enlace serial */
# define BUFFER_SIZE  80
char buf[BUFFER_SIZE];

int readLineFromSerial(char *buffer)
{
  static int pos = 0;
  int rpos;
  int character = Serial.read();

  if (character > 0)  {
    switch (character) {
      case '\r':
        break;
      case '\n':
        rpos = pos;
        pos = 0;
        return rpos;
      default:
        if (pos < BUFFER_SIZE - 1) {
          buffer[pos++] = character;
          buffer[pos] = 0;
        }
    }
  }
  return 0;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Esperando mensaje");
}

void loop()
{
  if (readLineFromSerial(buf) > 0)
  {
    Serial.print("Recibido:  ");
    Serial.println(buf);
    Serial.println("\nEsperando Mensaje");
  }
}
```


Ahora seleccione en el menú la opción "File" -> "Save" y proceda a grabar el programa en algún lugar de su computador.

### 13. Cargando el Programa

El siguiente paso es “cargar” el programa al microcontrolador ESP32 usando el cable USB. Para hacer ésto, usted puede seleccionar en el menú "Sketch" -> "Upload" ó hacer click en el ícono redondo que tiene una flecha apuntando a la derecha:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/12.png "Upload")

Al hacer ésto, la parte de abajo del IDE (fondo negro con texto naranja) empezará a mostrar una gran cantidad de mensajes mientras se compila y se carga el programa. Para ésta foto agrandé la sección de mensajes del IDE:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/13.png "Uploaded")

Si en lugar de los mensajes anteriores, el mensaje que le aparece dice: *"Connecting.....------...."* seguido de **"Failed to connect to ESP32: Timed out waiting for packet header"**, ésto se resuelve intentando de nuevo (haga click en "Sketch" -> "Upload") y tan pronto aparezca el mensaje que dice **"Connecting..."** presiona el botón físico del ESP32 que está marcado como "BOOT" y manténgalo presionado durante varios segundos.

La señal de que la carga ha sido exitosa es que en la barra verde del IDE aparece el mensaje "Done uploading." como se ve en la foto de arriba.

Si usted obtiene ese mensaje significa que todo funcionó y que el programa quedó compilado y cargado en el microcontrolador. De hecho, probablemente ya se está ejecutando en el pequeño dispositivo.

### 14. Validando que el microcontrolador ESP32 funcione

Lo que hace el programa ejemplo que hemos cargado al ESP32 es recibir mensajes y responder con un “eco”. Ésto nos permitirá validar que el hardware esté funcionando correctamente, incluyendo la conexión serial vía USB.

Para validarlo, seleccione en el menú  "Tools" -> Serial Monitor".

Aparecerá una pequeña ventana, que en su parte inferior derecha tiene un combo de selección. Úselo para seleccionar "115200" que es la velocidad de comunicación que el programa de prueba espera usar:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/14.png "Baud Rate")

Ahora, puede ver que en la parte superior de la ventana hay un campo de texto. Escriba algo allí (cualquier cosa, por ejemplo “Hola”) y haga click en el botón "Send".

Debería ver una respuesta del microcontrolador, que contiene el mismo texto que usted le envió, por ejemplo:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/15.png "Success")

Usted puede escribir y enviar más mensajes, y el ESP32 debería responder. Esto es evidencia de que el programa quedó correctamente cargado en la placa ESP32 y de que la conexión serial vía USB funciona correctamente.

Y eso es todo! Si llegó hasta éste punto y todo funcionó como se describe en ésta guía, entonces su computador ya está listo para programar microcontroladores ESP32 y usted está listo para la [siguiente guía](https://github.com/vlaate/DobsonianDSC/blob/master/docs/UploadConfigure.md).

