# Cargando y Configurando el Apuntador Digital
[[English]](https://github.com/vlaate/DobsonianDSC/blob/master/docs/UploadConfigure.md)
[[Español]](https://github.com/vlaate/DobsonianDSC/blob/master/docs/UploadConfigure.es.md)

La presente guía le mostrará cómo cargar el código del apuntador a un microcontrolador ESP32, cómo configurarlo y cómo conectar la aplicación móvil SkySafari Plus/Pro al apuntador.

Se recomienda que antes de seguir ésta guía, usted primero complete los pasos de la [Guía de Arduino para Principiantes](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.es.md) en la cual se indica cómo configurar correctamente Arduino en su computador incluyendo las placas y librerías que el proyecto necesita.

## Descargando el Código del Apuntador

Una vez usted haya terminado la configuración del IDE Arduino (y las placas y librerías del proyecto) en su computador, abra en el navegador del computador la página GitHub del proyecto: [https://github.com/vlaate/DobsonianDSC](https://github.com/vlaate/DobsonianDSC)

En la página encontrará un botón verde llamado "Code" o “Código”. Si hace click en éste, verá un menú con una opción llamada "Download ZIP" o “Descargar ZIP”. Haga click en ese botón!

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/download.png "Downloading Code")

Su computador descargará un archivo comprimido llamado *"DobsonianDSC-master.zip"*. Usted necesita extraer los contenidos de ese archivo y grabarlos en el lugar que desee en su computador. En Windows ésto se logra haciendo click derecho en el archivo y seleccionando "Extract All" (“Extraer Todo”).

Después de hacer ésto, usted debería tener una carpeta llamada "DobsonianDSC-master" en su computador, en la ubicación que eligió para descomprimir el archivo ZIP. 

En dicha carpeta, encuentre el siguiente archivo:

```
DobsonianDSC-master\DobsonianDSC\DobsonianDSC.ino
```

Haga doble click en dicho archivo para abrirlo. Ello debería lanzar el IDE Arduino, haciendo visibles los contenidos del archivo.

Conecte el cable USB a su microcontrolador ESP32, y el otro extremo a su computador. Asegúrese de que su IDE Arduino esté apropiadamente configurada como se indicó en el [paso #9 de la Guía de Arduino para Principiantes](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.es.md#9-conectar-el-microcontrolador). 

Siga los pasos indicados en  el [paso #13 de la Guía de Arduino](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.es.md#13-cargando-el-programa) para cargar el código al dispositivo ESP32. Ésto tomará varios minutos.

Una vez cargado el programa en el ESP32, para validar que funcione correctamente es necesario usar un dispositivo WiFi (computador portátil, tableta o celular) para revisar la lista de redes WiFi a su alrededor.

En la lista debería aparecer una nueva red llamada "Telescope_DSC". Conéctese a esa red.

Como ésta es la red WiFi interna creada por el Apuntador Digital, es una red que no tiene verdadera conexión a Internet. Tenga presente que algunas tabletas y celulares al conectarse a una red WiFi que no tiene internet, pueden emitir advertencias como la siguiente:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/WiFi_NoInternet_C.png "WiFi without Internet")

Asegúrese de revisar esas notificaciones y de decirle al celular/tableta que siga conectado a éste WiFi. De no hacerlo, algunos celulares/tabletas se desconectan automáticamente después de unos segundos.

Una vez usted se ha conectado al WiFi interno del dispositivo, apunte su navegador hacia http://192.168.4.1

Eso debería abrirle la página web de configuración del Apuntador Digital:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/webConfig_sm.png "Web Config")

## Configurando el Apuntador Digital

Para cambiar la configuración del ADT, usted necesita editar los campos apropiados en la página web de configuración, y presionar el botón "Save" par que queden grabados permanentemente. Para que los cambios tengan efecto inmediato, es necesario presionar el botón "Restart", el cual hará que el ESP-32 se reinicie.

### Encoders y Resoluciones

Los campos llamados *"Azimuth Steps"* y *"Altitude Steps"* pueden ser usados para permitirle al ADT saber la resolución de los ejes del telescopio (derivada de los Encoders y de la relación de transmisión), de manera que el dispositivo pueda darle dicha información a apps como  [SkySafari](https://skysafariastronomy.com/).

**Flip Azimuth**: Algunas veces pasa que al ensamblar el ADT e instalar los encoders en el telescopio, uno encuentra que al mover horizontalmente el telescopio en el sentido de las manecillas del reloj, la pantalla de SkySafari muestra el movimiento pero en la dirección opuesta. Para reversar la dirección del Encoder Azimutal sin tener que hacer cambios físicos al circuito, simplemente use ésta opción de *"Flip Azimuth"*.

**Flip Altitude**: De igual manera, si usted necesita reversar la dirección de movimiento del Encoder de Altitud, puede simplemente usar ésta opción.

### Bluetooth

El campo llamado *"Bluetooth device Name"* le permite definir el nombre que su ADT usará para exponer su interfaz bluetooth. Bluetooth es un mecanismo muy conveniente para conectarse al ADT sin usar cables, que además permite que su celular/tableta siga conectada a internet.

Después de darle un nombre Bluetooth a su dispositivo, haga click en el botón *"Save"*, y luego en el botón *"Restart"*. Puede tomar un par de minutos, pero con eso ya debería poder emparejar su teléfono o tableta con el dispositivo ADT.

**Nota para usuarios Android:** Algo que puede ser confuso al usar bluetooth en Android es que después de emparejar un dispositivo, puede aparecer un botón de “conectar” en el menú bluetooth, pero usar ese botón no parece hacer nada. Lo que ocurre es que la conexión Bluetooth debe ser solicitada por una App (como SkySafari), y el sólo hacer click en "conectar" no es suficiente. Entonces, después de emparejar su ADT por bluetooth, para probarlo en un celular o tableta Android es necesario usar una app como SkySafari.

**Nota para usuarios iOS:** Es conocido que en iOS no es posible conectar SkySafari con dispositivos seriales a través de Bluetooth. En esos teléfonos/tabletas la única forma de conectarse con el ADT es usando WiFi.

### Configurando un WiFi externo

Cuando se usa una conexión WiFi para conectarse al ADT, puede ocurrir que queramos mantener una conexión a internet en la tableta o teléfono usado para conectarnos al ADT.  Una forma de lograrlo es hacer que el ADT se conecte a una red WiFi existente, que puede ser la red de nuestra casa o un HotSpot (tethering) que abrimos en el celular.

En la página web de configuración, si llenamos los campos llamados *"WiFi SSID Name"* y *"WiFi Password"* y hacemos click en "Save", lo que ocurre es lo siguiente:

Cada vez que el ADT es encendido, revisará si hay algún valor asignado para éstos dos campos. Cuando no existen valores (por ejemplo cuando el ADT está nuevo), el dispositivo lanzará su propia red WiFi llamada "Telescope-DSC" y tomará la dirección IP por defecto (192.168.4.1).

Cuando por el contrario, si habían valores almacenados para los dos campos en cuestión, el ADT intentará conectarse a esa red. Si lo logra, todo estará bien: usted puede conectarse al ADT y al internet al mismo tiempo usando esa red WiFi. Si el ADT no logra conectarse a esa red WiFi (por ejemplo: la contraseña es incorrecta, o el ADT se usa muy lejos de esa red) entonces el ADT recurrirá por defecto a lanzar su propia red WiFi llamada "Telescope-DSC" y tomar la IP 192.168.4.1.

#### Cual es mi dirección IP?

Una complicación de hacer que el ADT se conecte a una red WiFi existente, es que esa red le asignará una dirección IP dinámica, y usted necesita una forma de averiguar esa dirección IP para poderse conectar al ADT.

Como ayuda, éste sistema ADT tiene una funcionalidad opcional: Después de conectarse exitosamente a una red WiFi que tiene acceso a internet, el dispositivo puede enviarte una notificación a tu celular diciéndote la dirección IP que le asignaron.

Ésta funcionalidad opcional depende de una app llamada PushOver, la cual está disponible tanto para Android como para iOS. No es gratuita, pero es poco costosa (y tiene un período de prueba de 30 días).

Si desea usar ésta funcionalidad, necesitará instalar la app PushOver en su celular, crear una cuenta PushOver, y autenticarse en https://pushover.net/ para realizar los siguientes pasos:

Estando autenticado en pushover.net, copie su *"user key"* de la parte superior derecha de la pantalla:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/pushover_user_key.png "Pushover user")

... y pegue ese valor en la página web de configuración del ADT, en el campo llamado *"Notification User Key"*.

Luego, en la página de pushover, seleccione la opción de *"Create an Application/API Token"*: 

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/pushover_new_app.png "Pushover Create app")

... llene el formulario (esencialmente: darle un nombre y descripción, como "Mi Telescopio") y haga click en *"Create Application"*. Ésto abrirá una nueva pantalla que contiene el *API key* para usar:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/pushover_api_key.png "Pushover API key")

