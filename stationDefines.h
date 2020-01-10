/* Parametros de Control Automatico */
int DRY_SOIL = 25;
int WET_SOIL = 60;
#define COLD_TEMP     12
#define HOT_TEMP      26
#define TIME_PUMP_ON  60
#define TIME_LAMP_ON  15


/* Modulo DeepSleep */
uint32_t SLEEP_TIME = 140e6;  // Tiempo en modo deep-sleep en microsegundos

/* TIMER */
#define READ_BUTTONS_TM   1L  // el termino L corresponde a Segundos
#define READ_SOIL_TEMP_TM 2L  // 2L = 2 segundos 
#define READ_SOIL_HUM_TM  10L
#define READ_AIR_DATA_TM  2L
#define SEND_UP_DATA_TM   10L
#define AUTO_CTRL_TM      60L     
#define DEEP_SLEEP_TM     60L  // un minuto



/* OLED */
boolean turnOffOLED = 1;
#define SHOW_SET_UP   30

/* DHT22*/
#define DHTPIN D3  
//#define DHTTYPE DHT22 
#define DHTTYPE DHT11 
float airHum = 0;
float airTemp = 0;

/*  Humedad de Suelo */
#define soilMoisterPin A0
#define soilMoisterVcc D8
int soilMoister = 0;


/* DS18B20 Sensor de Temperatura */
#define ONE_WIRE_BUS 14 // DS18B20 en NodeMCU pin D5 corresponde to GPIO 014 on Arduino
float soilTemp;

/* Relays */
#define PUMP_PIN D6              //PUMP (Red LED)
#define LAMP_PIN D7              //LAMP (Green LED)
boolean pumpStatus = 0;
boolean lampStatus = 0;
boolean deepSleepStatus = 0;


/* Botones */
#define PUMP_ON_BUTTON D9        //push-button BOMBA (Red)
#define LAMP_ON_BUTTON D10       //push-button LAMPARA (Green)
#define SENSORS_READ_BUTTON D4   //push-button SENSOR (White)

/* DeepSleep */
uint32_t TIEMPO_DeepSleep = 5e6;  // setea Tiempo deep-sleep en microsegundos

#define POWER_BUTTON D0        //encendido
