#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define BAUDRATE 115200

const char* ssid = "Ganeshlabs";
const char* password = "8cadb11f56";

String server = "http://192.168.100.132/nodemcu/index.php";

void wifiConnecting(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan ke Access Point");
    for(int c=0;c<3;c++){
      Serial.print(" .");
      delay(1000);  
    }
    Serial.println();
  }
}

void httpRequest(int numberRandom){
  WiFiClient client;
  Serial.println("--------------------HTTP Request--------------------");
  HTTPClient http;  
  http.begin(client, server);  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String data = "number="+(String)numberRandom;
  int httpCode = http.POST(data);                                                       
  if (httpCode > 0) { 
    String payload = http.getString();
    Serial.println("HTTP Response Payload : ");
    Serial.println(payload); 
  }
  http.end(); 
  Serial.println();
}


void setup() {
  Serial.println("-------------------------------------------------");
  Serial.println("Setup NodeMCU Baudrate . . .");
  WiFi.begin(ssid, password);
  Serial.begin(BAUDRATE);
  Serial.println("Setup koneksi. . .");
  wifiConnecting();
  Serial.println("-------------------------------------------------");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { 
   httpRequest(random(20,100) );
  }else
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("NodeMCU tidak terhubung ke Access Point");
    wifiConnecting();
  }
  Serial.println("\n");
  delay(10000);
}
