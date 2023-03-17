// WiFi Define
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "aisfibre_2.4G_368A9E";
const char* password = "$voot111";
// const char* ssid = "Nueng";
// const char* password = "yfwu8483";

// DHT Define
#include "DHT.h"
#define DHTTYPE DHT22
#define DHTPIN  17

DHT dht(DHTPIN, DHTTYPE);
float humidity;
float celsius;

//GPS Define
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial SerialGPS(3, 1); 
float Latitude , Longitude;
int year , month , date, hour , minute , second;
String DateString , TimeString , LatitudeString , LongitudeString;


//LCD Define
#include <LiquidCrystal_I2C.h>  
// // set the LCD number of columns and rows
int lcdColumns = 22;
int lcdRows = 21;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);


//Untrasonic
const int trigPin = 23;  
const int echoPin = 5;
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;



//buzzer
int buzzer = 16;


//Line notification
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "qzarRIBq0MzEmCmJZVa7MAfgXIYYtQUA6YIRQ0Uav0L"
#define MESSAGE "มีคนบุกรุก"


//send request define
#include <HTTPClient.h>
WiFiClient client;

String serverName = "http://159.65.132.47:8000";
unsigned long lastTime = 0;
unsigned long timerDelay = 60000;
bool alert = false;
bool sendLineCheck = false;

//web socket
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
bool security = false;

WebSocketsClient webSocket;
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
   DynamicJsonDocument json(1024);
  switch(type) {
    case WStype_CONNECTED:
     {
        Serial.println("WebSocket connected");
      // Create a JSON object and send it to the server
    
      // json["message"] = "Hello from ESP32";
      // String jsonString;
      // serializeJson(json, jsonString);
      // Serial.println(jsonString);
      // webSocket.sendTXT(jsonString);
     }
      break;
    case WStype_TEXT:
      {
        Serial.printf("Received message: %s\n", payload);
      // Handle incoming JSON messages
      
       deserializeJson(json, payload);
      String message = json["message"];
      security = message.equals("true");
        
      Serial.printf("Received message: %s\n", message.c_str());
      
      }
      break;
    case WStype_DISCONNECTED:
      {
        Serial.println("WebSocket disconnected");
      break;
      }
  }
}


void setup() {

  Serial.begin(115200);
  //setup Wifi
    WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");



  //setup untrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  //start dht
  dht.begin();
  //start LCD
  lcd.init();
  lcd.backlight();
  //start GPS
  SerialGPS.begin(9600);
  //setup buzzer
  pinMode(buzzer, OUTPUT);
  //setup Line
   LINE.setToken(LINE_TOKEN);
   //web socket
   // Connect to WebSocket server
   // Connect to the websocket server
  webSocket.begin("159.65.132.47", 8000, "/ws/security/");
  webSocket.onEvent(webSocketEvent);

 
  
}

void loop() {
  dhtSensor();
  printlcd(String(humidity) + " H",String(celsius) + " C");
  untraSonicSensor();
  gpsSensor();
  webSocket.loop();
  //check security

if(security){
  if(distanceCm < 10){
      alert = true;
  }

}else{
  alert =false;
  sendLineCheck = false;
}
 //
  if(alert == true){
   
    Serial.println("alert");
    digitalWrite(buzzer, HIGH);
 
    if(!sendLineCheck){
      sendLine();
      sendLineCheck = true;
    }
  }else{
    digitalWrite(buzzer, LOW);

  }
  sendDataToServer();

}

void dhtSensor(){
  humidity = dht.readHumidity();
  celsius = dht.readTemperature();
  // Serial.println("temperater");
  // Serial.println(humidity);
  // Serial.println(celsius);

}

void printlcd(String value1, String value2){
  lcd.setCursor(0, 0);
  lcd.print(value1);
  lcd.setCursor(0, 1);
  lcd.print(value2);
  // delay(1000);
  // lcd.clear();
}

void untraSonicSensor(){
   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance on the Serial Monitor
  // Serial.print("Distance (cm): ");
  // Serial.println(distanceCm);
  // Serial.print("Distance (inch): ");
  // Serial.println(distanceInch);
  
  // delay(1000);
}

void gpsSensor(){
  
  while (SerialGPS.available() > 0)
    Serial.println("GPS Available");
    if (gps.encode(SerialGPS.read()))
    {
      if (gps.location.isValid())
      {
        Latitude = gps.location.lat();
        LatitudeString = String(Latitude , 6);
        Longitude = gps.location.lng();
        LongitudeString = String(Longitude , 6);
          Serial.println(LatitudeString);
  Serial.println(LongitudeString);
      }

      if (gps.date.isValid())
      {
        DateString = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
        DateString = '0';
        DateString += String(date);

        DateString += " / ";

        if (month < 10)
        DateString += '0';
        DateString += String(month);
        DateString += " / ";

        if (year < 10)
        DateString += '0';
        DateString += String(year);
      }

      if (gps.time.isValid())
      {
        TimeString = "";
        hour = gps.time.hour()+ 5; //adjust UTC
        minute = gps.time.minute();
        second = gps.time.second();
    
        if (hour < 10)
        TimeString = '0';
        TimeString += String(hour);
        TimeString += " : ";

        if (minute < 10)
        TimeString += '0';
        TimeString += String(minute);
        TimeString += " : ";

        if (second < 10)
        TimeString += '0';
        TimeString += String(second);
      }
      
    }
}

void sendLine(){
  LINE.notify(MESSAGE);
}


void sendDataToServer(){
     if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
  
      HTTPClient http;
      // DynamicJsonDocument doc(1024);
      String endPoint = serverName + "/api/v1/dhtIOT/";
      Serial.println(endPoint);
      // Your Domain name with URL path or IP address with path
      http.begin(client, endPoint);
      http.setTimeout(10000);
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
      // Authorization token linebot
      // http.addHeader("Authorization","Bearer qzarRIBq0MzEmCmJZVa7MAfgXIYYtQUA6YIRQ0Uav0L");
    
      // Data to send with HTTP POST

  
      String httpRequestData = "{\"temp\":" +String(celsius)+",\"hum\":"+String(humidity)+"}";
      Serial.println(httpRequestData);
      // deserializeJson(doc, httpRequestData);
      // JsonObject obj = doc.as<JsonObject>();

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String response = http.getString();
      Serial.println(response);
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  
}








