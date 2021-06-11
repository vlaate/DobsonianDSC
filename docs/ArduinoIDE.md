# Arduino IDE Beginners Guide

The purpose of this guide is to help someone who wants to build the Telescope DSC project, but who has never had any experience with Arduino, microcontrollers, or anything similar. As such, this guide is for the absolute beginner, and 
it will provide step by step instructions on how to install and configure the Arduino IDE on your computer, connect your microcontroller, and validate that things are working as intended. 

### 1. Download the Arduino IDE Software

Go to https://www.arduino.cc/en/software and download the Arduino IDE for your operating system. As of 2021 I recommend using the Version 1.8.15 or later.

### 2. Install

Launch the downloaded installer, make sure all the components are selected (they are by default, even the "USB driver") and let it complete installation:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/2.png "Installing IDE")

### 3. Launch IDE

Now that you have installed the Arduino IDE (Integrated Development Environment) you'll see a new Arduino icon on your computer. Use it to Launch the Arduino Integrated Development Environment. 

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/3.png "Launch IDE")

This is the software used to compile the arduino programs and upload them (via USB) to your ESP32 microcontroller. 

### 4. Add Board Manager URLs

For the Arduino IDE to be able to work with ESP32 and similar microcontrollers, it needs to download their "board manager".

To do this, in the top menu of the Arduino IDE select "File" -> "Preferences":

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/4.png "Add URLs")

In the emerging window there's a setting called "Additional Boards Manager URLs".

Put the following value in it:

```
https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

### 5. Install Board Managers

Click "OK" to close the preferences window, and back at the arduino top menu, select "Tools" -> "Board: XXX" -> "Boards Manager"

The boards manager window pops up. The text field is a search field. Type "ESP32" on it, and wait for the list of boards to update. When a board called "esp32 by Espressif Systems" shows up, click on it's "Install" button:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/5.png "Install ESP32 BM")

Once it's done installing, click the "Close" button.

### 6. Install Libraries

The Telescope DSC project depends on a couple of open source libraries. To install them, do the following:

In the top menu, select "Tools" -> "Manage Libraries"

The library manager window pops up. The text field is a search field. Type "ESP32Encoder" on it, and wait for the list of libraries to update. When a library called *"ESP32Encoder by Kevin Harrington"* shows up, click on it's "Install" button.

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/6.png "Install ESP32Encoder")

After the encoder library is installed, change the search field to "ArduinoJson" and look for a library called *"ArduinoJson by Benoit Blanchon"* and Install it too. When finished, close the library manager window.

### 7. Select Board

Now that your Arduino IDE is ready to compile programs for the ESP32 family of microcontrollers, it's time to configure it for your particular microcontroller.

In the top arduino menu, select "Tools" -> "Board: XXX" -> "ESP32 Arduino"

You will see a long list of ESP32 boards supported by the IDE. If you are going to use the ESP-32S Development Board that is recommended for the Telescope DSC project, then choose "ESP32 Dev Module". 

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/7.png "Select Board")

### 8. Configure Memory Partition Scheme

The telescope DSC project takes a lot of memory (mostly because bluetooth libraries are big).
In order to prevent a compilation error saying *"Sketch too big"*, you need to assign more of the microcontroller's memory to the app (and less to the filesystem).

So, in the top arduino IDE menu select "Tools" -> "Partition Scheme: XX" -> *"Huge App 3MB no OTA/1MB SPIFFS"*. This will prevent you from getting the error detailed above (orange text):

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/8.png "Sketch Too Big")

**Note:** Part of the reason why I recommended you to select the "ESP32 Dev Module" in a previous step was that a few other boards don't allow you to change partition scheme (for example the NoedMCU21-S does not allow it). If you decide to use a different board such as WROOM or a Wemos D1 ESP32, etc, look for Partition Scheme settings called "Huge App" or similar.

### 9. Connect the Microcontroller

Now it's time to tell your IDE how to communicate with your microcontroller device. Plug your USB cable to your ESP32 microcontroller, and plug the other end to your computer.

Under normal circumstances, the needed drivers should already be bundled with your operating system and automatically installed upon connecting the ESP board to the PC. If you are using an old OS, or run into problems, check the guide from Espressiff   (the ESP manufacturer) which contains links for drivers:

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html

### 10. Identify COM Port

Once the USB driver for the microcontroller ins properly installed, it's time to check that you can 
connect to it properly.

In the Arduino IDE top menu, select "Tools" -> "Port: XX"

You will see a list of serial ports (COM1, COM5, etc). You are supposed to choose the one that was assigned to your ESP32 microcontroller:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/10.png "Com Ports")

**¿How do I know which COM port is the one assigned to my USB-connected microcontroller?**

A simple way is: While the USB cable is still connected, take note of all the names on the ports list. Then click with your mouse somewhere else on the IDE so that the menu (and the list of com ports) is no longer visible. Then Unplug the USB cable. Then select "Tools" -> "Port: XX" again to view the list. Whichever name dissappeared from the list after unplugging the USB cable, that's the COM port that corresponds to your ESP32 microcontroller.

### 11. Validate USB Connection

Make sure your USB cable is plugged to both your ESP32 microcontroller and your computer.

Then in the Arduino IDE top menu, select "Tools" -> "Get Board Info"

You should see a small pop-up window that contains either the serial number of your microcontroller board, or the message *"SN: upload any sketch to obtain it"*:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/11.png "Board Info")

If you get a similar  message to this, all is OK. If you get a small message on the green bar saying "can't obtain info", try with a different COM port.

### 12. Creating a Test Sketch

Now we will use a very simple program ("sketch" in Arduino parlance) to verify that things are working properly.

In the Arduino IDE, select "File" - > "New"

In the new IDE window, paste the following sketch:

``` C
/** Simple Echo sketch to validate serial communication */
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
  Serial.println("Waiting for user message");
}

