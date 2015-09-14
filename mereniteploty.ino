/****************************************************************
                        Mereni teploty
*****************************************************************

- Vyuziti cidel Dallas DS18B20
- Pravidelne mereni teploty v intervalu nastavitelnem promennou
  intervalMereniT
- Kazdou ctvrthodinu se vola ulozeni hodnot na SD kartu
  
*****************************************************************/

// Knihovny
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin pro pripojeni cidel
#define ONE_WIRE_BUS 32

// Cidla
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
DeviceAddress Cidlo1 = {0x28, 0xC0, 0x97, 0x8A, 0x06, 0x00, 0x00, 0x74};
DeviceAddress Cidlo2 = {0x28, 0x3E, 0x11, 0x8A, 0x06, 0x00, 0x00, 0x42};
DeviceAddress Cidlo3 = {0x28, 0x73, 0x9B, 0x89, 0x06, 0x00, 0x00, 0x83};
DeviceAddress Cidlo4 = {0x28, 0xFF, 0x34, 0xE0, 0x64, 0x15, 0x01, 0xEC};
DeviceAddress Cidlo5 = {0x28, 0xFF, 0x0A, 0xE1, 0x64, 0x15, 0x01, 0x45};
DeviceAddress Cidlo6 = {0x28, 0xFF, 0x43, 0xD2, 0x64, 0x15, 0x01, 0x9F};
DeviceAddress Cidlo7 = {0x28, 0xFF, 0x1F, 0xF5, 0x64, 0x15, 0x02, 0x3F};
DeviceAddress Cidlo8 = {0x28, 0xFF, 0x7F, 0xC2, 0x64, 0x15, 0x01, 0x02};
DeviceAddress Cidlo9 = {0x28, 0xFF, 0xA6, 0xAC, 0x64, 0x15, 0x01, 0x2A};
DeviceAddress Cidlo10 = {0x28, 0xFF, 0x30, 0xE0, 0x64, 0x15, 0x01, 0xF3};
// globalni promenne a konstanty

float Teplota1;
float Teplota2;
float Teplota3;
float Teplota4;
float Teplota5;
float Teplota6;
float Teplota7;
float Teplota8;
float Teplota9;
float Teplota10;
float dhtt;
float dhth;
float dhthic;
const unsigned int intervalMereniT =1000; // 1s
long posledniMereniT = 0;

// Inicializace mereni teploty - nastavi rozliseni
void mereniTeplotyInit()
{
  Serial.println("Inicializace mereni teploty...");
  sensor.begin();
    
      sensor.setResolution(Cidlo1, 12);
      sensor.setResolution(Cidlo2, 12);
      sensor.setResolution(Cidlo3, 12);
      sensor.setResolution(Cidlo4, 12);
      sensor.setResolution(Cidlo5, 12);
      sensor.setResolution(Cidlo6, 12);
      sensor.setResolution(Cidlo7, 12);
      sensor.setResolution(Cidlo8, 12);
      sensor.setResolution(Cidlo9, 12);
      sensor.setResolution(Cidlo10, 12);
}

// Aktualizuje udaj o teplote v globalnich promennych
void mereniTeploty()
{
  sensor.requestTemperatures();
 ;
  Teplota1 = sensor.getTempC(Cidlo1);
  Teplota2 = sensor.getTempC(Cidlo2);
  Teplota3 = sensor.getTempC(Cidlo3);
  Teplota4 = sensor.getTempC(Cidlo4);
  Teplota5 = sensor.getTempC(Cidlo5);
  Teplota6 = sensor.getTempC(Cidlo6);
  Teplota7 = sensor.getTempC(Cidlo7);
  Teplota8 = sensor.getTempC(Cidlo8);
  Teplota9 = sensor.getTempC(Cidlo9);
  Teplota10 = sensor.getTempC(Cidlo10);
  dhtt = dht.readTemperature();
  dhth = dht.readHumidity();
  dhthic = dht.computeHeatIndex(dhtt, dhth, false);
 
  posledniMereniT = millis();

}


// Kontrola, jestli neni treba udaje o teplote aktualizovat
void kontrolaMereniTeploty()
{
  //Serial.println("kontrola mereni teploty...");
  DateTime now = rtc.now();
  if(millis() > posledniMereniT + intervalMereniT)
  {
     mereniTeploty();
     if(now.minute() == 0 || now.minute() == 15 || now.minute() == 30 || now.minute() == 45 ) 
     {
       ulozTeploty();
     }
     if(zpravaPrectena)homeScreen();
  }
}




