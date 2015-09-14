


/*******************************************************************************
                                Webovy server
********************************************************************************

- Pro Arduino Mega + Ethernet Shield

- Funkce serveru:
  * Mereni vnitrni a venkovni teploty pomoci cidel DS18B20
  * Zaznam teplot na SD kartu kazdych 15 minut s casovym udajem z RTC.
    Namerene hodnoty si lze nechat vypsat bud do konzole nebo na web stranku.
  * Ovladani LED pomoci tlacitek weboveho formulare.
  * Odeslani kratke zpravy z web stranky primo na LCD displej serveru
    - maximalne 32 znaku. Tyto zpravy se rovnez archivuji do souboru na SD karte.
  * Soubor se zaznamy teplot a zprav lze prikazem vymazat pres konzoli,
    aby nebylo nutné vyjimat kartu.

- Prikazy pro ovladani z konzole (vzdy jen jeden znak):
  "t" - vypise datalog teplot
  "c" - smaze datalog teplot
  "z" - vypise datalog zprav
  "r" - smaze datalog zprav
  "u" - ulozi aktualni teplotu na SD kartu

- Pavel Juricek 05.09.2015

******************************************************************************/

// Knihovny

#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <EthernetUdp.h>
#include <LiquidCrystal.h>
#include <MemoryFree.h>
#include <Wire.h>
#include "RTClib.h"
#include <avr/pgmspace.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address
// LED a tlacitka
#define ZelenaLED 2
#define ModraLED 3
#define rele1 A0
#define rele2 A5

#define tlacitko1 digitalRead(5)
#define tlacitko2 digitalRead(6)
uint32_t nextIteration = 0;
uint8_t displayPage = 0;
boolean zacatekCteni = false;



#define DHTPIN 33
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "a85218ab48c44c38b65581456a3a53e1";

//znak pro stupen "o"
byte stupen[8] = {
  0b00110,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// Nastaveni knihovny pro Ethernet
// definice MAC adresy, IP a portu - 80 je default pro HTTP
byte arduino_mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0xC4, 0x36 };
IPAddress server_ip ( 192,  168,   99,  150);
IPAddress arduino_ip (192,  168,   99,  20);
IPAddress dns_ip     (  8,   8,   8,   8);
IPAddress gateway ( 192,   168,   99,   1);
IPAddress mask(255, 255, 255,   0);
 unsigned int localPort = 8888;             // local port to listen for UDP packets
byte timeServer[] = {
      193, 79, 237, 14};    // ntp1.nl.net NTP server 

const int NTP_PACKET_SIZE= 48;             // NTP time stamp is in the first 48 bytes of the message

    byte pb[NTP_PACKET_SIZE];                  // buffer to hold incoming and outgoing packets


EthernetServer arduinoServer(80);
EthernetClient pripojenyClient;

// Hodiny realneho casu
RTC_DS1307 rtc;

// globalni promenne a konstanty
boolean ModraLEDon = false;
boolean zpravaPrectena = true;
byte sampledata=50;            //some sample data - outputs 2 (ascii = 50 DEC)             
int ledPin = 4;  // LED pin
//char link[]="http://teplomer.juricekpavel.net:82/rele.html"; //link data
//String readString = String(30); //string for fetching data from address
//boolean LEDON = false; //LED status flag

////////////////////////////////////////////////////
// Inicializace vseho potrebneho pro chod serveru //
////////////////////////////////////////////////////
void setup()
{
  
//  EthernetUdp.begin(localPort);
  // Vstupy a vystupy
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(ZelenaLED, OUTPUT);
  pinMode(ModraLED, OUTPUT);
//   pinMode(A0, OUTPUT);
//  pinMode(A5, OUTPUT);
 pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
digitalWrite(rele1, HIGH);
digitalWrite(rele2, HIGH);



  // Inicializace seriove komunikace a LCD displeje
  Serial.begin(115200);
  //lcd.begin(16, 4);
  lcd1.begin(20, 4);
//  lcd.createChar(1, stupen);     // sestavíme si vlastní znak "stupeň"
  //


  // Pripojeni k ethernetu
  Serial.println("Inicializace pripojeni k ethernetu...");
  Ethernet.begin(arduino_mac, server_ip, gateway, mask);
  arduinoServer.begin();
dht.begin();


  // RTC, SD karta, mereni teploty

  rtcStart();
  SDinit();
  teplotyHlavicka();
  zpravyHlavicka();
  mereniTeplotyInit();
  mereniTeploty();
  homeScreen();
  HTMLteploty_start();
  termostat();
RELE();
  // Info do konzole
  Serial.print("Arduino server je na IP adrese: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Volna RAM = ");
  Serial.println(getFreeMemory());
  Serial.println(" B");
  Serial.println("---------------------------------------------");
  Serial.println();
}