Copie ese *API key*, y péguelo en la página web de configuración del ADT, en el campo llamado *"Notification API Key"*.

Si los valores son correctos, y la app de PushOver está correctamente instalada en su celular, entonces cada vez que el DSC sea encendido y se conecte a un WiFi externo, el dispositivo le enviará una notificación a su celular indicando la dirección IP que le asignó la red, que es la dirección IP que necesitará usar para conectar SkySafari y para abrir la página web de configuración del ADT.

## Conectando SkySafari

El ADT está concebido para ser usado con aplicaciones de astronomía que soportan el protocolo "Basic Encoding System" (también llamado protocolo Intelliscope/BBox/Sky Wizard). La presente guía recomienda usar [SkySafari](https://skysafariastronomy.com/) y muestra los ejemplos con esa app.

**Nota**: Sólo las versiones **SkySafari Plus** y **SkySafari Pro** soportan conectarse al ADT. La versión sencilla (que no es “Plus” ni “Pro”) no sirve para el proyecto.

Primero, usted necesita asegurarse de que su ADT esté encendido y de que puede conectarse a la página web de configuración (usando su navegador web).

En SkySafari, seleccione el ícono de *"Settings"* y busque la sección llamada *"Telescope"*. Ésta contiene un ítem llamado *"Setup"*:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/Skysafari_3.png "SkySafari B")

