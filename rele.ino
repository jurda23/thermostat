void RELE()
{
   Serial.println("Vypisuji web stranku RELE");
  long startVypisu = millis();  
char c = pripojenyClient.read();


  
//=========write signal indicator at web =========================== 
//if (digitalRead(7)) //display LED --> "1" {
//pripojenyClient.print(" LED is ON ");
//}
//else { pripojenyClient.print(" LED is OFF ");
//} 
pripojenyClient.println("<br />"); 
//========== create Form in web ==================================== 
pripojenyClient.print("<FORM action=\"http://192.168.99.150/\">"); 
pripojenyClient.print("<P><INPUT type=\"radio\"name=\"status\"value=\"1\">ON"); 
pripojenyClient.print("<P><INPUT type=\"radio\"name=\"status\"value=\"0\">OFF");
pripojenyClient.print("<P><INPUT type=\"submit\"value\"Submit\"></FORM>");
pripojenyClient.println("</html>");

//if (c == '\n') { 
//  // you're starting a new line 
//  currentLineIsBlank = true;
//  buffer=""; 
//  //clear the buffer at the end of line }
            } 
   

    
  
