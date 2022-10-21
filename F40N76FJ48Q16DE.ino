/*
 *  Created by TheCircuit
*/

#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
 if (content.substring(1) == "39 3D 9E B8") //change UID of the card that you want to give access
  {
    Serial.println(" Item 1 Added! ");
  Serial.println("Price : $10");
    delay(1000);
    Serial.println();
    statuss = 1;
  }

  else if (content.substring(1) == "87 04 D5 60") //change UID of the card that you want to give access
  {
    Serial.println(" Item 2 Added! ");
  Serial.println("Price : $20");
    delay(1000);
    Serial.println();
    statuss = 1;
  }

  else if (content.substring(1) == "05 D0 7F 22") //change UID of the card that you want to give access
  {
    Serial.println(" Item 3 Added! ");
  Serial.println("Price : $30");
    delay(1000);
    Serial.println();
    statuss = 1;
  }
  
  else   {
    Serial.println(" Invalid Item... Please Try again. ");
    delay(3000);
  }
} 