Para el campo *Scope Type*, seleccione *"Basic Encoder System"*, y para el campo *Mount Type* seleccione *"Alt-Az Push to"*

Aquí es necesario indicar los valores de “encoder steps per revolution” que es la resolución de cada eje del telescopio. También puede seleccionar *"Get Automatically"* si ya los cargó en la página web de configuración del ADT.

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/Skysafari_4.png "SkySafari C")

Es necesario indicarle a SkySafari si la conexión con el ADT debe ser por Bluetooth o por WiFi:

Si selecciona Bluetooth, asegúrese de que el celular/tableta si tenga activado el bluetooth, y de que previamente haya sido emparejado con el ADT.

Si selecciona WiFi, SkySafari le pedirá indicar la dirección IP del ADT, la cual es *192.168.4.1* si está usando el WiFi interno del ADT, ó es una dirección IP dinámica si está usando una red WiFi ya existente. Recuerde que el número de puerto (*Port Number*) siempre deberá ser 4030.

Finalmente, puede cerrar el menú de Settings para regresar a la pantalla principal de SkySafari (que tiene un mapa del cielo). En esa pantalla, seleccione el botón "Scope" y luego el botón "Connect". Luego de un par de segundos debería escuchar un agudo "ding", sonido que indica que SkySafari se ha conectado exitosamente al telescopio.

Si en lugar de escuchar el exitoso "ding" aparece un mensaje de error, verifique que aún pueda  abrir la página web de configuración del ADT en el mismo celular/tableta y revise la configuración.

Habiendo cargado y configurado el microcontrolador ESP32 con el sistema ADT, ahora es el momento oportuno para seguir la [Guía para Armar el Circuito del ADT](https://github.com/vlaate/DobsonianDSC/blob/master/docs/Solderless.es.md).

### Recomendaciones de Alineación

Siempre que vaya a usar el ADT, se recomienda usar un nivel (de los que tienen una burbuja en un líquido brillante) para nivelar horizontalmente la base del telescopio dobsoniano y así obtener mayor precisión del ADT.

Cuando abra SkySafari y lo conecte exitosamente al ADT, la app no sabrá inicialmente a dónde está apuntando el telescopio. Es necesario realizar un proceso de Alineación (*Star Alignment*) para poder que la pantalla de SkySafari presente correctamente hacia dónde está apuntando el telescopio.

Para hacer esa alineación, lo que hay que hacer es apuntar el telescopio hacia una estrella conocida y  centrar la estrella en el campo visual del ocular. Entonces, en SkySafari busque y seleccione la misma estrella y presione el botón *"Align"*. Con eso, la pantalla de SkySafari debería mostrar correctamente hacia dónde está apuntando el telescopio, a medida que usted lo mueve.

SkySafari ahora también permite realizar una segunda alineación con una segunda estrella (ojalá una que esté en otra parte alejada del cielo). Esto se llama *“2-star alignment”*, y reduce la necesidad de nivelar la base del telescopio antes de usarlo y aumenta la precisión del ADT.

Para hacer la segunda alineación, simplemente repita el proceso con una segunda estrella conocida, asegurándose de presionar *"Align"* (no *"Restart Alignment"*) cuando SkySafari lo pregunte. Hacer éste segundo alineamiento le permite a SkySafari tener un mejor modelo matemático del telescopio y así presentar un despliegue más preciso de su posición.

**Nota:** Aunque pareciera que puede hacerse la alineación con más estrellas, en realidad SkySafari sólo recuerda las últimas dos estrellas usadas para la alineación.

La primera vez que usted realice éste proceso, podría ocurrir que encuentra que al mover el telescopio en una dirección, SkySafari muestra el movimiento en la dirección opuesta. Para corregir ésto, abra la página web de configuración del ADT y cambie las opciones **Flip Azimuth** y/o **Flip Altitude** para reversar la dirección del encoder que necesite corregir.
