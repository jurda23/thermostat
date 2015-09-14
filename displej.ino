/****************************************************************
                        Obsluha LCD displeje
****************************************************************/

// domaci obrazovka serveru
void homeScreen()
{
if (nextIteration < millis()) {
    // LCD init
//    lcd.clear();
//    lcd.setCursor(0, 0);
lcd1.clear();
    lcd1.setCursor(0, 0);
    // respektive pro display to bude asi takto:
    if (displayPage == 0) {
        // dispay I
//        lcd.print("Bazen:   ");
//        lcd.print(Teplota1);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 1);
//        lcd.print("B_Ohrev: ");
//        lcd.print(Teplota2);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 2);
//        lcd.print("TUV:     ");
//        lcd.print(Teplota3);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0,3);
//        lcd.print(timeStamp(true,true));
        
        lcd1.print("Bazen:      ");
        lcd1.print(Teplota1);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 1);
        lcd1.print("Bazen_Ohrev:");
        lcd1.print(Teplota2);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 2);
        lcd1.print("TUV:        ");
        lcd1.print(Teplota3);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0,3);
        lcd1.print(timeStamp(true,false));

    } else if (displayPage == 1) {
        // display II
//        lcd.print("Topeni:  ");
//        lcd.print(Teplota4);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 1);
//        lcd.print("Solar:   ");
//        lcd.print(Teplota5);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 2);
//        lcd.print("Venek:   ");
//        lcd.print(Teplota6);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 3);
//        lcd.print("Garaz:   ");
//        lcd.print(Teplota7);
//        lcd.write(1);
//        lcd.print("C");

        lcd1.print("Topeni:  ");
        lcd1.print(Teplota4);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 1);
        lcd1.print("Solar:   ");
        lcd1.print(Teplota5);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 2);
        lcd1.print("Venek:   ");
        lcd1.print(Teplota6);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 3);
        lcd1.print("Garaz:   ");
        lcd1.print(Teplota7);
        lcd1.print((char)223);
        lcd1.print("C");
        
    } else if (displayPage == 2) {
        // display III
//        lcd.print("Cidlo5:  ");
//        lcd.print(Teplota8);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 1);
//        lcd.print("Cidlo6:  ");
//        lcd.print(Teplota9);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 2);
//        lcd.print("Cidlo7:  ");
//        lcd.print(Teplota10);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0,3);
//        lcd.print(timeStamp(true,true));

        lcd1.print("Cidlo5:  ");
        lcd1.print(Teplota8);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 1);
        lcd1.print("Cidlo6:  ");
        lcd1.print(Teplota9);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 2);
        lcd1.print("Cidlo7:  ");
        lcd1.print(Teplota10);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0,3);
        lcd1.print(timeStamp(true,false));
    }
    else if (displayPage == 3){
        // display IV
//        lcd.print("DhtTep:  ");
//        lcd.print(dhtt);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 1);
//        lcd.print("Vlhkost:");
//        lcd.print(dhth);
//        lcd.print("%Rh");
//        lcd.setCursor(0, 2);
//        lcd.print("TepIndex:");
//        lcd.print(dhthic);
//        lcd.write(1);
//        lcd.print("C");
//        lcd.setCursor(0, 4);
//        lcd.print(timeStamp(true,true));

        lcd1.print("DhtTeplota: ");
        lcd1.print(dhtt);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 1);
        lcd1.print("Vlhkost:");
        lcd1.print(dhth);
        lcd1.print("%Rh");
        lcd1.setCursor(0, 2);
        lcd1.print("TepIndex:");
        lcd1.print(dhthic);
        lcd1.print((char)223);
        lcd1.print("C");
        lcd1.setCursor(0, 4);
         if(ModraLEDon) lcd1.print("Rele 1 Zapnuto");
        else lcd1.print("Rele 1 Vypnuto");
    }

    displayPage++;
    if (displayPage == 4) displayPage = 0; // jdeme od znova
    nextIteration = millis() + 7000;
}}
