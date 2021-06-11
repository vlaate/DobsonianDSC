# Construyendo el circuito del Apuntador Digital
[[English]](https://github.com/vlaate/DobsonianDSC/blob/master/docs/Solderless.md)
[[Español]](https://github.com/vlaate/DobsonianDSC/blob/master/docs/Solderless.es.md)

Hay muchas formas de construir el circuito electrónico para éste proyecto de Apuntador Digital para Telescopio.

La presente guía plantea una forma muy sencilla de ensamblar los componentes sin tener que soldar, de manera que incluso personas que no tengan un cautín (o no sepan cómo usarlo) puedan construir el ADT para su telescopio.

Es necesario que antes de comenzar a ensamblar éste circuito, usted ya haya cargado el código del proyecto al microcontrolador ESP32 tal como se detalla en la [Guía de Carga y Configuración](https://github.com/vlaate/DobsonianDSC/blob/master/docs/UploadConfigure.es.md).

## Lista de Partes

Éste proyecto de apuntador digital requiere muy pocos componentes:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/components.jpg "Parts List")

  * Dos encoders ópticos tipo NPN open-collector (explicados en detalle más adelante).
  * Un microcontrolador ESP32 de "30 pines" ([aliexpress](https://www.aliexpress.com/item/32800930387.html), [amazon](https://www.amazon.com/dp/B079PVCF2G)).
  * Un módulo “keyes screw shield v2” ([keyestudio.com](https://www.keyestudio.com/products/keyes-screw-shield-v2-stud-terminal-expansion-board-double-support), [aliexpress](https://www.aliexpress.com/item/2030646961.html)).
  * Un juego de 10 cables Dupont de 10cm de largo, bien sea macho-hembra ó hembra-hembra ([aliexpress](https://www.aliexpress.com/item/32798042976.html)).

Antes de comenzar a ensamblar el circuito, asegúrese de haber cargado primero el código del proyecto al dispositivo ESP-32.

## El Circuito

El circuito de éste apuntador digital es muy sencillo. El diagrama lógico muestra que básicamente se trata de conectar los 4 cables de cada Encoder al microcontrolador ESP32:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/Circuit_ESP32S.png "Logic Circuit")

Para lograr éstas conexiones de manera fácil y sin tener que usar un cautín ni soldadura, usaremos el módulo *"keyes screw shield v2"* que es un pequeño módulo que ofrece terminales atornillables y los adapta a conectores tipo dupont:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/keyes_screw_shield.jpg "keyes screw shield")

El siguiente diagrama explica cómo sería el cableado desde el ESP32 hacia éste módulo "keyes screw shield", y también muestra cuales de los terminales atornillables verdes corresponden (vienen preconectados con) cuales de los terminales dupont negros:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/solderless.jpg "Solderless Circuit")

  * Observe que hay 4 terminales atornillables verdes marcados como "**GND**", usted puede usar cualquiera de éstos para conectar los cables negros GND de los Encoders ópticos.
  * Observe que hay 2 terminales atornillables verdes marcados "**5V**", usted puede usar cualquiera de éstos para conectar los cables rojos 5V de los Encoders ópticos.
  * Los cables **A (Amarillo)** y  **B (Verde)** del Encoder azimutal deben conectarse en los terminales verdes marcados como **A0** y **A1**.
  * Los cables **A (Amarillo)** y **B (Verde)** del Encoder altitudinal deben conectarse a los terminales verdes marcados como **A2** y **A3**.

Después de conectar los cables de ambos Encoders a los terminales verdes atornillables correctos, use los cables dupont para conectar los terminales negros dupont con los pines correspondientes del ESP-32. Las conexiones se ven así:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/connected_2.jpg "Solderless")

Asegúrese de usar los pines correctos del ESP-32: 
  * El cable rojo 5V debe conectarse al pin del ESP32 etiquetado como **VIN**.
  * El cable negro GND debe conectarse al pin del ESP32 etiquetado como **GND**.
  * Las conexiones A y B que vienen de los terminales A0 y A1 deben conectarse a los pines del ESP32 etiquetados como **D18** y **D19**.
  * Las conexiones A y B que vienen de los terminales A2 y A3 deben conectarse a los pines del ESP32 etiquetados como **D25** y **D26**.

Y eso es todo! Si las conexiones están correctas y el ESP32 ya está programado con el software, entonces el circuito está completo.


## Acerca de los Encoders Ópticos

La resolución del Apuntador Digital para Telescopio depende de la resolución de los encoders ópticos que utilice, y de la proporción de transmisión con la cual usted conecte los encoders a los ejes del telescopio.

Para encoders conectados *directamente* al telescopio  (sin usar engranajes ni reducción), se recomienda usar encoders con resoluciones de **2000 p/r** a **2500 p/r**. Ésto permitiría resoluciones de entre 8.000 a 10.000 pasos en 360 grados, es decir entre 2.2 a 2.7 minutos de arco por paso del encoder. 

Para encoders conectados al telescopio mediante algún tipo de transmisión o reducción (por ejemplo poleas tipo GT2) los encoders económicos de **600 p/r** son suficientes, y por ejemplo usando poleas GT2 a una relación de transmisión de 4,25 (una polea grande de 85 dientes conectada a una polea pequeña de 20 dientes) se lograría una resolución de (600 * 4 * 4,25 = 10.200) 10.200 pasos por 360 grados, es decir de 2.1 minutos de arco por paso.

Ejemplo con poleas GT2:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/full_close.jpg "Close up AZ")

Para lograr que el circuito sea lo más sencillo posible, los encoders ópticos a usar **deben** tener salidas tipo **"NPN open-collector"**. Encoders con otro tipo de salidas (por ejemplo: *"Line Driver output"*) no sirven con éste sencillo circuito, pues requerirían hardware adicional.

El tipo de Encoder más común utilizable en éste proyecto de apuntador digital es el *Signswise / BQLZR* 600 p/r y sus clones genéricos. Se recomienda buscar que la página del vendedor mencione *"NPN open-collector"* cuando compre los genéricos. ([aliexpress](https://www.aliexpress.com/item/32669741048.html)). 

Parece existir un [vendedor](https://www.aliexpress.com/item/32961497880.html) de Encoders de alta resolución OMRON E6B2-CWZ6C (que dan hasta 2500 p/r) pero no los he probado personalmente. Recuerde que únicamente la familia CWZ6C es “NPN open-collector”, otras familias de la marca OMRON (ej: CWZ5B, CWZ3E, CWZ1X) no servirían. ([datasheet](http://www.ia.omron.com/data_pdf/cat/e6b2-c_ds_e_6_1_csm491.pdf)).

Si usted va a usar poleas GT2 (las de las impresoras 3D) como transmisión, para las poleas pequeña recuerde que el eje de los Encoders tiene un ancho de 6mm, tanto para los Signswise, BQLZR como para los OMRON E6B2.

[Aquí](https://www.cloudynights.com/topic/589521-37-dobsonian-dsc-for-diy-makers/page-5#entry8724826) puede encontrar un diseño de sujetador para los encoders Signswise para crearlo con una impresora 3D. También puede hacer uno sencillo con madera de balso.

Si conoce otros encoders tipo NPN open-collector que puedan funcionar con el proyecto, puede hacernos saber en los foros de [CloudyNights forum](https://www.cloudynights.com/topic/589521-37-dobsonian-dsc-for-diy-makers/)

## Acerca de diferentes versiones del ESP-32

El microcontrolador ESP32 viene en diferentes versiones. La presente guía se basa en la versión de 30 pines / GPIOs, pero hay versiones con 38 pines, y versiones en otros formatos como el tipo UNO o el tipo Wemos Mini. Cualquier versión del ESP32 puede usarse para construir el proyecto, pero los diagramas y pines ilustrados en ésta guía son para la versión de 30 pines, por lo que para un principiante sería mejor usar esa placa de desarrollo ESP32 específicamente.

## Fuente de Energía

Las placas ESP32 generalmente vienen con un conector micro-USB, de manera que un banco de poder USB (de los usados para recargar teléfonos celulares) sería la solución mas sencilla para darle energía al apuntador digital.

Si desea usar otras fuentes de energía de los que tienen un conector DC tipo “plug”, como las populares baterías recargables Talentcell de 12V, or una pila de 9V recargable con adaptador plug, hay un pequeño módulo que se puede usar:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/battery_options.jpg "Battery")

Ese pequeño [módulo azul](https://www.aliexpress.com/item/32806774850.html) puede recibir voltajes entre 7V a 12V y entregar 5V regulados con suficiente corriente para energizar el proyecto. Para usarlo, conecte los pines "5V OUT" del módulo con el pin "VIN" del ESP32 y con el cable rojo "5V" del terminal atornillable.  También conecte los pines “GND” del módulo azul con el pin “GND” del ESP32 y con el cable negro GND del terminal atornillable.

No es una forma eficiente de darle energía al proyecto ya que para bajar el voltaje a 5V, se desperdicia algo de energía en forma de calor, pero puede ser una solución conveniente para quienes no tienen un banco USB, pero si tienen una batería portátil de 12V.

