# Sistema automatico de riego para huerta
 basado en ARDUINO con NodeMCU ESP8266 and an IoT app, the BLYNK.


> Resumen: 
capturamos información de una plantación, temperatura y humedad , tanto del aire como del suelo. 
En base a esos datos, el sistema decidirá la cantidad correcta que la plantación debe recibir calor y agua. 
Además, el proyecto permite la intervención manual de un operador para controlar una bomba de agua y una lámpara eléctrica para generar calor para la plantación. 
La intervención manual puede ser tanto local como remota a través de Internet.
#### Estos son las entradas:

Sensors:

 - Air Temperature
 - Air Relative 
 - Humidity Soil 
 - Temperature Soil 
 - Moisture (humidity)


Buttons:

- Pump ON/OFF
- Lamp ON/OFF


#### Estas son las salidas del sistema:

Perisfericos:
  
- Relay for Pump control
- Relay for Lamp control



Avisos:
  
Mensajes automaticos enviados como eventos:
    
- Pump ON
- Lamp On
- System Off line
    
    
    
Datos del Display:

- Datos digitales y analogos mostrados en pantalla
  


Data Storage
  
- Estos datos se deberan guardar en un repo remoto
 

###  Instalacion:
'''
** OLED **
  Its is a I2C display, so we will connect it to the NodeMCU I2C pins, using:
SCL ==> D1 (5)
SDA ==> D2 (4)
The SSD1306 can be powered with 5V (external) or 3.3V directly from the NodeMCU module. The first option was the chosen one (5V).
Once we have connected the display, let's download and install its library on our Arduino IDE. We will use the ACROBOT library version:
https://github.com/acrobotic/Ai_Ardulib_SSD1306

** DHT22 ** 
VCC (we will connect to 3.3V from NodeMCU);
Data out;
Not connected and
Ground.

The sensor should be powered between 3.3V and 5V and will work from -40oC to +80oC 
https://github.com/adafruit/DHT-sensor-library

** MOISTURE SENSOR ** 
The LM393 module has 2 outputs, one digital (D0) that can be set-up using the potentiometer that exist on it and an analog one (A0). This module can be sourced with 3.3V, what is very convenient when working with an NodeMCU. What we will do, is install the LM393 4 pins as bellow:

LM393 A0 output to A0 NodeMCU A0 input
LM393 VCC to NodeMCU VCC or to NodeMCU GPIO D3*
LM393 GND to NodeMCU GND
LM393 D0 open

It's important to highlight that the correct is to connect the Sensor VCC to a Digital Pin as output, so the LM393 will be powered only when we need a read. This is important no only to save power, but also to protect the probes from corrosion.
the NodeMCU did not worked well the soilMoisterVcc PIN connected, connect powered the LM393 direct to VCC (5V)

** TEMP SENSOR DS18B20 ** 
it good to use even over long distances! The sensor works from 3.0 to 5.0V.

The sensor has 3 wires:
  Black: GND
  Red: VCC
  Yellow: 1-Wire Data 
  
  In order to use the DS18B20 properly, two libraries will be necessary: (Install both libraries in your Arduino IDE Library depository)
    1- OneWire  https://github.com/adafruit/ESP8266-Arduino/tree/esp8266/libraries/OneWire
    2 - DallasTemperature https://github.com/milesburton/Arduino-Temperature-Control-Library
 
 ** LEDs ** 
 Note that LEDs connected on NodeMCU, are for testing only. They will "simulate", the Pump (Red LED) and the Lamp (Green LED). 
 For the final circuity the Relays will connected to those outputs as described on the next Step.
 
 ** BUTTONS ** 
 Pump and/or Lamp. For that, three push-buttons will be incorporate to the project:

RED: Pump Manual Ctrl
GREEN: Lamp manual Ctrl
WHITE: Sensor Read Button (To update sensors, "light on" the OLED and present data 


** BLINK ** 
It is really very easy to built IoT projects using BLYNK. The first you need is to have the BLINK App installed on you phone its Library on the Arduino IDE. If you do not have them yet, please follow the bellow steps:

Download BLYNK app for Apple Iphone or Google Android
Install BLYNK Library for Arduino. Note that you will download the zip file (There are 5 files there that you must manually install in your Arduino Library).
Once the Arduino IDE is reloaded, you should be OK to start using BLINK on your IoT project.
Now, let's open our app at the SmartPhone:

Open Blynk app.Tap on "Create New Project" screen
Give a name for your project (For example "ArduFarmBot 2")
Select the appropriated Hardware Model: "NodeMCU"
Take note from Authorization Token (you can e-mail it to you to ease copy&past on your code)
Press "OK". A Blank screen with dots will appear.
Tap the Screen to open the "Widget Box"
OK, let's take a moment and think about our ArduFarmBot 2 Blynk App and define what will be the Widgets to be installed. Revisiting the general specification at introduction, we can summarize that our app we be needed for:

Read all Sensors and verify the actuators status
Take remote actions, "turning on/off" Pump and Lamp
Sending messages when the System is "off-line" and/or an actuator is ON
Record the general sensors data
In order to organize things, let's split the above "tasks" in 3 tabs:

SENSORS
ACTUATORS / CONTROL
GRAPHICS
"Tabs" will be the first Widget to be installed. Enter on it and define the above "Tab names"

Next, go to each Tab and install the Widgets as described bellow:

SENSORS
Gauge: "Temp Air [oC]" Blue; input: V10 0 to 50; frequency: 5 sec
Gauge: "Humidity Air [%]" Green; input: V11 0 to 100; frequency: 5 sec
Gauge: "Soil Humidity [%]" Red; input: V12 0 to 100; frequency: 5 sec
Gauge: "Soil Temperature[oC]" Yellow; input: V13 -10 to 50; frequency: 5 sec
LED: "PUMP" Red; V0
LED: "LAMP" Green; V1
ACTUATORS / CONTROL
Button: "PUMP" Red; output: V3 0 to 1; mode: Switch; label: on: ACT, off: OK
Button: "LAMP" Green; output: V4 0 to 1; mode: Switch; label: on: ACT, off: OK
LED: "PUMP" Red; V0
LED: "LAMP" Green; V6
Notifications: Notify When HW goes offline: ON
GRAPHICS
Data to Show:
V10 "Temp Air"
V11 "Humidity Air"
V12 "Soil Humidity "
V13 "Soil Temp"
'''

