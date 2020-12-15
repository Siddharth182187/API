#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "SPI.h"
#include "SD.h"

const int chipSelect = D8;  // used for ESP8266
 
const char* ssid = "T102";
const char* password = "bluestar17";
 
void setup () {
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.print("Connecting..");
    
   if (!SD.begin(chipSelect)) {
   Serial.println("Initialization failed!");
   while (1);
}}
}
 
void loop() {
  String web = "http://jsonplaceholder.typicode.com/users/";
  String ext = "1";
  String url = web + ext;
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin(url);  //Specify request destination https://fastag-internal.parkzap.com/account/mockable_test/
    int httpCode = http.GET();                                  //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload 

  File dataFile = SD.open("API.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(payload);
    dataFile.close();
  }  
  else {
    Serial.println("error opening API.txt");
  }
    }
    http.end();   //Close connection
  }
  delay(5000);    //Send a request every 30 seconds
}
