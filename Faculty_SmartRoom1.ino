//Hand_wash,Auto_light_fan,Smart_Dustbin
#include <Servo.h>

  Servo sd,ss;  
  int pos = 0;
  int irS = 3;
  int irD = 4;
  int pir = 5;
  int led1 = 6;
//int led2 = 7;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(pir,INPUT);
  pinMode(irD,INPUT);
  pinMode(irS,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(13,OUTPUT);
//pinMode(led2,OUTPUT);
  sd.attach(8);
  ss.attach(9);
//sd.write(180);
//ss.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(irS)== LOW)
  { 
    ss.write(0);
    digitalWrite(13,HIGH);
    ss.write(90);
    ss.write(0);
    Serial.println("Thanks For Wash!!!!");
    digitalWrite(13,LOW);
    delay(3000);
  }


   if (digitalRead(irD)== LOW)
  { 
    ss.write(0);
    digitalWrite(13,HIGH);
    ss.write(90);
    ss.write(0);
    Serial.println("Thanks For Use Me!!!!");
    digitalWrite(13,LOW);
    delay(3000);
  }

   if (digitalRead(pir)== HIGH)
  { 
    digitalWrite(13,HIGH);
    Serial.println("Light and Fan On!!!!");
    digitalWrite(led1,HIGH);
  //digitalWrite(led2,HIGH);
    digitalWrite(13,LOW);
  }
  else{
    Serial.println("Light and Fan Off!!!!");
    digitalWrite(led1,LOW);
  //digitalWrite(led2,LOW);
  }
  

}
