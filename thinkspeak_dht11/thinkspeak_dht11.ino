#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

const char* ssid = "TP-Link_99B2";   // network SSID  
const char* password = "91283207";   // network password
//const char* ssid = "Viettran";     
//const char* password = "viettran123";  

WiFiClient  client;

unsigned long ChannelNumber = 1730167;
const char *APIKey = "SRXZ683UFWIV1PHU";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

// Variable to hold temperature readings
float temperature = 0;
float humidity = 0;
String myStatus = "";

//buffer store value of temperature and humidity
uint8_t buff[] = {0,0};
int incoming;
uint8_t idx = 0;

void check_mess(uint8_t *buff);;

void setup() {
  Serial.begin(115200);  //Initialize serial
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect...");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
    if(Serial.available()){
      check_mess(buff);
      temperature = buff[0];
      Serial.print("Temperature: ");
      Serial.println(buff[0]);
      humidity = buff[1];
      Serial.print("Humidity: ");
      Serial.println(buff[1]);
    }
    // set the fields with the values
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(3, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(4, humidity);
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(ChannelNumber, APIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}

void check_mess(uint8_t *buff){
  while(Serial.available()){
    int tmp = 0;
    while(1){
      incoming = Serial.read();
      if(incoming == '\t') break;
      if(incoming == -1) continue;
      if(incoming == '\n'){
        buff[idx] = tmp;
        idx = 0;
        break;
      }
      tmp *= 10;
      tmp += incoming-'0';
    }
    if(incoming!='\n'){
      buff[idx] = tmp;
      idx++;
    }
  }
}
