# Uploading and Configuring the DSC Software

This guide will show you how to upload the DSC software to an ESP-32 microcontroller, and how to configure it for use.

It is recommended that you complete reading the [Arduino IDE Beginners Guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.md) to properly setup your develompent environment before following this guide.

## Downloading the DSC code

Once you have set up your computer with the Arduino IDE+board managers+libraries, use that computer's web browser to open the project GitHub page: [https://github.com/vlaate/DobsonianDSC](https://github.com/vlaate/DobsonianDSC)

In the web page you'll see a green button called "Code". If you click on it, you will see a menu with an option called "Download ZIP". Click on it!

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/download.png "Downloading Code")

Your computer will download a compressed file called "DobsonianDSC-master.zip". You need to extract the contents of this file to somewhere you want in your computer. On windows this can be easily done by right-clicking the file and selecting "Extract All".

After doing this, you should see a folder called "DobsonianDSC-master" in the location you chose to expand the zip file's contents. 

In the extracted contents, locate the following file:

```
DobsonianDSC-master\DobsonianDSC\DobsonianDSC.ino
```

Double click on the file to open it. The Arduino IDE should launch, making the contents of the file visible.

Plug your USB cable to your ESP32 microcontroller, and plug the other end to your computer. Make sure that your Arduino IDE is still properly configured, as was indicated in the [Arduino IDE Guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.md#9-connect-the-microcontroller). 

Follow the steps indicated in [step 13 of the Arduino guide](https://github.com/vlaate/DobsonianDSC/blob/master/docs/ArduinoIDE.md#13-uploading-the-sketch) to upload the code to the ESP32 board. It will take a while.


To validate that the upload was correct, you need to use a WiFi device (laptop, tablet or smartphone) to check the list of WiFi networks around you.

On the list you should see a new network called "Telescope_DSC". Connect to it.

Because this is the internal WiFi network of your DSC, it does not have a true connection to the internet. Be aware that some tablets and smartphones, after connecting to a WiFi network that lacks internet connection, will emit a warning like this:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/WiFi_NoInternet_C.png "WiFi without Internet")

Make sure to check out these notifications and to tell the device to stay connected to this wifi. Otherwise some phones/tablets disconnect automatically after a few seconds.

Once you have connected to the DSC's internal WiFi, point your web browser to http://192.168.4.1

You should see the Web Configuration page:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/webConfig_sm.png "Web Config")

## Configuring the DSC

In order to change the configuration of the DSC, you need to edit the appropriate fields in the web configuration page, and hit the "Save" button which will store them in permanent memory. For any changes to take effect immediately, you need to hit the "Restart" button, which will reboot the ESP-32.

### Encoders and Resolutions

The fields called *"Azimuth Steps"* and *"Altitude Steps"* can be used to let the DSC know the resolution of it's axis (calculated from encoder resolution and gear ratio), so that it can provide such information to apps like [SkySafari](https://skysafariastronomy.com/). This is quite convenient but optional, since you can also manually configure the resolution information directly in the apps.

**Flip Azimuth**: Sometimes it happens that after building the DSC electronic circuit and installing the encoders in your telescope, you find out that moving the telescope clockwise in azimuth shows up in skysafari as movement in the opposite direction. To reverse the direction of the Azimuth encoder you could swap the connections of the A and B cables from the Azimuth encoder, but to avoid having to make changes to the hardware, you can just check this *"Flip Azimuth"* option to reverse the direction of the Azimuth encoder if you need to.

**Flip Altitude**: As with altitude, if you happen to need to reverse the direction of the Altitude encoder, instead of swapping it's A and B cables you can just check this option.

### Bluetooth

The field called *"Bluetooth device Name"* lets you select the name your DSC will use when exposing it's bluetooth interface. Bluetooth is a very convenient way of connecting to the DSC, not just because it's wireless but also because it lets your smarphone/tablet stay connected to the internet.

After you give your DSC a Bluetooth name, click the *"Save"* button, and later the *"Restart"* button. It may take a while, but you should be able to pair your smartphone or tablet device with it.

**Note for Android users:** One thing that can be confusing about bluetooth on Android is that after pairing a device, a "connect" button might appear in the bluetooth menu but using it does not seem to do anything. It turns out that the Bluetooth connection needs to be requested by an App (such as Skysafari), and just clicking on "connect" will do nothing unless there is an app requesting bluetooth services. So, after pairing the DSC via bluetooth, to test it with an android device you should use Skysafari or a similar app.

**Note for iOS users:** It is known that SkySafari on many iOS devices cannot connect to serial devices via Bluetooth. For those phones/tablets the only option is to use WiFi.

### Configuring an External WiFi

When connecting to the DSC via WiFi, we often want to keep having access to the internet in the tablet/smartphone used to connect to it. One way to do this is to make your DSC connect to your existing WiFi, which could be your home's network, or a tethering HotSpot that you open with your smartphone when outside.

If you fill out the fields labeled *"WiFi SSID Name"* and *"WiFi Password"* and click "Save", where's what will happen:

Any time the DSC turns on, it will check if there's a value stored for those two fields. When there are no stored values (like when the DSC is brand new), it will launch it's own WiFi called "Telescope-DSC" and take the default IP address (192.168.4.1).

