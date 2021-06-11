# Apuntador Digital para Telescopios Dobsonianos  (ADT)
[[English]](https://github.com/vlaate/DobsonianDSC)
[[Español]](https://github.com/vlaate/DobsonianDSC/blob/master/README.es.md)

Los astrónomos aficionados desean saber hacia dónde está apuntando su telescopio. Por ésta razón, algunos telescopios comerciales como el Orion IntelliScope vienen equipados con funcionalidades tipo “push-to”, basadas en encoders ópticos de alta precisión conectados a la montura del telescopio, y un dispositivo electrónico o control de mano que tiene una base de datos con las coordenadas de miles de objetos celestes.

También existen apps para Android y para iOS como [SkySafari](https://skysafariastronomy.com/),  que contienen bases de datos celestes incluso mejores, y que ofrecen una interfaz de usuario muy superior a los controles de mano que vienen con los telescopios push-to.

Éste proyecto es una implementación de código libre “open source” de un Apuntador Digital para Telescopio, que mediante dos encoders ópticos de bajo costo y un microcontrolador ESP32 permite conectar un telescopio dobsoniano con la app SkySafari, y así poder ver fácilmente hacia dónde está apuntando el telescopio.

En el diseño del apuntador digital, se puso mucho énfasis en lograr que cualquier astrónomo aficionado pueda construir el circuito incluso si no tiene experiencia alguna con electrónica ni con Arduino. Para ello, el proyecto ofrece guías paso-a-paso ilustradas que indican desde cómo instalar y configurar Arduino hasta como ensamblar de una forma muy sencilla los componentes sin tener que soldar, de manera que incluso personas que no tengan un cautín (o no sepan cómo usarlo) puedan construir el ADT para su telescopio. 

El ADT logra lo siguiente:

* Un mínimo absoluto de componentes electrónicos, haciéndolo sencillo y de bajo costo (las partes cuestan menos de **USD $40**).
* Fácil de construir, no necesita soldadura ni herramientas especiales.
* Comunicación inalámbrica con apps como SkySafari Plus/Pro.
* Capacidad de conectarse a un WiFi externo/existente (para poder seguir conectado a internet mientras se usa el ADT vía WiFi). 
* Soporta conexión Bluetooth.
* Página Web de configuración, para fácilmente ajustar todo: password WiFi, resoluciones de los encoders, reversar dirección de encoders, notificación, nombre del dispositivo.

Así se ve cuando está instalado en un pequeño dobsoniano de sobremesa:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/full.jpg "Mini Dob with DSC")

## Documentación

  * La [Guía de Arduino para Principiantes](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.es.md) explica de manera ilustrada y paso a paso cómo instalar y configurar Arduino en su computador, incluyendo las placas y librerías necesarias para que pueda cargar el software de éste ADT en un microcontrolador ESP-32.
  * La [Guía para Cargar y Configurar el ADT](https://github.com/vlaate/DobsonianDSC/blob/master/docs/UploadConfigure.es.md) provee instrucciones paso a paso para cargar el software ADT en un microcontrolador ESP32 microcontroller, para configurarlo, y para conectarse con la app SkySafari.
  * La [Guía de construcción del Circuito](https://github.com/vlaate/DobsonianDSC/blob/master/docs/Solderless.es.md) contiene la lista de partes, diagrama esquemático e instrucciones paso a paso para ensamblar el circuito del ADT de manera sencilla, sin necesitar soldadura ni herramientas especiales.
  * Si tiene problemas o comentarios, puede escribirnos en el foro de [CloudyNights](https://www.cloudynights.com/topic/589521-37-dobsonian-dsc-for-diy-makers/).
  * [Aquí](https://www.cloudynights.com/topic/772803-how-to-attach-altitude-encoders-to-dobsonians/) puede encontrar información útil sobre cómo montar mecánicamente encoders en algunos tipos de dobsonianos.

## Fotos:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/full_close.jpg "Close up AZ")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/Alt_encoder_1.jpg "Alt Encoder 1")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/Alt_encoder_2.jpg "Alt Encoder 2")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/components.jpg "Components")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/webConfig_sm.png "Web Configuration")
