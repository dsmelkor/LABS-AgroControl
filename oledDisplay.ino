/***************************************************
 * Iniciando OLED
 **************************************************/
void oledStart(void)
{
  Wire.begin();  
  oled.init();                      // Inicializando SSD1306 OLED display
  clearOledDisplay();
  //oled.setFont(font5x7);          //   Seteando tipo de fuente (default 8x8)
  oled.clearDisplay();              //   Limpiando Pantalla
  
  oled.setTextXY(0,0); oled.putString("    SANDIEGO");
  oled.setTextXY(1,0); oled.putString(String(SW_VERSION));  
  
  oled.setTextXY(2,0); oled.putString("AUTO CONTROL");
  oled.setTextXY(2,13); oled.putString(String(AUTO_CTRL_TM));
  oled.setTextXY(3,0); oled.putString("SUELO SECO");
  oled.setTextXY(3,13); oled.putString(String(DRY_SOIL));
  oled.setTextXY(4,0); oled.putString("TEMP FRIO");
  oled.setTextXY(4,13); oled.putString(String(COLD_TEMP));
  oled.setTextXY(5,0); oled.putString("TM_BOMBA_ON");
  oled.setTextXY(5,13); oled.putString(String(TIME_PUMP_ON));
  oled.setTextXY(6,0); oled.putString("TM_LAMP_ON");
  oled.setTextXY(6,13); oled.putString(String(TIME_LAMP_ON));
  oled.setTextXY(7,0); oled.putString("Sensores ==>>");
}

/***************************************************
 * Mosatrando datos en Display OLED
 **************************************************/
void displayData(void)
{ 
  String pumpStatusStr;
  String lampStatusStr;
  if (pumpStatus == 1) pumpStatusStr = "on ";
  if (pumpStatus == 0) pumpStatusStr = "off";
  if (lampStatus == 1) lampStatusStr = "on ";
  if (lampStatus == 0) lampStatusStr = "off";
  
  oled.setTextXY(2,0); oled.putString("                ");
  
  oled.setTextXY(3,0); oled.putString("TmpAire ");
  oled.setTextXY(3,7); oled.putString("         ");
  oled.setTextXY(3,8); oled.putString(String(airTemp));
  oled.setTextXY(3,14); oled.putString("'C");

  oled.setTextXY(4,0); oled.putString("HumAire ");
  oled.setTextXY(4,7); oled.putString("         ");
  oled.setTextXY(4,8); oled.putString(String(airHum));
  oled.setTextXY(4,14); oled.putString(" %");

  oled.setTextXY(5,0); oled.putString("TmpSuel ");
  oled.setTextXY(5,7); oled.putString("         ");
  oled.setTextXY(5,8); oled.putString(String(soilTemp));
  oled.setTextXY(5,14); oled.putString("'C");

  oled.setTextXY(6,0); oled.putString("HumSuel ");
  oled.setTextXY(6,7); oled.putString("         ");
  oled.setTextXY(6,8); oled.putString(String(soilMoister));
  oled.setTextXY(6,14); oled.putString(" %");

  oled.setTextXY(7,0); oled.putString("Riego <= ");
  oled.setTextXY(7,10); oled.putString("         ");
  oled.setTextXY(7,11); oled.putString(String(DRY_SOIL));

 // oled.setTextXY(7,7); oled.putString("  WET ");
 // oled.setTextXY(7,14); oled.putString(String(WET_SOIL));
}

/***************************************************
 * Borrando pantalla OLED
 **************************************************/
void clearOledDisplay()
{
  oled.setFont(font8x8);
  oled.setTextXY(0,0); oled.putString("                ");
  oled.setTextXY(1,0); oled.putString("                ");
  oled.setTextXY(2,0); oled.putString("                ");
  oled.setTextXY(3,0); oled.putString("                ");
  oled.setTextXY(4,0); oled.putString("                ");
  oled.setTextXY(5,0); oled.putString("                ");
  oled.setTextXY(6,0); oled.putString("                ");
  oled.setTextXY(7,0); oled.putString("                ");
  oled.setTextXY(0,0); oled.putString("                ");              
}