When there are stored values for WiFi name and password, the DSC will attept to connect to it. If it succeeds then all is well: you can connect to the DSC and to the internet using that WiFi network. If it fails to connect (for example: wrong password, or DSC is used on the field, far away from that WiFi network) then it will resort back to launching its own "Telescope-DSC" WiFi and take the 192.168.4.1 IP.

#### What's my IP?

One caveat of having your telescope DSC connect to a home network or other existing WiFi, is that the home's router will assign it a dynamic IP address, and you need a way to figure out this IP address so that you can connect to the DSC.

To help with that, this DSC software has an optional feature: After it successfully connects to a WiFi that has Internet access, it can send a notification to your smartphone telling you which IP address it was given.
This optional feature depends on an app called PushOver which is available for both Andoid and iOS. It's not free but it's inexpensive (and there's a 30 day trial).

If you want to use this feature, you'll need to install the PushOver app, create a PushOver account, and login to https://pushover.net/ to do the following steps:

When logged in to pushover.net, copy your *"user key"* from the top right of the screen:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/pushover_user_key.png "Pushover user")

... and paste it on the DSC web configuration page, to the field labeled *"Notification User Key"*.

Then in the pushover website, select the option to *"Create an Application/API Token"*: 

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/pushover_new_app.png "Pushover Create app")

... fill the form (essentially: give the app a name, such as "My Telescope") and click on *"Create Application"*. This will give you a new screen containing an API key for your DSC:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/pushover_api_key.png "Pushover API key")

Copy that API key, and paste it on the DSC web configuration page, to the field labeled *"Notification API Key"*.

If the values are correct, and the PushOver app is properly setup in your smartphone, then everytime the DSC is powered on and connects to an external WiFi, it will send you an notification to your mobile telling you it's IP address, which you will need to use to connect apps like SkySafari to the DSC, and also to acess the web configuration page.

## Connecting with SkySafari

The DSC is meant to be used with astronomy apps that support the "Basic Encoding System" protocol (a.k.a Intelliscope/BBox/Sky Wizard protocol). This guide will assume you are using [SkySafari](https://skysafariastronomy.com/).

**Note**: only Skysafari Plus and SkySafari Pro support connecting to telescopes, the vanilla "non Plus/Pro" version does not.

First, you need to make sure that your DSC is powered on and that you can connect to it's web configuration page.

In SkySafari, tap on the *"Settings"* icon and look for a section called *"Telescope"*. This contains an item called *"Setup"*:

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/Skysafari_3.png "SkySafari B")

For the *Scope Type*, select *"Basic Encoder System"*, and for the *Mount Type* select *"Alt-Az Push to"*

Here you should either indicate the values of the encoder steps per revolution, or (if you have configured them in the DSC's web configuration page) check the *"Get Automatically"* box so that SkySafari gets this data directly from the DSC.

![alt text](https://raw.githubusercontent.com/vlaate/DobsonianDSC/master/img/Skysafari_4.png "SkySafari C")

You should select either *"Connect via Bluetooth"* or *"Connect via WiFi"*.

If you select Bluetooth, make sure that Bluetooth is activated in your Smartphone/Tablet and that you have previously paired it with your DSC.

If you select WiFi, SkySafari will ask you to provide the IP address of the DSC, which is *192.168.4.1* if you are using the DSC's internal WiFi, or is a dynamic IP address if you are using a home/existing WiFi network.  Note that the *Port Number* should always be 4030.

Finally, you can close the Settings menu and in SkySafari's main screen select "Scope" and "Connect". After a second or two, you should hear a "ding" sound, indicating that SkySafari has succesffully connected to the telescope.

If you don't get the success "ding", check that you can still connect to the web configuration interface. As long as you can browse the web configuration page, you should be able to connect with SkySafari.

If you haven't yet built the circuit for the DSC, now is the right time to check the [Guide for Building the Circuit](https://github.com/vlaate/DobsonianDSC/blob/master/docs/Solderless.md).

### Alignment Tips

It's often recommended that you first use a bubble level to properly level the base of your dobsonian, to get more accuracy from the DSC.

Once SkySafari successfully connects to your DSC, it will initially assume that the telescope is pointing due north. You need to do the *Star Alignment* in order to get the DSC and SkySafari to properly display where your telescope is aimed at.

What you need to do is point the telescope at a known star, and center the star in the field of view of the eyepiece. In Skysafari, search and select the same star, and tap *"Align"*. Now the SkySafari screen should be showing where your telescope is aimed at, as you move it.

SkySafari now also lets you perform a second alignment with another star (hopefully one that's far away from the first star). This is called 2-star alignment, and it reduces the need to level the telescope mount base, and improves accuracy.

To do this, just repeat the alignment process with a second star, choosing *"Align"* rather than *"Restart Alignment"* when asked by SkySafari. Doing this second star alignment will allow SkySafari to have a better model of the mount and more accurately display where your telescope is pointed at.

**Note:** Although it seems that you can align on more stars, SkySafari only remembers the two most recent alignments.

The first time you do this process, you might discover at this point that when moving the telescope in one direction, SkySafari shows it moving in the opposite direction. To fix this, go to the DSC's web configuration page, and change the **Flip Azimuth** and **Flip Altitude** options to reverse the direction of either encoder.
