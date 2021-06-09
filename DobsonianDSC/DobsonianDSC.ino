/*
  Dual Encoder Digital Setting Circles for ESP32 microcontrollers

  This is a simple adapter to connect two inexpensive incremental optical encoders
  via WiFi and/or BlueTooth to astronomy apps such as SkySafari,
  in order to provide "Push To" style features to dobsonian style telescope mounts.

  Copyright (c) 2017-2021 Vladimir Atehortúa. All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the version 3 GNU General Public License as
  published by the Free Software Foundation.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.
  If not, see <http://www.gnu.org/licenses/>
*/

/**
    Hardware used:
    ESP-32S Development Board, I used a generic one: https://www.aliexpress.com/item/32800930387.html?
    Two Optical Encoders with NPN (a.k.a. "N channel") "Open Collector" (a.k.a. "open drain") output, I used some 600 p/r generic ones: https://www.aliexpress.com/item/32669741048.html
    Dupont cables or other suitable connectors.
    Power supply (could be a 5V USB power bank)

    ESP32 pinout:
     IMPORTANT: Only encoders with NPN Open collector outputs can be connected directly to the pins of the ESP32. Other encoders might require level shifters.
     AZ_Encoder_A = GPIO18 = D18  (or change it in the #define code below)
     AZ_Encoder_B = GPIO19 = D19  (or change it in the #define code below)
     ALT_Encoder_A = GPIO25 = D25 (or change it in the #define code below)
     ALT_Encoder_B = GPIO26 = D26 (or change it in the #define code below)
     VIN = Encoder VCC (and if you don't use a USB power bank, this would also connect to your 5V power source)
     GND = Encoder GND
*/

/**
   Required Additional Board Managers for the Arduino IDE (File->Preferences):
   https://dl.espressif.com/dl/package_esp32_index.json

   Required libraries for the Arduino IDE (Tools -> Manage Libraries):
   ESP32Encoder by Kevin Harrington, see https://github.com/madhephaestus/ESP32Encoder
   ArduinoJson by Benoit Blanchon, see https://arduinojson.org/
*/

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <ESP32Encoder.h>
#include "WebConfig_DSC.h"
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define MAX_SRV_CLIENTS         3   // How many clients can connect simultaneously to the DSC.

// Choose which pins of the ESP32 to use for the Azimuth Encoder
ESP32Encoder AZencoder;
#define PIN_AZ_A 18 // Important: Not all encoders can be connected directly to the pins of the ESP32, read more about this in the project's github page
#define PIN_AZ_B 19

// Choose which pins of the ESP32 to use for the Altitude Encoder
ESP32Encoder ALTencoder;
#define PIN_ALT_A 25
#define PIN_ALT_B 26

BluetoothSerial SerialBT;

String params = "["
                "{"
                "'name':'ssid',"
                "'label':'WiFi SSID Name',"
                "'type':" + String(INPUTTEXT) + ","
                "'default':''"
                "},"
                "{"
                "'name':'pwd',"
                "'label':'WiFi Password',"
                "'type':" + String(INPUTPASSWORD) + ","
                "'default':''"
                "},"
                "{"
                "'name':'btname',"
                "'label':'Bluetooth device Name',"
                "'type':" + String(INPUTTEXT) + ","
                "'default':'Telescope'"
                "},"
                "{"
                "'name':'azsteps',"
                "'label':'Azimuth Steps',"
                "'type':" + String(INPUTNUMBER) + ","
                "'min':1,'max':10000000,"
                "'default':'10000'"
                "},"
                "{"
                "'name':'alsteps',"
                "'label':'Altitude Steps',"
                "'type':" + String(INPUTNUMBER) + ","
                "'min':1,'max':10000000,"
                "'default':'10000'"
                "},"
                "{"
                "'name':'flpaz',"
                "'label':'Flip Azimuth',"
                "'type':" + String(INPUTCHECKBOX) + ","
                "'default':'1'"
                "},"
                "{"
                "'name':'flpalt',"
                "'label':'Flip Altitude',"
                "'type':" + String(INPUTCHECKBOX) + ","
                "'default':'1'"
                "},"
                "{"
                "'name':'apikey',"
                "'label':'Notification API Key (optional)',"
                "'type':" + String(INPUTTEXT) + ","
                "'max':35,"
                "'default':''"
                "},"
                "{"
                "'name':'userkey',"
                "'label':'Notification User Key (optional)',"
                "'type':" + String(INPUTTEXT) + ","
                "'max':35,"
                "'default':''"
                "}"
                "]";

WebServer server;
WiFiServer TCPserver(4030);                 // 4030 is the TCP port Skysafari usually expects for "Basic Encoder Systems"
WiFiClient serverClients[MAX_SRV_CLIENTS];
WebConfig conf;

boolean initWiFi() {
  boolean connected = false;
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.print(conf.values[0]);
  Serial.println(" SSID");
  if (conf.values[0] != "") {
    WiFi.begin(conf.values[0].c_str(), conf.values[1].c_str());
    uint8_t cnt = 0;
    while ((WiFi.status() != WL_CONNECTED) && (cnt < 20)) {
      delay(500);
      Serial.print(".");
      cnt++;
    }
    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("IP Adress:");
      Serial.println(WiFi.localIP());
      connected = true;
      // We can use the Pushover service to send a notification to your smartphone, an easy way to obtain the IP address that was assigned to the device:
      if (conf.getValue("apikey") != "" && conf.getValue("userkey") != "")
      {
        HTTPClient http;
        http.begin("https://api.pushover.net/1/messages.json");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        char _header[300];
        sprintf(_header, "token=%s&user=%s&message=Telescope-DSC connected to SSID:[%s] IP Address: [%s]", conf.getValue("apikey"), conf.getValue("userkey"), WiFi.SSID(), WiFi.localIP().toString().c_str());
        int httpResponseCode = http.POST(_header);
        http.end();
      }
    }
  }
  if (!connected) { // if unable to connect to an external WiFi, let's launch our own passwordless WiFi SSID:
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Telescope_DSC", "", 1);
  }
  return connected;
}

