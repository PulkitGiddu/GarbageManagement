#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS.h>
//standard libraray 
#include <NewPing.h>
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 100
NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);
LiquidCrystal lcd(13,12,11,10,9,8);
float duration,distance;
SoftwareSerial gpsSerial(5,4);
TinyGPS gps;
// create a new instance of the TinyGPS object
boolean newData=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   Serial.println(TinyGPS::library_version());
  gpsSerial.begin(9600);
  lcd.begin(20,4);
  
  Serial.begin(4800);
  Serial.begin(9600);
  
  Serial.print("Simple tiny gps library v. ");
  Serial.println("Garbage Management system");
  Serial.println("Designed by: Group4");
  Serial.println();

}

void loop() {
 lcd.setCursor(0,0);
  lcd.println("Smart Dustbin!");
  delay(100);
  lcd.clear();
  distance= sonar.ping_cm();
  lcd.setCursor(0,1);
   lcd.print("the dustbin status ");
   delay(100);
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.println(distance);
   delay(100);
   lcd.clear();
 if(distance<5)
 {
  Serial.println("Dustbin is full!!, SMS SENT");
  Serial.println(distance);
  lcd.setCursor(0,0);
  lcd.println("Dustbin is Full");
 }
 else
 {
  Serial.println(distance);
 }
   Serial.println("object happend!");
   Serial.print("DISTANCE: ");
   Serial.println(distance);

   Serial.println();
   lcd.setCursor(0,0);
   lcd.println("Something happend!");
   delay(100);
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.println("dustbin is about to full at distance: ");
   lcd.print(distance);
   delay(100);
   lcd.clear();
lcd.setCursor(0,1);
 lcd.print("sending SMS");
  gpsSerial.println("AT+CMGF=1");
  // GSM modules are set in the text modes
  delay(1000);
  // giving delay of 1s
  gpsSerial.println("AT + CMGF=\"+918491041426\"\r");
  delay(1000);
  gpsSerial.println("dustbin full!!"); //SMS text will be sent
  gpsSerial.println("Distance:");
  gpsSerial.print(distance);
  gpsSerial.println("Distance in cm");
  //the SMS text we want to send 
  gpsSerial.print(distance);
  delay(100);
  gpsSerial.print((char)26);
  //ASCII code of CTRL +Z
  lcd.clear();
  delay(1000);
  delay(20);
  //for one secound we parse GPS data and report some key values 
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //Serial.print(c);
      if (gps.encode(c))
      newData = true;
    }
  }

  if (newData)         //if newData is true 
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("Latitude = ");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print("Longitude = ");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    
  }

}
