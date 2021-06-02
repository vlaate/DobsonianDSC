# DobsonianDSC

Amateur astronomers want to know where their telescope is pointing at. For this reason, many commercial telescopes come equipped with "push to" or "go to" features, often based on high precision optical rotary encoders attached to the telescope mount, and a hand control device with a database of coordinates of thousands of stars and other sky objects.

There are also commercial Digital Setting Circles, which are kits sold for telescope owners to adapt to their existing telescope, in order to give it "push to" features, costing a few hundred dollars.

This project is an open source implementation of Digital Setting Circles for dobsonian telescopes using inexpensive optical encoders and the ESP32 microcontroller, with the goal of enabling amateur astronomers to build their own DSC system.

Particular emphasis has been placed on making sure anybody can build the circuit regardless of their experience (or lack thereof) with electronics or arduino, including a step-by-step guide for a very simple implementation that requires no soldering.

This DSC achieves the following:

* Absolute minimum number of components, making it simple and inexpensive.
* Easy to build, no soldering required.
* Wireless communication with apps like SkySafari Plus/Pro. No need for a wired handheld control.
* Ability to connect to an external WiFi (to maintain access to the internet while using the DSC)
* Ability to communicate the obtained IP address via notification to smartphones.
* Web configuration page for easily configuring everything: WiFi settings/password, encoder resolutions, flipping encoder pins, notification API/keys, device name.
* Bluetooth support.

This is what it looks like installed on a small tabletop dobsonian:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/full.jpg "Mini Dob with DSC")


## Documentation

  * This [Arduino IDE guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.md) will provide beginner-friendly step by step instructions on how to install and configure the Arduino IDE on your computer, including the board managers and libraries required by the DSC, so that you can upload this software to an ESP-32 microcontroller.
  * This [Upload and Configuration guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/UploadConfigure.md) provides step by step insrtuctions on how to upload the DSC software to the ESP32 microcontroller, how to configure the DSC using it's web configuration interface, and how to connect the SkySafari app to it.
  * The [Circuit Building Guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/Solderless.md) contains the circuit schematics, the parts list and a step-by-step instructions on how to build a **beginner-friendly solderless** version.
  * You can ask questions or provide feedback in the [CloudyNights forums](https://www.cloudynights.com/topic/589521-37-dobsonian-dsc-for-diy-makers/).
  * Useful information on how to attach altitude encoders to dobsonians can be found [here](https://www.cloudynights.com/topic/772803-how-to-attach-altitude-encoders-to-dobsonians/)

## Pics:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/full_close.jpg "Close up AZ")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/Alt_encoder_1.jpg "Alt Encoder 1")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/Alt_encoder_2.jpg "Alt Encoder 2")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/components.jpg "Components")
![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/img/webConfig_sm.png "Web Configuration")


