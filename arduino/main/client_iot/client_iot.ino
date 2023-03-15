
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
bool alert = false;


//buzzer
int buzzer = 16;


void setup() {

  Serial.begin(115200);
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
  
}

void loop() {
  dhtSensor();
  printlcd(String(humidity) + " H",String(celsius) + " C");
  untraSonicSensor();
  gpsSensor();
  //check security
  if(distanceCm < 10){
      alert = true;
  }else{
    alert = false;
  }
 //
  if(alert == true){
    digitalWrite(buzzer, HIGH);
    Serial.println("alert");
    delay(2000);
  }else{
    digitalWrite(buzzer, LOW);
    delay(2000);
  }
  // digitalWrite(buzzer, LOW);
  delay(1000);
  // digitalWrite(buzzer, HIGH);
  

}

void dhtSensor(){
  humidity = dht.readHumidity();
  celsius = dht.readTemperature();
  Serial.println("temperater");
  Serial.println(humidity);
  Serial.println(celsius);

}

void printlcd(String value1, String value2){
  lcd.setCursor(0, 0);
  lcd.print(value1);
  lcd.setCursor(0, 1);
  lcd.print(value2);
  delay(3000);
  lcd.clear();
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
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(1000);
}

void gpsSensor(){
  Serial.println(SerialGPS.available());
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