////////////////////////////////////////////////////
//                   Hlavni smycka                //
////////////////////////////////////////////////////
void loop() {
  termostat();

  // Stisknuti tlacitka smaze displej s prijatou zpravou
  // a zobrazi domaci obrazovku
  if (tlacitko1)
  {
    zpravaPrectena = true;
    homeScreen();
    while (tlacitko1)delay(10);
  }
// {
//buttonState = digitalRead(tlacitko2);
// if (buttonState != lastButtonState) {
//        // jestliže se stav změnil, navyšte hodnotu počítadla
//        if (buttonState == HIGH)
//        buttonPushCounter++;
//      }
//
//  if (buttonPushCounter % 4 == 0) {
//        digitalWrite(ModraLED, LOW);
//    } else {
//        digitalWrite(ModraLED, HIGH);
//    }
//}



        
    
  // Obsluha prikazu z konzole
  if (Serial.available())
  {
    byte prikaz = Serial.read();
    if (prikaz == 't')sendTeploty();
    if (prikaz == 'c') {
      clearTeploty();
      teplotyHlavicka();
    }
    if (prikaz == 'z')sendZpravy();
    if (prikaz == 'r') {
      clearZpravy();
      zpravyHlavicka();
    }
    if (prikaz == 'u')ulozTeploty();
  }

  // Pripojeny klient - pokud nejaky existuje,
  // je treba ho obslouzit
  pripojenyClient = arduinoServer.available();
  if (pripojenyClient)
  {
    obsluhaKlienta();
  }

  // kontrola, jestli neni treba aktualizovat udaje o teplote
  kontrolaMereniTeploty();
}


////////////////////////////////////////////////////
//           Obsluha pripojeneho klienta          //
////////////////////////////////////////////////////
void obsluhaKlienta()
{
  Serial.println("Novy klient!");
  Serial.println("");
  digitalWrite(ZelenaLED, LOW);
  // http pozadavek konci prazdnym radkem
  boolean currentLineIsBlank = true;
  // Prvni radek obsahuje data z formulare (metoda GET)
  boolean current_line_is_first = true;
  String prvniRadek = "";

  while (pripojenyClient.connected())
  {
    // k dispozici data od klienta
    if (pripojenyClient.available())
    {
      char prijato = pripojenyClient.read();
      Serial.write(prijato);

      // Pokud dorazil znak pro novy radek (LF - linefeed = \n)
      // a zaroven je aktualni radek prazdny -> http pozadavek skoncil
      // a lze odeslat odpoved
      if (prijato == '\n' && currentLineIsBlank) {
        vyhodnoceni_get(prvniRadek);
        break;
      }

      // Novy radek - zatim je prazdny, ale uz neni prvni
      if (prijato == '\n') {
        currentLineIsBlank = true;
        current_line_is_first = false;
      }

      // Pokud prislo cokoliv jineho, nez carrige return (\r), radek uz neni prazdny
      else if (prijato != '\r') currentLineIsBlank = false;

      // Pokud se jedna o prvni radek http pozadavku,
      // ulozi ho do stringu pro pozdejsi vyhodnoceni
      if (current_line_is_first) prvniRadek = prvniRadek + prijato;
    }
  }

  delay(1);
  pripojenyClient.stop();
  Serial.println("Klient odpojen");
  Serial.print("Volna RAM = ");
  Serial.print(getFreeMemory());
  Serial.println(" B");
  Serial.println("---------------------------------------------");
  Serial.println();
  digitalWrite(ZelenaLED, HIGH);
}






