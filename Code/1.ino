#include <LiquidCrystal.h>// includes the LiquidCrystal Library
#include <SoftwareSerial.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //LCD pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
const int trigPin = 7;
const int echoPin = 6;

SoftwareSerial mySerial(9, 10); //rx, tx - > tx is connected to rx

long duration;
int distanceCm, distanceInch;

void setup() 

{
lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
lcd.print("SmartDustbin");
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
mySerial.begin(9600);   // Setting the baud rate of GSM Module  
Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
delay(100);
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918491041426\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Bin Number: 300 is Full kindly empty the bin. Location: ");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

bool msgSent = false;
void loop() 
{
  lcd.setCursor(0,1);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);

digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;
//  cm = microsecondsToCentimeters(duration);

//lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
//lcd.print("Distance: "); // Prints string "Distance" on the LCD
//lcd.print(distanceCm); // Prints the distance value from the sensor
//lcd.print(" cm");
//delay(10);

//lcd.setCursor(0,0);
lcd.print("Distance: ");
lcd.print(distanceInch);
lcd.print(" inch");
delay(10);

bool full = false; //sets full to false at every loop then checks
if(distanceInch >= 150)
  {
    if(distanceInch >= 150){
    lcd.setCursor(0,0);
    lcd.print("Empty");
    Serial.println("Empty");
    full = false;
    msgSent = false;

  }
  else if(distanceInch < 150 && distanceInch > 30)
  {
     Serial.println("Medium");
     lcd.setCursor(0,0);
     lcd.print("Medium");
     full = false;
     msgSent = false;
  }
  else if(distanceInch <= 30)
  {
    Serial.println("Full!");
    lcd.setCursor(0,0);
    lcd.print("Full");
    full = true;
  }
  //if dustbin is full and message is not already sent, send the message and set message flag to true
  if(full && !msgSent)
  {
    //send message code here
    SendMessage();
    Serial.print("Sent!");
    delay(1000);
    msgSent = true;
  }

  delay(1000);
}
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
