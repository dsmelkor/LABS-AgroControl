/***************************************************************************************************************
 *  AgroControl utiliza NodeMCU ESP-12 Develop Kit V1.0
 *  DHT se conecta a NodeMCU pin D3 (Temperatura Ambiente y Humedad Relativa)
 *  Humedad de Suelo se conecta a A0
 *  los datos de sensores se visualizan en Display OLED
 *  Los comandos en el control son mediante botones 
 *  OLED Display por defecto estará apagado. 
 *  Presionar el boton de sensores para tomar datos y visualizarlos en el Display
 *  Nueva funcion "waitButtonPress (int waitTime)", para parar el Loop inicial
 *  Se muestra la configuracion automatica al iniciar el display
 *  Los datos de sensores se envian a BLYNK
 *  Los comandos de contros son recibidos desde BLYNK
 *  Deepsleep, El tiempo que está el microprocesador en reposo es de 140*10^6 us = 140 segundos.
 *  
 *  Descargas, tutoriales y docs: http://www.blynk.cc
 *  Blynk licensed under MIT license
 *       
 *  Modificado por DSMELKOR Basado en proyecto "Automatic and Remote Control Developed by MJRovai"
 ********************************************************************************************************************************/
#define SW_VERSION "   SW Ver. 3.0" // VErsion a mostrar en el Display
#include "stationDefines.h"       //   Definiciones del proyecto
#include "stationCredentials.h"   // Credenciales de acceso Blynk

/* ESP & Blynk */
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
WidgetLED PUMPs(V0);  // Feedback de señales de sensores en Blynk App
WidgetLED PUMPa(V5); //  Feedback de señales de controles en Blynk App
WidgetLED LAMPs(V1);  // Feedback de señales de sensores en Blynk App
WidgetLED LAMPa(V6); //  Feedback de señales de controles en Blynk App


/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;

/* OLED */
#include <ACROBOTIC_SSD1306.h> // libreria para OLED: SCL ==> D1; SDA ==> D2
#include <SPI.h>
#include <Wire.h>

/* DHT22*/
#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);

