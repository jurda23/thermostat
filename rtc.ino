/****************************************************************
                      Hodiny realneho casu
****************************************************************/

// Inicializace komunikace a kontrola, jestli hodiny bezi
void rtcStart()
{
  Serial.println("Inicializace RTC...");
  Wire.begin();
  rtc.begin();
  
  if (!rtc.isrunning()) 
  {
    Serial.println("RTC nebezi! Udaj o case neni aktualni.");
    lcd1.clear();
    lcd1.print("RTC nebezi!");
    // Nastaveni data a casu - konstanty obsahuji cas, kdy je kod kompilovan
   rtc.adjust(DateTime(__DATE__, __TIME__));
    delay(1000);
  }
}

// Generovani casoveho razitka ve stringu. Pomoci parametru 
// lze zvolit, zda bude obsahovat datum a sekundy
String timeStamp(boolean datum, boolean sek)
{
  // Definice oddelovacu jednotlivych udaju
  const char oddCasu = ':';
  const char oddData = '.';
  const char oddDatCas = ' ';
  
  DateTime now = rtc.now();
  
  // Osetreni situaci, kdy je udaj pouze jednomistny
  // -> doplni se nulou
  String den = String(now.day());
  if(now.day() < 10) den = '0' + den;
  
  String mesic = String(now.month());
  if(now.month() < 10) mesic = '0' + mesic;
  
  String rok = String(now.year());
  if(now.year() < 10) rok = '0' + rok;
  
  String hodiny = String(now.hour());
  if(now.hour() < 10) hodiny = '0' + hodiny;
  
  String minuty = String(now.minute());
  if(now.minute() < 10) minuty = '0' + minuty;
  
  String sekundy = String(now.second());
  if(now.second() < 10) sekundy = '0' + sekundy;
  
  // Slozeni stringu podle parametru
  String aktualniCas;
  if(datum) aktualniCas = den + oddData + mesic + oddData + rok + oddDatCas + hodiny + oddCasu + minuty;
  else aktualniCas = hodiny + oddCasu + minuty;
  if(sek) aktualniCas = aktualniCas + oddCasu + sekundy;
    
  return aktualniCas;
}
  
