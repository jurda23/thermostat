/****************************************************************
                            SD karta
****************************************************************/

// Inicializace
void SDinit()
{
  Serial.println("Inicializace SD karty...");
  if(!SD.begin(4))
  {
    lcd1.clear();
    lcd1.print("Chyba karty!");
    Serial.println("Chyba karty!");
    delay(1000);
  }
  
  // Karta musi obsahovat soubor teploty.txt
  if(!SD.exists("teploty.txt"))
  {
    lcd1.clear();
    lcd1.print("Soubor nenalezen");
    Serial.println("Soubor teploty.txt nenalezen!");
    delay(1000);
  }
  
  // Karta musi obsahovat soubor zpravy.txt
  if(!SD.exists("zpravy.txt"))
  {
    lcd1.clear();
    lcd1.print("Soubor nenalezen");
    Serial.println("Soubor zpravy.txt nenalezen!");
    delay(1000);
  }
}

////////////////////////////////////////////////////////////////
//               Obsluha souboru teploty.txt                  //
////////////////////////////////////////////////////////////////

// Zapis teplot a casoveho razitka
void ulozTeploty()
{
  File dataFile = SD.open("teploty.txt", FILE_WRITE);
  
  if(dataFile)
  {
    //lcd.clear();
    //lcd.print("Zapisuji teplotu");
    dataFile.print(timeStamp(true, true));
    dataFile.print('\t');
    dataFile.print(Teplota1);
    dataFile.print('\t');
    dataFile.println(Teplota2);
    
    dataFile.close();
  }
  else
  {
    lcd1.clear();
    lcd1.print("Chyba zapisu!");
    Serial.println("Chyba zapisu na SD kartu!");
    delay(1000);
  }
}

// Zapis hlavicky k ukladanym datum do datalogu
void teplotyHlavicka()
{
  File dataFile = SD.open("teploty.txt", FILE_WRITE);
  
  if(dataFile)
  {
    if(dataFile.size() == 0)
    {
      dataFile.print("Datum a cas        ");
      dataFile.print("\t");
      dataFile.print("T_IN");
      dataFile.print("\t");
      dataFile.println("T_OUT");
     
      dataFile.close();
    }
  }
  else
  {
    lcd1.clear();
    lcd1.print("Chyba zapisu!");
    Serial.println("Chyba zapisu hlavicky na SD kartu!");
    delay(1000);
  }
}

// Odesle datalog s teplotami do konzole - znak po znaku
void sendTeploty()
{
  File dataFile = SD.open("teploty.txt");
  
  if(dataFile)
  {
    Serial.println("Obsah datalogu teplot:");
    Serial.println("************************");
    while(dataFile.available())
    {
      Serial.write(dataFile.read());
    }
    Serial.println("************************");
    Serial.println("");
    dataFile.close();
  }
  else
  {
    Serial.println("Chyba cteni souboru s datalogem");
  }
}

// Vymazani souboru s teplotami
void clearTeploty()
{
  SD.remove("teploty.txt");
  File dataFile = SD.open("teploty.txt", FILE_WRITE);
  if(dataFile)
  {
    dataFile.close();
    Serial.println("Obsah datalogu teplot byl vymazan!");
  }
  else
  {
    Serial.println("Doslo k chybe!");
  }
} 

////////////////////////////////////////////////////////////////
//                Obsluha souboru zpravy.txt                  //
////////////////////////////////////////////////////////////////

// Zapis zpravy a casoveho razitka
void ulozZpravu(String zprava)
{
  File dataFile = SD.open("zpravy.txt", FILE_WRITE);
  
  if(dataFile)
  {
    //lcd.clear();
    //lcd.print("Zapisuji zpravu");
    dataFile.print(timeStamp(true, true));
    dataFile.print('\t');
    dataFile.println(zprava);
    dataFile.close();
  }
  else
  {
    lcd1.clear();
    lcd1.print("Chyba zapisu!");
    Serial.println("Chyba zapisu na SD kartu!");
    delay(1000);
  }
}

// Zapis hlavicky k ukladanym zpravam do datalogu
void zpravyHlavicka()
{
  File dataFile = SD.open("zpravy.txt", FILE_WRITE);
  
  if(dataFile)
  {
    if(dataFile.size() == 0)
    {
      dataFile.print("Datum a cas        ");
      dataFile.print("\t");
      dataFile.println("Zprava");
      dataFile.close();
    }
  }
  else
  {
    lcd1.clear();
    lcd1.print("Chyba zapisu!");
    Serial.println("Chyba zapisu hlavicky ke zpravam na SD kartu!");
    delay(1000);
  }
}

// Odesle datalog se zpravami do konzole - znak po znaku
void sendZpravy()
{
  File dataFile = SD.open("zpravy.txt");
  
  if(dataFile)
  {
    Serial.println("Obsah datalogu zprav:");
    Serial.println("************************");
    while(dataFile.available())
    {
      Serial.write(dataFile.read());
    }
    Serial.println("************************");
    Serial.println("");
    dataFile.close();
  }
  else
  {
    Serial.println("Chyba cteni souboru se zpravami");
  }
}

// Vymazani souboru se zpravami
void clearZpravy()
{
  SD.remove("zpravy.txt");
  File dataFile = SD.open("zpravy.txt", FILE_WRITE);
  if(dataFile)
  {
    dataFile.close();
    Serial.println("Obsah datalogu zprav byl vymazan!");
  }
  else
  {
    Serial.println("Doslo k chybe!");
  }
} 
  
