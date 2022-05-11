#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

const char* ssid = "TP-Link_99B2";   // your network SSID (name) 
const char* password = "91283207";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1730167;
const char * myWriteAPIKey = "SRXZ683UFWIV1PHU";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

// Variable to hold temperature readings
float temperatureC = 0;
float humidity = 0;
String myStatus = "";

void setup() {
  Serial.begin(115200);  //Initialize serial
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    temperatureC++;
    humidity++;
    // set the fields with the values
    ThingSpeak.setField(1, temperatureC);
    ThingSpeak.setField(2, humidity);

    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
