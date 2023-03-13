// #include <SoftwareSerial.h>
// #include <TinyGPS++.h>

#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// // กำหนดขา 8 เป็น RX และขา 9 เป็น TX
// static const int RXPin = D7, TXPin = D8;
// // กำหนดค่า Baud Rate ของโมดูล GPS = 9600 (ค่า Default)
// static const uint32_t GPSBaud = 9600;
 
// // สร้าง TinyGPS++ object ชื่อ myGPS
// TinyGPSPlus myGPS;
 
// สร้าง Software Serial object ชื่อ mySerial
// SoftwareSerial mySerial(RXPin, TXPin);

#define DHTTYPE DHT22
#define DHTPIN 12
DHT dht(DHTPIN, DHTTYPE);

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup(){
  Serial.begin(115200);
  
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  // start GPS
  // mySerial.begin(GPSBaud);

  // start dht
  dht.begin();
}
// void GPSinfo(){
//   Serial.print("Location: "); 
//   // ถ้ามีข้อมูลตำแหน่ง
//   if (myGPS.location.isValid()) {
//     Serial.print(myGPS.location.lat(), 6);      // lattitude เป็นองศา ทศนิยม 6 ตำแหน่ง
//     Serial.print(", ");
//     Serial.print(myGPS.location.lng(), 6);      // longitude เป็นองศา ทศนิยม 6 ตำแหน่ง
//     Serial.print("\t");                         // เคาะวรรค 1 tab
//   } else {                                      // กรณีผิดพลาดแสดงข้อความผิดพลาด
//     Serial.print("INVALID");
//   }
// }

void loop(){
  // set cursor to first column, first row
  // print message
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  String humidity = String(h);
  String temperature = String(t);
  lcd.clear();
  printlcd(humidity + " H",temperature + " C");
  Serial.println(humidity + " " + temperature);
  // clears the display to print new message

  // delay(3000);
  //   while (mySerial.available() > 0){
  //   if (myGPS.encode(mySerial.read())){
  //     GPSinfo();
  //   }}  
  // if (millis() > 5000 && myGPS.charsProcessed() < 10) {
  //   Serial.println("No GPS detected: check wiring.");
  // }
}

void printlcd(String value1, String value2){
  lcd.setCursor(0, 0);
  lcd.print(value1);
  lcd.setCursor(0, 1);
  lcd.print(value2);
}