/* DS18B20  Sensor de Temperatura */
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("agroContro");
  Serial.println(".... comenzando Setup");
  Serial.println(" ");

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(PUMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(LAMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(SENSORS_READ_BUTTON, INPUT_PULLUP);
  pinMode(soilMoisterVcc, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  oledStart();
  dht.begin();
  DS18B20.begin();

  PUMPs.off();
  LAMPs.off();
  PUMPa.off();
  LAMPa.off();
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(LAMP_PIN, LOW);
  digitalWrite (soilMoisterVcc, LOW);
  
  waitButtonPress (SHOW_SET_UP); // esperando para que un boton sea presionado 
  oled.clearDisplay();
  startTimers();
}

void loop()
{
  timer.run(); // Iniciando SimpleTimer
  Blynk.run();
}

/****************************************************************
* Leer comandos remotos 
****************************************************************/
BLYNK_WRITE(3) // Control remoto de la Bomba
{
  int i=param.asInt();
  if (i==1) 
  {
    pumpStatus = !pumpStatus;
    aplyCmd();
  }
}

BLYNK_WRITE(4) // Control remoto de la Lampara
{
  int i=param.asInt();
  if (i==1) 
  {
    lampStatus = !lampStatus;
    aplyCmd();
  }
}

/****************************************************************
* Leer comandos Locales (Boton de bomba y lampara normalmente abiertos "HIGH"):
****************************************************************/
void readLocalCmd() 
{  
  boolean digiValue = debounce(PUMP_ON_BUTTON);
  if (!digiValue) 
  {
    pumpStatus = !pumpStatus;
    aplyCmd();
  }

  digiValue = debounce(LAMP_ON_BUTTON);
  if (!digiValue) 
  {
    lampStatus = !lampStatus;
    aplyCmd();
  }

  digiValue = debounce(SENSORS_READ_BUTTON);
  if (!digiValue) 
  {
    turnOffOLED = !turnOffOLED;
    if (!turnOffOLED)
    {
      oled.setTextXY(0,0); oled.putString("ACTUALIZANDO ");
      oled.setTextXY(1,0); oled.putString("SENSORES");
      getDhtData();
      getSoilMoisterData();
      getSoilTempData();
      oledStart();
      displayData();
    }else oled.clearDisplay();
  }
}

/***************************************************
* Recibiendo comandos y notificando a Blink y activando perisfericos
****************************************************/
void aplyCmd()
{
  if (pumpStatus == 1) 
  {
    Blynk.notify("agroControl: Warning ==>> Bomba ON"); 
    digitalWrite(PUMP_PIN, HIGH);
    if (!turnOffOLED) displayData();
    PUMPs.on();
    PUMPa.on();
  }
  else
      {
        digitalWrite(PUMP_PIN, LOW);
        if (!turnOffOLED) displayData();
        PUMPs.off();
        PUMPa.off();
      }
  
  if (lampStatus == 1) 
  {
    Blynk.notify("agroControl: Warning ==>> Lampara ON");
    digitalWrite(LAMP_PIN, HIGH);
    if (!turnOffOLED) displayData();
    LAMPs.on();
    LAMPa.on();
  }
  else
      {
        digitalWrite(LAMP_PIN, LOW);
        if (!turnOffOLED) displayData();
        LAMPs.off();
        LAMPa.off();
      }

  if (deepSleepStatus == 1)
  {
    //ESP.deepSleep(TIEMPO_DeepSleep, WAKE_RF_DEFAULT); // Calibración de señal de radio si es necesario 
    ESP.deepSleep(TIEMPO_DeepSleep, WAKE_RFCAL);      // Calibración de señal de radio siempre
    //ESP.deepSleep(TIEMPO_DeepSleep, WAKE_NO_RFCAL);   // Sin calibración de la señal de radio
    //ESP.deepSleep(TIEMPO_DeepSleep, WAKE_RF_DISABLED);  // Desabilita la señal de radio después del reencendido

  }
  else
      {
        Blynk.notify("agroControl: Warning ==>> deepSleep OFF");
      }
}

/***************************************************
* Control Automatico basado en la lectura de sensores
****************************************************/
void autoControlPlantation(void)
{ 
  if (soilMoister < DRY_SOIL) 
  {
    turnPumpOn();
  }

  if (airTemp < COLD_TEMP) 
  {
    turnLampOn();
  }
}

/***************************************************
* Encendiendo bomba por un cierto tiempo 
****************************************************/
void turnPumpOn()
{
  pumpStatus = 1;
  aplyCmd();
  delay (TIME_PUMP_ON*1000);
  pumpStatus = 0;
  aplyCmd();
}

/***************************************************
* Encendiendo lámpara por un cierto tiempo 
****************************************************/
void turnLampOn()
{
  lampStatus = 1;
  aplyCmd();
  delay (TIME_LAMP_ON*1000);
  lampStatus = 0;
  aplyCmd();
}

/***************************************************
 * Enviando datos a Blink
 **************************************************/
void sendUptime()
{
  Blynk.virtualWrite(10, String(airHum,2) + " %");     // Mostrando con un solo decimal y agregando letra C
  Blynk.virtualWrite(11, String(airTemp, 1) + " ºC");  // Mostrando con un solo decimal y agregando letra C
  Blynk.virtualWrite(12, soilMoister); // virtual pin V12
  Blynk.virtualWrite(13, soilTemp); //virtual pin V13
}

/***************************************************
 * Durmiendo la bestia (uControlador)
 **************************************************/
void deepsleep()
{
  pumpStatus = 0;
  aplyCmd();
    delay (TIME_LAMP_ON*1000);
  deepSleepStatus = 1;
  aplyCmd()
}
