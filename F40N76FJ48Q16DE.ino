#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 4   //
#define RST_PIN 5  //D1

// WiFi Credentials 
const char* ssid = ""; // thor           
const char* password = ""; // 12345678 
const char* server_url = "http://192.168.137.249:8000";

// StaticJsonBuffer<200> jsonBuffer; 
DynamicJsonBuffer jsonBuffer;

// Set up the client objet
WiFiClient client;
HTTPClient http;

// Create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN);  
int statuss = 0;
int out = 0;

// Buzzer Setup
// int frequency=1000; //Specified in Hz
// int buzzPin=2; //D3
// int timeOn=1000; //specified in milliseconds
// int timeOff=1000; //specified in millisecods

void setup() {
  Serial.begin(9600);  // Initiate a serial communication
  SPI.begin();         // Initiate  SPI bus
  mfrc522.PCD_Init();  // Initiate MFRC522

  // WiFi Setup
  delay(3000);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  delay(1000);
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();

  if (content.substring(1) == "39 3D 9E B8")  //change UID of the card that you want to give access
  {
    Serial.println("Apples Added!");
    Serial.println("Price : ₹100");

    JsonObject& values = jsonBuffer.createObject();
    values["itemname"] = "Apples";
    values["price"] = 100;

    http.begin(client, server_url);
    http.addHeader("Content-Type", "application/json");
    char json_str[100];
    values.prettyPrintTo(json_str, sizeof(json_str));

    int httpCode = http.POST(json_str);
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.print("Response: ");
        Serial.println(payload);
        // tone(buzzPin, frequency);
        // delay(timeOn);
        // noTone(buzzPin);
        // delay(timeOff);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
    }
    http.end();

    delay(1000);
    Serial.println();
    statuss = 1;
  }

  else if (content.substring(1) == "87 04 D5 60")  //change UID of the card that you want to give access
  {
    Serial.println(" Oranges Added!");
    Serial.println("Price : ₹80");

    JsonObject& values = jsonBuffer.createObject();
    values["itemname"] = "Oranges";
    values["price"] = 80;

    http.begin(client, server_url);
    http.addHeader("Content-Type", "application/json");
    char json_str[100];
    values.prettyPrintTo(json_str, sizeof(json_str));

    int httpCode = http.POST(json_str);
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.print("Response: ");
        Serial.println(payload);
        // tone(buzzPin, frequency);
        // delay(timeOn);
        // noTone(buzzPin);
        // delay(timeOff);
      }
    } 
    else {
      Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
    }
    http.end();

    delay(1000);
    Serial.println();
    statuss = 1;
  }

  else if (content.substring(1) == "05 D0 7F 22")  //change UID of the card that you want to give access
  {
    Serial.println("Banana Added!");
    Serial.println("Price : ₹50");

    JsonObject& values = jsonBuffer.createObject();
    values["itemname"] = "Banana";
    values["price"] = 50;

    http.begin(client, server_url);
    http.addHeader("Content-Type", "application/json");
    char json_str[100];
    values.prettyPrintTo(json_str, sizeof(json_str));

    int httpCode = http.POST(json_str);
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.print("Response: ");
        Serial.println(payload);
        // tone(buzzPin, frequency);
        // delay(timeOn);
        // noTone(buzzPin);
        // delay(timeOff);
      }
    } 
    else {
      Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
    }
    http.end();

    delay(1000);
    Serial.println();
    statuss = 1;
  }

  else {
    Serial.println(" Invalid Item... Please Try again. ");
    delay(3000);
  }
}
