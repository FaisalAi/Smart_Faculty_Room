#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include "DHT.h"

#define DHTPIN 7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04  
#define SS_PIN 10
#define RST_PIN 9
#define card "4B 90 9B 1C"
//#define tag "F0 58 C0 80"
int led1 = 4;
int led2 = 5;
int c=0;
int x=0;
//
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

MFRC522 mfrc522(SS_PIN, RST_PIN);
DHT dht(DHTPIN, DHTTYPE);
Servo s;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();   
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  s.attach(6);
  s.write(0);
  pinMode(led1,OUTPUT); 
  pinMode(led2,OUTPUT);
 
}

void loop() {
/*
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }*/
   //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

   
  if (content.substring(1) == card) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access to this card");
    Serial.println("THE GATE IS Opening!!!!");
    Serial.println();
    s.write(180);
    delay(3000);
    Serial.println("THE GATE IS Closing!!!!");
    s.write(0);
    
  }
  
  else   
  {
    Serial.println(" Access denied");
    delay(1000);
    
   }

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance<=3){
     digitalWrite(led1, HIGH);
     if(x==0){
     Serial.println("Faculty is available");
     x=1; 
    }
     else if(c%30==0){
      Serial.println("Faculty is available");
      x=0;
    }
     
     
  }
  else{
    digitalWrite(led1, LOW);
  }

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  if(c%19==0){
      Serial.print(F(" Humidity: "));
      Serial.print(h);
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.print(F("C "));
      Serial.print(f);
      Serial.print(F("F  Heat index: "));
      Serial.print(hic);
      Serial.print(F("C "));
      Serial.print(hif);
      Serial.println(F("F"));
    }
    c=c+1;
    delay(1000);
}
