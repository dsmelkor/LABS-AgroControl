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
 
***

[Aqui la info extra necesaria para la instalación - WIKI](https://github.com/dsmelkor/LABS-AgroControl/wiki) 
