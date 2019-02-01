<<<<<<< HEAD

/* Parametros de Control Automatico */
#define DRY_SOIL      15
#define WET_SOIL      66
=======
/* Automatic Control Parameters Definition */
#define DRY_SOIL      20
#define WET_SOIL      45
>>>>>>> e0f7f387a2edd7aa77bebf8762b23e9be140b082
#define COLD_TEMP     12
#define HOT_TEMP      26
#define TIME_PUMP_ON  30
#define TIME_LAMP_ON  15


/* Modulo DeepSleep */
uint32_t SLEEP_TIME = 140e6;  // Tiempo en modo deep-sleep en microsegundos

/* TIMER */
<<<<<<< HEAD
#define READ_BUTTONS_TM   1L  // el termino L corresponde a Segundos
#define READ_SOIL_TEMP_TM 2L  // 2L = 2 segundos 
#define READ_SOIL_HUM_TM  10L
#define READ_AIR_DATA_TM  2L
#define SEND_UP_DATA_TM   10L
#define AUTO_CTRL_TM      60L     
#define DEEP_SLEEP_TM     300L  
=======
#define READ_BUTTONS_TM   1L  // definitions in seconds
#define READ_SOIL_TEMP_TM 20L
#define READ_SOIL_HUM_TM  20L
#define READ_AIR_DATA_TM  20L
#define SEND_UP_DATA_TM   180L
#define AUTO_CTRL_TM      180L     
>>>>>>> e0f7f387a2edd7aa77bebf8762b23e9be140b082

/* OLED */
boolean turnOffOLED = 1;
#define SHOW_SET_UP   30

/* DHT22*/
#define DHTPIN D3  
#define DHTTYPE DHT22 
float airHum = 0;
float airTemp = 0;

/*  Humedad de Suelo */
#define soilMoisterPin A0
#define soilMoisterVcc D8
int soilMoister = 0;

<<<<<<< HEAD
/* DS18B20 Sensor de Temperatura */
#define ONE_WIRE_BUS 14 // DS18B20 en NodeMCU pin D5 corresponde to GPIO 014 on Arduino
=======
/* DS18B20 Temperature Sensor */
#define ONE_WIRE_BUS 14 // DS18B20 on NodeMCU pin D5 corresponds to GPIO 014 on Arduino
>>>>>>> e0f7f387a2edd7aa77bebf8762b23e9be140b082
float soilTemp;

/* Relays */
#define PUMP_PIN D6              //PUMP (Red LED)
#define LAMP_PIN D7              //LAMP (Green LED)
boolean pumpStatus = 0;
boolean lampStatus = 0;

<<<<<<< HEAD
/* Botones */
#define PUMP_ON_BUTTON D9        //push-button BOMBA (Red)
#define LAMP_ON_BUTTON D10       //push-button LAMPARA (Green)
#define SENSORS_READ_BUTTON D4   //push-button SENSOR (White)
=======
/* Buttons */
#define PUMP_ON_BUTTON D9        //push-button PUMP (Red)
#define LAMP_ON_BUTTON D10       //push-button LAMP (Green)
#define SENSORS_READ_BUTTON D4   //push-button SENSOR (yellow)
>>>>>>> e0f7f387a2edd7aa77bebf8762b23e9be140b082