// method that handles the clicks on "SAVE" and "RESET" buttons on the web config form
void handleRoot() {
  conf.handleFormRequest(&server);
  if (server.hasArg("SAVE"))
  {
    uint8_t cnt = conf.getCount();
    for (uint8_t i = 0; i < cnt; i++)
    {
      Serial.print(conf.getName(i));
      Serial.print(" = ");
      Serial.println(conf.values[i]);
    }
  }
}

/**
   Configure encoders using the ESP32Encoder library by Kevin Harrington.
   This uses the ESP32's hardware pulse counters, not polling nor interrupts!
   In my tests, two encoders can get simultaneous quadrature pulses at 20Khz without missing a step.
*/
void setupEncoders()
{
  // It's very important to enable pull up resistors in order to work with the NPN open collector outputs:
  ESP32Encoder::useInternalWeakPullResistors = UP;

  // flip the pins used by Altitude encoder if the web configuration says so:
  if (conf.getBool("flpalt"))
  {
    ALTencoder.attachFullQuad(PIN_ALT_A, PIN_ALT_B);
  }
  else
  {
    ALTencoder.attachFullQuad(PIN_ALT_B, PIN_ALT_A);
  }
  ALTencoder.setFilter(0); // filters are only needed for cheap mechanical/switch encoders such as the Keyes KY-040, not by the 600p/s encoders

  // flip the pins used by Azimuth encoder if the web configuration says so:
  if (conf.getBool("flpaz"))
  {
    AZencoder.attachFullQuad(PIN_AZ_B, PIN_AZ_A);
  }
  else
  {
    AZencoder.attachFullQuad(PIN_AZ_A, PIN_AZ_B);
  }
  AZencoder.setFilter(0); // filters are only needed for cheap mechanical/switch encoders such as the Keyes KY-040, not by the 600p/s encoders

  // set starting count value after attaching
  ALTencoder.clearCount();
  AZencoder.clearCount();
}

void attendTcpRequests()  // handle connections from SkySafari and similar software via TCP on port 4030
{
  uint8_t i;
  // check for new clients trying to connect
  if (TCPserver.hasClient()) {
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      // find a free or disconnected spot:
      if (!serverClients[i] || !serverClients[i].connected()) {
        if (serverClients[i]) {
          serverClients[i].stop();
        }
        serverClients[i] = TCPserver.available();
        // the new client has connected
        break;
      }
    }
    // when there are no free/disconnected spots, reject the new client:
    if (i == MAX_SRV_CLIENTS) {
      WiFiClient serverClient = TCPserver.available();
      serverClient.stop();
    }
  }

  // check what the client sends for "Basic Encoder protocol" commands:
  for (i = 0; i < MAX_SRV_CLIENTS; i++)
  {
    if (serverClients[i] && serverClients[i].connected())
    {
      if (serverClients[i].available())
      {
        char character = serverClients[i].read(); // read the first character received, usually the command
        char response[30];
        switch (character)
        {
          case 'Q':   // the Query command, sent by SkySafari and others as the "Basic Encoder protocol" to query for encoder values.
            sprintf(response, "%lld\t%lld\t\n", AZencoder.getCount(), ALTencoder.getCount());
            serverClients[i].println(response);
            break;
          case 'H':   // 'H' - request for encoder resolution, e.g. 10000-10000\n
            snprintf(response, 20, "%u-%u", conf.getInt("azsteps"), conf.getInt("alsteps"));
            serverClients[i].println(response);
            break;
        }
      }
    }
  }
}

void attendBTRequests()   // handle connections from SkySafari and similar software via BlueTooth
{
  if (SerialBT.available()) {
    //WiFi.disconnect();
    //WiFi.mode(WIFI_OFF);

    char character = SerialBT.read();
    while (SerialBT.available())
    {
      SerialBT.read();  // flushing the buffer was necessary with Skysafari 5 Plus because it sent an initial "long" command.
    }
    Serial.print("BT: ");
    Serial.println(character);
    char response[30];
    switch (character)
    {
      case 'Q':   // the Query command, sent by SkySafari and others as the "Basic Encoder protocol" to query for encoder values.
        sprintf(response, "%lld\t%lld\t\n", AZencoder.getCount(), ALTencoder.getCount());
        Serial.print(response);
        SerialBT.println(response);
        break;
      case 'H':   // 'H' - request for encoder resolution, e.g. 10000-10000\n
        snprintf(response, 20, "%u-%u\n", conf.getInt("azsteps"), conf.getInt("alsteps"));
        Serial.print(response);
        SerialBT.println(response);
        break;
      default: SerialBT.print("\n");
    }
  }
}

/**
 * Arduino main setup method
 */
void setup() {
  Serial.begin(115200);
  Serial.println(params);
  conf.setDescription(params);
  conf.readConfig();
  initWiFi();
  char dns[30];
  sprintf(dns, "%s.local", conf.getApName());
  if (MDNS.begin(dns))
  {
    Serial.println("DNS active");
  }
  server.on("/", handleRoot);
  server.begin(80); // starts web server for configuration page

  TCPserver.begin(); // starts TCP server for skysafari via WiFi

  setupEncoders();

  if (conf.getValue("btname") != "")  // starts Bluetooth service only if a name has been configured for our device
  {
    SerialBT.begin(conf.getValue("btname"));
    Serial.println("BT started");
  }
}

void loop() 
{
  server.handleClient();
  attendBTRequests();
  attendTcpRequests();
}
