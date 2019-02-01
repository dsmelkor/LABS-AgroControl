/***************************************************
 * Obteniendo datos DHT 
 **************************************************/
void getDhtData(void)
{
  float tempIni = airTemp;
  float humIni = airHum;
  airTemp = dht.readTemperature();
  airHum = dht.readHumidity();
  if (isnan(airHum) || isnan(airTemp))   // Comprueba si alguna de las lecturas ha fallado y sale antes (para intentarlo de nuevo).
  {
    Serial.println("falla en leer sensor DHT!");
    airTemp = tempIni;
    airHum = humIni;
    return;
  }
}

/***************************************************
 * Obteniendo datos del sensor de Humedad de suelo
 **************************************************/
void getSoilMoisterData(void)
{
  soilMoister = 0;
  digitalWrite (soilMoisterVcc, HIGH);
  delay (500);
  int N = 3;
  for(int i = 0; i < N; i++) // leyendo sensor "N" veces y obteniendo promedio
  {
    soilMoister += analogRead(soilMoisterPin);   
    delay(150);
  }
  digitalWrite (soilMoisterVcc, LOW);
  soilMoister = soilMoister/N; 
  soilMoister = map(soilMoister, 600, 0, 0, 100); //LM393 on 5V (+Vin)
} 

/***************************************************
 * Obteniendo Temperatura del suelo
 **************************************************/
void getSoilTempData()
{
  DS18B20.requestTemperatures(); 
  soilTemp = DS18B20.getTempCByIndex(0);

  int newData = ((soilTemp + 0.05) * 10); // Fija el valor del suelo a 1 decimal.
  soilTemp = (newData / 10.0);
}
