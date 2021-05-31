# DobsonianDSC

Amateur astronomers want to know where their telescope is pointing at. For this reason, many commercial telescopes come equipped with "push to" or "go to" features, often based on high precision optical rotary encoders attached to the telescope mount, and a hand control device with a database of coordinates of thousands of stars and other sky objects.

There are also commercial Digital Setting Circles, which are kits sold for telescope owners to adapt to their existing telescope, in order to give it "push to" features. Commercial DSCs are very accurate, mostly based on magnetic or optical encoders, and usually cost a few hundred dollars.

This project is an implementation of Digital Setting Circles for dobsonian telescopes using inexpensive optical encoders and the ESP32 microcontroller.

This DSC achieves the following:

* Absolute minimum number of components, making it simple and inexpensive.
* Easy and inexpensive to build, no soldering required.
* Wireless communication with apps like SkySafari, DSO-Browser and others. No need for a wired handheld control.
* Ability to connect to an external WiFi (to maintain access to the internet while using the DSC)
* Ability to communicate the obtained IP address via Pushover notifications to smartphones.
* Web configuration page for easily configuring everything: WiFi settings/password, encoder resolutions, flipping encoder pins, notification API/keys.
* Bluetooth support.


## Under construction - guides:

  * The [Circuit Building Guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/Solderless.md) contains the details of the DSC circuit, including the parts list and step-by-step instructions on how to build a beginner-friendly solderless version.
  * The [Arduino IDE guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.md) provide beginner-friendly step by step instructions on how to install and configure the Arduino IDE on your computer, so that you can upload this software to an ESP-32 microcontroller.
  * Useful information on how to attach altitude encoders to dobsonians can be found [here](https://www.cloudynights.com/topic/772803-how-to-attach-altitude-encoders-to-dobsonians/)


## Pics:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/dobDSC-upclose.jpg "GT2 up close")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/components.jpg "GT2 up close")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/webConfig_sm.png "Web Configuration")

You can ask questions or provide feedback [here](https://www.cloudynights.com/topic/589521-37-dobsonian-dsc-for-diy-makers/).