void loop()
{
  if (readLineFromSerial(buf) > 0)
  {
    Serial.print("Recieved: ");
    Serial.println(buf);
    Serial.println("\nWaiting for user message");
  }
}
```


Now select "File" -> "Save" and proceed to save the sketch somewhere in your computer.

Next step is to "upload" the sketch to the ESP32 microcontroller via the USB vable. To do this, you can either select "Sketch" -> "Upload" or click on the round icon with an arrow pointing right:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/12.png "Upload")

When you do this, the bottom part of the IDE (black background with orange text) will show a lot of messages from the compiling and uploading process. For this screenshot I enlarged the messages section, but it's normally just 3 lines tall:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/13.png "Uploaded")

When this is complete, the little green bar will contain the message "Done uploading." as seen on the screenshot.

If you get this message then all is well: the program has been compiled and uploaded to your ESP microcontroller. In fact, it's proably already being executed in the device.

If instead of *"Done uploading"* you see the message: "Connecting.....------...."* followed by *"Failed to connect to ESP32: Timed out waiting for packet header"*, this is solved by trying again (Click "Sketch" -> "Upload") and as soon as you see the *"Connecting"* message, hold down the physical button labeled "BOOT/FLASH" on the ESP32 bboar for a few seconds.

### 14. Validating the ESP32 microcontroller works

What the sketch you uploaded does, is recieve messages and respond with an echo. This will enable us to validate that the hardware is properly working, including the ESP32 microcontroller itself, and the USB connection to it.

To test this, select "Tools" -> Serial Monitor".

A small window shows up. At the bottom-right of the window, there is a combo-box. Use it to select "115200" which is the communication speed out test sketch expects to use:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/14.png "Baud Rate")

Now in the top of the serial monitor window, there's a text box. Type something into it (for example "Hello") and click the "Send" button.

You should see a reply from the microcontroller containing whatever text you sent, like this:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/15.png "Success")

You can type and send more messages, and the ESP32 should reply. This is evidence that the ESP32 board and the USB connection are working properly.

And that's it! If you got this far and things worked as described in the steps, then you've successfully set up your computer to program an ESP32 microcontroller, and you're ready for the next guide.




