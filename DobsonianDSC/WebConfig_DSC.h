/*
  Original file: WebConfig.h version 1.4
  Author Gerald Lechner lechge@gmail.com https://github.com/GerLech
  Licensed under the GNU Lesser General Public License v3.0

  This library builds a web page with a smart phone friendly form to edit
  a free definable number of configuration parameters. The submitted data will be stored in the SPIFFS
  The library works with ESP8266 and ESP32

  It has been modified by Vladimir Atehortúa to customize the HTML styles for 
  astronomy/night use (dark background with red colors) for the Digital Setting Circles project
  which is released under the compatible GPLv3
  
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

#ifndef WebConfig_h
#define WebConfig_h

#include <Arduino.h>
#if defined(ESP32)
  #include <WebServer.h>
#else
  #include <ESP8266WebServer.h>
#endif

//maximum number of parameters
#define MAXVALUES 20

//maximum number of options per parameters
#define MAXOPTIONS 15

//character limits
#define NAMELENGTH 20
#define LABELLENGTH 40

//name for the config file
#define CONFFILE "/WebConf.conf"

#define INPUTTEXT 0
#define INPUTPASSWORD 1
#define INPUTNUMBER 2
#define INPUTDATE 3
#define INPUTTIME 4
#define INPUTRANGE 5
#define INPUTCHECKBOX 6
#define INPUTRADIO 7
#define INPUTSELECT 8
#define INPUTCOLOR 9
#define INPUTFLOAT 10
#define INPUTTEXTAREA 11
#define INPUTMULTICHECK 12
//number of types
#define INPUTTYPES 13

#define BTN_CONFIG 0
#define BTN_DONE 1
#define BTN_CANCEL 2
#define BTN_DELETE 4
//data structure to hold the parameter Description
typedef //Struktur eines Datenpakets
struct  {
  char name[NAMELENGTH];
  char label[LABELLENGTH];
  uint8_t type;
  int min;
  int max;
  uint8_t optionCnt;
  String options[MAXOPTIONS];
  String labels[MAXOPTIONS];
} DESCRIPTION;

class WebConfig {
public:
  WebConfig();
  //load form descriptions
  void setDescription(String parameter);
  //Add extra descriptions
  void addDescription(String parameter);
  //function to respond a HTTP request for the form use the filename
  //to save.
#if defined(ESP32)
  void handleFormRequest(WebServer * server, const char * filename);
  //function to respond a HTTP request for the form use the default file
  //to save and restart ESP after saving the new config
  void handleFormRequest(WebServer * server);
  //get the index for a value by parameter name
#else
  void handleFormRequest(ESP8266WebServer * server, const char * filename);
  //function to respond a HTTP request for the form use the default file
  //to save and restart ESP after saving the new config
  void handleFormRequest(ESP8266WebServer * server);
  //get the index for a value by parameter name
#endif
  int16_t getIndex(const char * name);
  //read configuration from file
  boolean readConfig(const char *  filename);
  //read configuration from default file
  boolean readConfig();
  //write configuration to file
  boolean writeConfig(const char *  filename);
  //write configuration to default file
  boolean writeConfig();
  //delete configuration file
  boolean deleteConfig(const char *  filename);
  //delete default configutation file
  boolean deleteConfig();
  //get a parameter value by its name
  const String getString(const char * name);
  const char * getValue(const char * name);
  int getInt(const char * name);
  float getFloat(const char * name);
  boolean getBool(const char * name);
  //get the accesspoint name
  const char * getApName();
  //get the number of parameters
  uint8_t getCount();
  //get the name of a parameter
  String getName(uint8_t index);
  //Get results as a JSON string
  String getResults();
  //Ser values from a JSON string
  void setValues(String json);
  //set the value for a parameter
  void setValue(const char*name,String value);
  //set the label for a parameter
  void setLabel(const char * name, const char* label);
  //remove all options
  void clearOptions(uint8_t index);
  void clearOptions(const char * name);
  //add a new option
  void addOption(uint8_t index, String option);
  void addOption(uint8_t index, String option, String label);
  //modify an option
  void setOption(uint8_t index, uint8_t option_index, String option, String label);
  void setOption(char * name, uint8_t option_index, String option, String label);
  //get the options count
  uint8_t getOptionCount(uint8_t index);
  uint8_t getOptionCount(char * name);
  //set form type to doen cancel
  void setButtons(uint8_t buttons);
  //register onSave callback
  void registerOnSave(void (*callback)(String results));
  //register onSave callback
  void registerOnDone(void (*callback)(String results));
  //register onSave callback
  void registerOnCancel(void (*callback)());
  //register onSave callback
  void registerOnDelete(void (*callback)(String name));

  //values for the parameter
  String values[MAXVALUES];
private:
  char _buf[2000];
  uint8_t _count;
  String _apName;
  uint8_t _buttons = BTN_CONFIG;
  DESCRIPTION _description[MAXVALUES];
  void (*_onSave)(String results) = NULL;
  void (*_onDone)(String results) = NULL;
  void (*_onCancel)() = NULL;
  void (*_onDelete)(String name) = NULL;
};

#endif
