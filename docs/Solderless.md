# Building the DSC Circuit

There are many ways to build the electronic circuit for this telescope DSC.

This guide will focus on a very simple and solderless way to assemble the components, so that even people who don't own a soldering iron (or don't know how to use one) can build the DSC for their telescope.


## Parts List

There are very few components involved in this dual encoder DSC:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/components.jpg "Parts List")

  * Two optical encoders with NPN open-collector outputs (discussed in more detail further below).
  * One "30 pin" ESP32 development board ([aliexpress](https://www.aliexpress.com/item/32800930387.html), [amazon](https://www.amazon.com/dp/B079PVCF2G)).
  * One keyes screw shield v2 ([keyestudio.com](https://www.keyestudio.com/products/keyes-screw-shield-v2-stud-terminal-expansion-board-double-support), [aliexpress](https://www.aliexpress.com/item/2030646961.html)).
  * A set of 10 Dupont Cables 10cm long, either male-to-female or female-to-female ([aliexpress](https://www.aliexpress.com/item/32798042976.html)).

Before you go on assembling the circuit, make sure you have already uploaded the software to the ESP-32.


## The Circuit

The circuit for this DSC is very simple. The logical view tells you it's basically about connecting the 4 wires from each encoder to the ESP32 microcontroller:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/Circuit_ESP32S.png "Logic Circuit")

To make those connections easily and without needing to use a soldering iron, we'll use the *"keyes screw shield v2"* which is a small module that offers screw terminals and adapts them to dupont connectors:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/keyes_screw_shield.jpg "keyes screw shield")

The following diagram explains how the wiring should go from the ESP32 to this "screw terminal shield", and also shows which "green screw" terminals corresponds to which "black dupont" connectors:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/solderless.jpg "Solderless Circuit")

  * Note that there 4 screw terminals labeled "**GND**", you can use any of them to connect the black GND wires from the optical encoders.
  * Note that there are 2 screw terminals labeled "**5V**", you can use any of them to connect the red 5V wires from the optical encoders.
  * The **A (Yellow)** and a **B (Green)** wires from the Azimuth encoder should go into the green screw terminals labeled **A0**, **A1**.
  * The **A (Yellow)** and a **B (Green)** wires from the Altitude encoder should go into the green screw terminals labeled **A2**, **A3**.

After plugging the encoder wires into the appropriate screw terminals (green), you can use dupont cables to connect the dupont terminals (black) to the corresponding pins of the ESP-32, like this:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/connected_2.jpg "Solderless")

Make sure you are using the correct pins of the ESP-32: 
  * The red 5V dupont connection should go to the ESP32 pin labeled **VIN**.
  * The black GND dupont connection should go to the ESP32 pin labeled **GND**.
  * The A and B connections from the A0 and A1 screw terminals should go to the ESP32 pins labeled **D18** and **D19**.
  * The A and B connections from the A2 and A3 screw terminals should go to the ESP32 pins labeled **D25** and **D26**.

And that's it! If the connections are correct and the ESP32 was already programmed with the software, then the circuit is complete.


## About Encoders

The resolution of your DSC will depend upon the resolution of the optical encoders you choose, and the gear ratio with which you affix those encoders to your telescope's axis.

For encoders attached *directly* to the telescope axis (without any gear reduction), Encoders with resolutions of **2000 p/r** to **2500 p/r** are recommended. This will provide between 8.000 to 10.000 steps in a full circle, or between 2.2 and 2.7 arcminutes per step. 

For encoders connected to the telescope via some sort of gear reduction (such as GT2 gears and belt) the cheaper **600 p/r** encoders are sufficient, and for example attached through GT2 gears at a 4,25 gear ratio (85 teeth big gear to 20 teeth small gear) they will provide (600 * 4 * 4,25 = 10.200) 10.200 steps per full circle, or 2.1 arcminutes per step.

In order to make this circuit as simple as possible, the optical encoders to be used **must** have **"NPN open-collector outputs"**. Encoders with other type of outputs (for example: *"Line Driver output"*) are not suited for this simple circuit and will require additional hardware such as level shifters.

The most common encoder useable for this DSC project is the *Signswise / BQLZR* 600 p/r and it's generic clones. It's recommended to look for the mention of *"NPN open-collector"* in the vendor's page when dealing with generic ones. ([aliexpress](https://www.aliexpress.com/item/32669741048.html)) 

There seems to be a [source](https://www.aliexpress.com/item/32961497880.html) for higher resolution OMRON E6B2-CWZ6C encoders (of up to 2500 p/r) but I've not personally tested them. Note that only the CWZ6C family is NPN open-collector, other references (CWZ5B, CWZ3E, CWZ1X) are not. ([datasheet](http://www.ia.omron.com/data_pdf/cat/e6b2-c_ds_e_6_1_csm491.pdf))

If you are going to use GT2 gears, remember that the shaft width is 6mm for the Signswise, BQLZR and OMRON E6B2.

If you know of other suitable encoders, you can let us know at the [CloudyNights forum](https://www.cloudynights.com/topic/589521-37-dobsonian-dsc-for-diy-makers/)


## About Different versions of the ESP-32

The ESP32 microcontroller comes in different versions. This guide features the one with 30 pins / GPIOs, but there are versions with 38 pins, versions in the UNO form factor and in the Wemos Mini form factor, among others. Any version of the ESP32 can be used, but the pinouts illustrated in this guide are for the 30 pin version, so a beginer might be better off using exactly the 30 pin development board.


## About Battery Power

The ESP32 boards typically come with a micro-USB connector, so USB power banks are the easiest solution to power the DSC.

In order to use power sources with a DC barrel plug, such as the popular Talentcell 12V rechargeable batteries, or a 9V rechargeable with a plug adapter, there's a small module that can be used:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/battery_options.jpg "Battery")

That little [blue module](https://www.aliexpress.com/item/32806774850.html) can take any voltage from 7V to 12V and output 5V (and more than enough mA for the ESP32 and two encoders). so you can use it to power the DSC by connecting the "VIN" pin rfom the ESP32 and the red "5V" cable from the screw shield to the "5V OUT" pins of the blue module, and also the black GND cable from the screw shield plus the GND pin of the ESP32 to the GND pin of the blue module.

It's not actually efficient because to drop the voltage to 5V, some energy must be wasted into heat, but it can be convenient, specially if you don't already own an USB power bank.
