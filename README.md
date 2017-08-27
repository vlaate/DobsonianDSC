# DobsonianDSC

Amateur astronomers want to know where their telescope is pointing at. For this reason, many commercial telescopes come equipped with "push to" or "go to" features, often based on high precision optical rotary encoders attached to the telescope mount, and a hand control device with a database of coordinates of thousands of stars and other sky objects.

There are also commercial Digital Setting Circles, which are kits sold for telescope owners to adapt to their existing telescope, in order to give it "push to" features. Commercial DSCs are very accurate, mostly based on optical encoders, and usually cost a few hundred dollars.

This project is an implementation of a simple Digital Setting Circles, that evolves from my previous DSC project, but now using an inexpensive optical encoder (and GT2 timing belt+gear) instead of the magnetometer.

This DSC achieves the following:

* Easy and inexpensive to build, for a DIY maker or Arduino enthusiast.
* Can be attached to dobsonian mounts, included tabletops.
* High resolution: 10200 counts per resolution (compare to the 11,748 counts per revolution of the Skywatcher Goto Dobs)
* Instead of a wired handheld control, it communicates with Android/iOS apps like Skysafary 5 (plus or pro), DSC-Browser and others via WiFi.

My prototype is a removable version installed on a Zhumell Z114 tabletop:
![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/dobDSC-front.jpg "Finished look")
You can see I'm using a woodworking clamp to affix the encoder in the position required to have proper tension in the timing belt. This way, the DSC is very easy to remove from the scope without leaving any permanent marks.

## Parts list:

* $3.05 NodeMCU ESP8266 development board (version 12E)[link](https://www.aliexpress.com/item/1pcs-lot-NodeMcu-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266-esp-12e-for-arduino/32775934156.html)
* $4.20 LSM303DLHC sensor module [link](https://www.aliexpress.com/item/1-pcs-GY-511-LSM303DLHC-Module-E-Compass-3-Axis-Accelerometer-3-Axis-Magnetometer-Module-Sensor/1956617486.html)
* $17.99 Signswise 600p/r Incremental Rotary Encoder DC5-24v 6mm shaft [link](https://www.amazon.com/gp/product/B00UTIFCVA)
* $9.99 85 teeth GT2 timing pulley 10mm shaft [link](https://www.aliexpress.com/item/POWGE-1pcs-85-Teeth-GT2-Timing-Pulley-Bore-5-6-35-8mm-for-width-6mm-GT2/32773386105.html)
* $0.82 20 teeth Gt2 timing pulley 6.35mm shaft  https://www.aliexpress.com/item/20tooth-Bore-6-35mm-GT2-Synchronous-Pulley-Aluminium-Timing-Gear-For-Width-6mm-Belt-3D-Printers/32808150854.html
* 1.05 GT2 timing  belt (size depends on your telescope size), I used 400mm for the Z114 [link]https://www.aliexpress.com/item/Free-Shipping-3D-printer-belt-closed-loop-rubber-GT2-timing-belt-400-2GT-6-teeth-100/32477498985.html

Subtotal parts cost: $37.1

Add some solder, cables, a 5V power source, and screws for attaching the encoder to the base whichever way you want. The cost still, is low compared to the cost of high resolution optical encoders and a NexusDSC.

The key to this new version of my DSC is the use of an inexpensive optical encoder for azimuth. The $17.99 encoder I used has 600ppr, which using quadrature produces 2400 counts per revolution, which would not be engough for a DSC, but using GT2 timing pulleys of 85 and 20 teethm (for a ratio of 1 : 4.25) we can now get 10200 counts per revolution on azimuth, for just a fraction of the price of a 10k encoder. This is how the GT2 pulleys and belt look in the base of my Z114:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/dobDSC-upclose.jpg "Pulleys")

For simplicity and cost savings, altitude is driven by the same high-res accelerometer I used in my previous DSC, the LSM303DLHC which has more than enough resolution to match the azimuth encoder.

The microcontroller is a very inexpensive ESP8266, I used the nodeMCU variant which seems to be tolerant of the 5V inputs from the encoder. You can use any 5V power source you want, I'm using a power bank:

The large box is the power bank, the smaller box is housing the main circuit with the ESP8266:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/dobDSC-back.jpg "Back")

And the circuit, is very very simple:

![alt text](https://github.com/vlaate/DobsonianDSC/blob/master/encoder.png "Circuit")

I've tried it successfully with my Z114 telescope (from now on, my Z114i). The accuracy is on par to that of my Skywatcher goto mount. 

The source code released here is open source, you need the arduino IDE to compile and deploy it to your microcontroller.
