# DobsonianDSC

Amateur astronomers want to know where their telescope is pointing at. For this reason, many commercial telescopes come equipped with "push to" or "go to" features, often based on high precision optical rotary encoders attached to the telescope mount, and a hand control device with a database of coordinates of thousands of stars and other sky objects.

There are also commercial Digital Setting Circles, which are kits sold for telescope owners to adapt to their existing telescope, in order to give it "push to" features. Commercial DSCs are very accurate, mostly based on optical encoders, and usually cost a few hundred dollars.

This project is an implementation of Digital Setting Circles for dobsonian telescopes using an inexpensive variety of optical encoders. There are two version:

* The old version uses an accelerometer for Altitude (for when it's difficult to mount an alt encoder) and is meant for ESP8266 microcontrollers.
* The new version uses optical encoders for both Azimuth and Altitude and is meant for the ESP32 mircocontrollers, and adds a web configuration page.

This DSC achieves the following:

* Easy and inexpensive to build for a DIY maker or Arduino enthusiast.
* A bare minimum number of components/connections to plug/solder.
* Wireless communication with apps like SkySafari, SDC-Browser and others (no need for a wired handheld control)

The new ESP32 version also features:
* Ability to connect to an external WiFi (to maintain access to the internet while using the DSC)
* Ability to communicate the obtained IP address via Pushover notifications to smartphones.
* Bluetooth support.
* Web configuration page for easily configuring everything: WiFi settings/password, encoder resolutions, flipping encoder pins, notification API/keys.

This is what the Encoder+Accelerometer version looks like installed on a tabletop Zhumell Z114 minidob:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/dobDSC-front.jpg "Finished look")

Useful information on how to attach altitude encoders to dobsonians can be found [here](https://www.cloudynights.com/topic/772803-how-to-attach-altitude-encoders-to-dobsonians/)


## Under construction - Building guide for the ESP32 version:

* $3.05 NodeMCU ESP8266 development board (version 12E) [link](https://www.aliexpress.com/item/1pcs-lot-NodeMcu-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266-esp-12e-for-arduino/32775934156.html)
* $4.20 LSM303DLHC sensor module [link](https://www.aliexpress.com/item/1-pcs-GY-511-LSM303DLHC-Module-E-Compass-3-Axis-Accelerometer-3-Axis-Magnetometer-Module-Sensor/1956617486.html)
* $17.99 Signswise 600p/r Incremental Rotary Encoder DC5-24v 6mm shaft [link](https://www.amazon.com/gp/product/B00UTIFCVA)
* $9.99 85 teeth GT2 timing pulley 10mm shaft [link](https://www.aliexpress.com/item/POWGE-1pcs-85-Teeth-GT2-Timing-Pulley-Bore-5-6-35-8mm-for-width-6mm-GT2/32773386105.html)
* $0.82 20 teeth Gt2 timing pulley 6.35mm shaft [link](https://www.aliexpress.com/item/20tooth-Bore-6-35mm-GT2-Synchronous-Pulley-Aluminium-Timing-Gear-For-Width-6mm-Belt-3D-Printers/32808150854.html)
* $1.05 GT2 timing  belt (length depends on your telescope size), I used 400mm for the Z114 [link](https://www.aliexpress.com/item/Free-Shipping-3D-printer-belt-closed-loop-rubber-GT2-timing-belt-400-2GT-6-teeth-100/32477498985.html)

Add some solder, cables, a 5V power source, a couple resistors, and screws for attaching the encoder to the base whichever way you want. A maker can build this DIY DSC for much less than the cost of two high resolution optical encoders and a NexusDSC.

The key to this new version of my DSC is the use of an inexpensive optical encoder for azimuth. The $17.99 encoder I used has 600ppr, which using quadrature produces 2400 counts per revolution, which would not be engough for a DSC, but using GT2 timing pulleys of 85 and 20 teeth (for a ratio of 4.25 to 1) we can now get 10200 counts per revolution on azimuth, for just a fraction of the price of a 10k encoder. 

This is how the GT2 pulleys and belt look in the base of my Z114:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/dobDSC-upclose.jpg "Pulleys")

For simplicity and cost savings, altitude is driven by the same high-res accelerometer I used in my previous DSC, the LSM303DLHC which has more than enough resolution to match the azimuth encoder.

The microcontroller is a very inexpensive ESP8266, I used the nodeMCU variant which seems to be tolerant of the 5V inputs from the encoder. You can use any 5V power source you want, I'm using a power bank:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/dobDSC-back.jpg "Back")

The large box is the power bank, the smaller box is housing the main circuit with the ESP8266.

## Circuit

The circuit, is very very simple:

ESP32 version:
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/Circuit_ESP32.png "ESP32 Circuit")

ESP8266 version:
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/encoder.png "ESP8266 Circuit")

You can ask questions or provide feedback [here](https://www.cloudynights.com/topic/589521-37-dobsonian-dsc-for-diy-makers/).
